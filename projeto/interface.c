
#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "structs/types.h"

//-Globais-//

GtkWidget *window;
GtkWidget *grid;
GtkEntryBuffer *bufferS;
GtkTextBuffer *bufferConsole, *bufferInput;
GtkWidget *viewC;
GtkListStore *storeCode, *storeHeap, *storeOP, *storeCall;
GtkWidget *labelPC, *labelFP, *labelSP, *labelGP;
GtkWidget *buttonR, *button1, *buttonN;

char* lastfile;

#define PC 0
#define FP 1
#define SP 2
#define GP 3

void insCode(char*);
void insCall(char*);
void insOP(char*);
void insHeap(char*);

//-----------------------------------------------------------------------------//

void freeLine(char** line, int t) {
    for(int i=0; i<t; i++) free(line[i]);
}

void initLine(char** line, int t) {
    for(int i=0; i<t; i++) line[i] = (char*)malloc(10 * sizeof(char));
}

void parseLine(char* line) {
    if(!strncmp(line, "> CO", 3)) insCode(line);
    else if(!strncmp(line, "> CA", 3)) insCall(line);
    else if(!strncmp(line, "> OP", 3)) insOP(line);
    else if(!strncmp(line, "> HE", 3)) insHeap(line);
    //else if(!strncmp(line, "\e[", 2)) {;}
    //else { }
}

//-----------------------------------------------------------------------------//

static char* GtkFileOpen () {

  GtkWidget *dialog;
  GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
  gint res;

  dialog = gtk_file_chooser_dialog_new ("Open File", GTK_WINDOW (window), action, ("Cancel"), GTK_RESPONSE_CANCEL, ("Open"), GTK_RESPONSE_ACCEPT, NULL);

  res = gtk_dialog_run (GTK_DIALOG (dialog));
  if (res == GTK_RESPONSE_ACCEPT) {
      char *filename;
      GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
      filename = gtk_file_chooser_get_filename (chooser);
      gtk_widget_destroy (dialog);
      lastfile = filename;
      return(filename);
    }
  gtk_widget_destroy (dialog);
  return NULL;
}

//-----------------------------------------------------------------------------//

static void selecionar (const gchar *i) {

  GtkTreeIter iter;
  GtkTreePath *path;
  const gchar *b = i + 3;
  path = gtk_tree_path_new_from_string (b);
  gtk_tree_model_get_iter(GTK_TREE_MODEL(storeCode), &iter, path);

  gtk_tree_view_set_cursor (GTK_TREE_VIEW (viewC), path, NULL, FALSE);
}

static void turnButtons (_Bool b) {
  gtk_widget_set_sensitive (buttonR, b);
  gtk_widget_set_sensitive (button1, b);
  gtk_widget_set_sensitive (buttonN, b);
}

static void limpaStacks() {
  gtk_list_store_clear (storeCode);
  gtk_list_store_clear (storeHeap);
  gtk_list_store_clear (storeOP);
  gtk_list_store_clear (storeCall);
}

    //-----------------------------------------//

static void exeInst (const char* nvezes) {

  char line[MAX_LINE];
  if(nvezes[0] == '0'){ fprintf(stdout, "run \n"); fflush(stdout); }
  else { fprintf(stdout, "next %s\n", nvezes); fflush(stdout); }
  line[0]='>';
  while(line[0] == '>'){
    fgets(line, MAX_LINE, stdin);
    parseLine(line);
  }
}

static void bExe (GtkWidget *widget, gpointer data) {
  exeInst("1");
}

static void bExeT (GtkWidget *widget, gpointer data) {
  const char* n = gtk_entry_buffer_get_text(bufferS);
  exeInst(n);
}

static void loadficheiro(char *filename) {

  int len;
  char line[MAX_LINE];

  fprintf(stdout, "file %s\n", filename); fflush(stdout);
  turnButtons(TRUE);

  line[0]='>';
  while(line[0] == '>'){
    fgets(line, MAX_LINE, stdin);
    parseLine(line);
  }
  free(filename);
}

static void bLoadPFile (GtkWidget *widget, gpointer data) {

  char* filename = GtkFileOpen();
  limpaStacks();

  if (filename != NULL) {
    loadficheiro(filename);
  }
  //else { turnButtons(FALSE); }
}

static void bReloadFile (GtkWidget *widget, gpointer data) { // POR ISTO DIREITO
  loadficheiro(lastfile);
}

static void bLoadIFile (GtkWidget *widget, gpointer data) {
  char* filename = GtkFileOpen();
  limpaStacks();

  if (filename != NULL) {
    GError *err = NULL;
    gchar *contents;

    g_file_get_contents (filename, &contents, NULL, &err);
    gtk_text_buffer_set_text (bufferInput, contents, strlen(contents));
  }
  //else { turnButtons(FALSE); }
}

//-----------------------------------------------------------------------------//

void actLabel (int lab, int value) {

  GtkWidget *label;
  char l[10], b[5];
  sprintf(b, "%d", value);
  switch (lab) {
    case PC:
      strncpy(l, "PC:", 10); strcat(l,b);
      gtk_label_set_text (GTK_LABEL (labelPC), l); break;
    case FP:
      strncpy(l, "FP:", 10); strcat(l,b);
      gtk_label_set_text (GTK_LABEL (labelFP), l); break;
    case SP:
      strncpy(l, "SP:", 10); strcat(l,b);
      gtk_label_set_text (GTK_LABEL (labelSP), l); break;
    case GP:
      strncpy(l, "GP:", 10); strcat(l,b);
      gtk_label_set_text (GTK_LABEL (labelGP), l); break;
    default :
    g_print("Erro label invalido\n" );
  }
}

    //-----------------------------------------//

static void activateLables () {

  GtkWidget *label;

  label = gtk_label_new ("Code");
  gtk_grid_attach (GTK_GRID (grid), label, 0, 0, 1, 1);

  label = gtk_label_new ("Heap");
  gtk_grid_attach (GTK_GRID (grid), label, 2, 0, 1, 1);

  label = gtk_label_new ("OPStack");
  gtk_grid_attach (GTK_GRID (grid), label, 1, 0, 1, 1);

  label = gtk_label_new ("Call Stack");
  gtk_grid_attach (GTK_GRID (grid), label, 2, 10, 1, 1);

  //-------------------------------------------//

  labelPC = gtk_label_new ("PC:0");
  gtk_grid_attach (GTK_GRID (grid), labelPC, 3, 0, 1, 1);

  labelFP = gtk_label_new ("FP:0");
  gtk_grid_attach (GTK_GRID (grid), labelFP, 4, 0, 1, 1);

  labelSP = gtk_label_new ("SP:0");
  gtk_grid_attach (GTK_GRID (grid), labelSP, 5, 0, 1, 1);

  labelGP = gtk_label_new ("GP:0");
  gtk_grid_attach (GTK_GRID (grid), labelGP, 6, 0, 1, 1);
}

//-----------------------------------------------------------------------------//

static void activateInputs () {

  GtkWidget *entry;

  //gtk_widget_set_hexpand (entry, FALSE);
  //gtk_widget_set_vexpand (entry, FALSE);

  bufferS = gtk_entry_buffer_new ("1", 1);
  entry = gtk_entry_new_with_buffer (bufferS);
  gtk_entry_set_max_length (GTK_ENTRY (entry), 5);
  gtk_grid_attach (GTK_GRID (grid), entry, 5, 2, 2, 1);

    //-----------------------------------------//

  GtkWidget *button;

  button1 = gtk_button_new_with_label ("Execute 1");
  g_signal_connect (button1, "clicked", G_CALLBACK (bExe), NULL);
  gtk_widget_set_sensitive (button1, FALSE);
  gtk_grid_attach (GTK_GRID (grid), button1, 3, 1, 4, 1);

  buttonN = gtk_button_new_with_label ("Execute N:");
  g_signal_connect (buttonN, "clicked", G_CALLBACK (bExeT), NULL);
  gtk_widget_set_sensitive (buttonN, FALSE);
  gtk_grid_attach (GTK_GRID (grid), buttonN, 3, 2, 2, 1);

  button = gtk_button_new_with_label ("Load Program File");
  g_signal_connect (button, "clicked", G_CALLBACK (bLoadPFile), NULL);
  gtk_grid_attach (GTK_GRID (grid), button, 3, 3, 2, 1);

  buttonR = gtk_button_new_with_label ("Reload File?");
  g_signal_connect (buttonR, "clicked", G_CALLBACK (bReloadFile), NULL);
  gtk_widget_set_sensitive (buttonR, FALSE);
  gtk_grid_attach (GTK_GRID (grid), buttonR, 5, 3, 2, 1);

  button = gtk_button_new_with_label ("Load Input File");
  g_signal_connect (button, "clicked", G_CALLBACK (bLoadIFile), NULL);
  gtk_grid_attach (GTK_GRID (grid), button, 3, 4, 4, 1);

    //-----------------------------------------//

  GtkWidget *scrolled_window;
  GtkWidget *view;

  scrolled_window = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_set_hexpand (scrolled_window, FALSE);
  gtk_widget_set_vexpand (scrolled_window, FALSE);

  view = gtk_text_view_new();
  bufferInput = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));

  gtk_text_view_set_editable (GTK_TEXT_VIEW (view), TRUE);
  gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW (view), TRUE);
  gtk_container_add (GTK_CONTAINER (scrolled_window), view);
  gtk_grid_attach (GTK_GRID (grid), scrolled_window, 3, 13, 4, 7);

    //-----------------------------------------//

  scrolled_window = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_set_hexpand (scrolled_window, FALSE);
  gtk_widget_set_vexpand (scrolled_window, FALSE);

  view = gtk_text_view_new();
  bufferConsole = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));

  gtk_text_view_set_editable (GTK_TEXT_VIEW (view), FALSE);
  gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW (view), FALSE);
  gtk_container_add (GTK_CONTAINER (scrolled_window), view);
  gtk_grid_attach (GTK_GRID (grid), scrolled_window, 3, 5, 4, 8);

}

//-----------------------------------------------------------------------------//

void remLinha(int i, GtkListStore* a) {
  GtkTreeIter iter;
  GtkTreePath *path;
  path = gtk_tree_path_new_from_indices (i, -1);
  gtk_tree_model_get_iter(GTK_TREE_MODEL(a), &iter, path);
  gtk_list_store_remove (GTK_LIST_STORE(a), &iter);
}

void treatOutput(char extension) {

  GtkTextIter inicio, fim;
  gtk_text_buffer_get_iter_at_line (bufferInput, &inicio, 0);
  gtk_text_buffer_get_iter_at_line (bufferInput, &fim, 1000);

  char *tudo;
  tudo = gtk_text_buffer_get_text (bufferInput, &inicio, &fim, FALSE);

  char* tudoMaisExtension;
  tudoMaisExtension = malloc(strlen(tudo)+strlen(extension));
  strcpy(tudoMaisExtension, tudo);
  strcat(tudoMaisExtension, extension);
  free(tudo);

  gtk_text_buffer_set_text (bufferConsole, tudoMaisExtension, strlen(tudoMaisExtension));

}


char* treatInput() {

  GtkTextIter inicio, fim;

  gtk_text_buffer_get_iter_at_line (bufferInput, &inicio, 0);
  gtk_text_buffer_get_iter_at_line (bufferInput, &fim, 1);

  char *teste;
  teste = gtk_text_buffer_get_text (bufferInput, &inicio, &fim, FALSE);
  //gtk_text_buffer_set_text (bufferConsole, teste, strlen(teste));
  gtk_text_buffer_get_iter_at_line (bufferInput, &fim, 1000); // 1000 LINHAS DE INPUT DEVEM CHEGAR

  if (strlen(teste) == 0) {return "FALTA DE INPUT";}
  else {
    char *tudo;
    tudo = gtk_text_buffer_get_text (bufferInput, &inicio, &fim, FALSE);
    tudo += strlen(teste);
    gtk_text_buffer_set_text (bufferInput, tudo, strlen(tudo));
  }
  return teste;
}

  //-----------------------------------------//

void insCode(char *line) {

    GtkTreeIter iter;
    enum stack {Index, Instruction, ValueA, TypeA, ValueB, TypeB, NUM_COLS };
    char* arr[NUM_COLS];
    int codePC;
    char signal;

    initLine(arr, NUM_COLS);
    sscanf(line, "> CODE %c %s %s %s %s %s %s %d\n", &signal, arr[0], arr[1], arr[3], arr[2], arr[5], arr[4], &codePC);
    if(signal == '+'){
        gtk_list_store_append(storeCode, &iter);
        gtk_list_store_set (storeCode, &iter,   Index,          arr[0],
                                                Instruction,    arr[1],
                                                ValueA,         arr[2],
                                                TypeA,          arr[3],
                                                ValueB,         arr[4],
                                                TypeB,          arr[5],
                                                -1);
    }
    actLabel(PC, codePC);
    selecionar( gtk_label_get_text (labelPC) );
    freeLine(arr, NUM_COLS);
}

void insOP(char *line) {

    GtkTreeIter iter;
    enum stack {Index, Value, Type, NUM_COLS };
    char* arr[NUM_COLS];
    int sp, fp, gp;
    char signal;

    initLine(arr, NUM_COLS);
    sscanf(line, "> OPSTACK %c %s %s %s %d %d %d\n", &signal, arr[0], arr[2], arr[1], &sp, &fp, &gp);
    if(signal == '+'){
        gtk_list_store_append(storeOP, &iter);
        gtk_list_store_set (storeOP, &iter, Index, arr[0],
                                            Value, arr[1],
                                            Type,  arr[2],
                                            -1);
    }
    else if(signal == '-') remLinha(sp,storeOP);
    actLabel(SP, sp);
    actLabel(FP, fp);
    actLabel(GP, gp);
    freeLine(arr, NUM_COLS);
}

void insHeap(char *line) {
  /*
    GtkTreeIter iter;
    enum stack {Index, Value, Type, NUM_COLS };
    gtk_list_store_append(storeHeap, &iter);
    gtk_list_store_set (storeHeap, &iter, Index, idx, Value, val, Type, tp, -1);
    */
}

void insCall(char *line) {

    GtkTreeIter iter;
    enum stack {Index, PcValue, FpValue , NUM_COLS };
    char* arr[NUM_COLS];
    int pc, fp;
    char signal;

    initLine(arr, NUM_COLS);
    sscanf(line, "> CALLSTACK %c %s %s %s", &signal, arr[0], arr[2], arr[1]);
    if(signal == '+'){
        gtk_list_store_append(storeCall, &iter);
        gtk_list_store_set (storeCall, &iter, Index,    arr[0],
                                              PcValue,  arr[1],
                                              FpValue,  arr[2],
                                              -1);
    }
    else if(signal == '-') gtk_list_store_remove(storeCall, &iter);
    freeLine(arr, NUM_COLS);
}

//-----------------------------------------------------------------------------//

static void criarJanela (GtkWidget *view, int x, int y, int xx, int yy) {

  GtkWidget *scrolled_window;
  scrolled_window = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_set_hexpand (scrolled_window, TRUE);
  gtk_widget_set_vexpand (scrolled_window, TRUE);
  gtk_container_add (GTK_CONTAINER (scrolled_window), view);
  gtk_grid_attach (GTK_GRID (grid), scrolled_window, x, y, xx, yy);
}

//-----------------------------------------------------------------------------//

static void activateSCode (int x, int y, int xx, int yy) {
  GtkCellRenderer *renderer;
  GtkTreeModel    *model;

  viewC = gtk_tree_view_new ();
  renderer = gtk_cell_renderer_text_new ();\

  enum stack {Index, Instruction, ValueA, TypeA, ValueB, TypeB, NUM_COLS };
  static const char *nomes[] = {"#--", "Instruction", "ValueA", "TypeA", "ValueB", "TypeB"};
  storeCode = gtk_list_store_new (NUM_COLS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

  for (int coluna = Index; coluna < NUM_COLS; coluna++) {
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (viewC), -1, nomes[coluna], renderer, "text", coluna, NULL);
  }

  model = GTK_TREE_MODEL (storeCode);
  gtk_tree_view_set_model (GTK_TREE_VIEW (viewC), model);

  criarJanela(viewC, x, y, xx, yy);
}

  //-----------------------------------------//

static void activateSHeap (int x, int y, int xx, int yy) {

  GtkWidget       *view;
  GtkCellRenderer *renderer;
  GtkTreeModel    *model;

  view = gtk_tree_view_new ();
  renderer = gtk_cell_renderer_text_new ();\

  enum stack {Index, Value, Type, NUM_COLS };
  static const char *nomes[] = {"#--", "Value", "Type"};
  storeHeap = gtk_list_store_new (NUM_COLS, G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING);

  for (int coluna = Index; coluna < NUM_COLS; coluna++) {
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view), -1, nomes[coluna], renderer, "text", coluna, NULL);
  }

  model = GTK_TREE_MODEL (storeHeap);
  gtk_tree_view_set_model (GTK_TREE_VIEW (view), model);

  criarJanela(view, x, y, xx, yy);
}

  //-----------------------------------------//

static void activateSOP (int x, int y, int xx, int yy) {

  GtkWidget       *view;
  GtkCellRenderer *renderer;
  GtkTreeModel    *model;

  view = gtk_tree_view_new ();
  renderer = gtk_cell_renderer_text_new ();\

  enum stack {Index, PcValue, FpValue, NUM_COLS };
  static const char *nomes[] = {"#--", "Value", "Type"};
  storeOP = gtk_list_store_new (NUM_COLS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

  for (int coluna = Index; coluna < NUM_COLS; coluna++) {
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view), -1, nomes[coluna], renderer, "text", coluna, NULL);
  }

  model = GTK_TREE_MODEL (storeOP);
  gtk_tree_view_set_model (GTK_TREE_VIEW (view), model);

  criarJanela(view, x, y, xx, yy);
}

    //-----------------------------------------//

static void activateSCall (int x, int y, int xx, int yy) {

  GtkWidget       *view;
  GtkCellRenderer *renderer;
  GtkTreeModel    *model;

  view = gtk_tree_view_new ();
  renderer = gtk_cell_renderer_text_new ();

  enum stack {Index, Value, Type, NUM_COLS };
  static const char *nomes[] = {"#--", "PcValue", "FpValue"};
  storeCall= gtk_list_store_new (NUM_COLS, G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING);

  for (int coluna = Index; coluna < NUM_COLS; coluna++) {
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view), -1, nomes[coluna], renderer, "text", coluna, NULL);
  }

  model = GTK_TREE_MODEL (storeCall);
  gtk_tree_view_set_model (GTK_TREE_VIEW (view), model);

  criarJanela(view, x, y, xx, yy);
}

//-----------------------------------------------------------------------------//

void activateStacks () {
  activateSCode (0, 1, 1, 19);
  activateSHeap (2, 1, 1, 9);
  activateSCall (2, 11, 1, 9);
  activateSOP   (1, 1, 1, 19);

  GtkTreeSelection x;
}

//-----------------------------------------------------------------------------//

static void activate () {
  grid = gtk_grid_new ();
  gtk_container_add (GTK_CONTAINER (window), grid);
  gtk_grid_set_row_spacing (GTK_GRID (grid),10);
  gtk_grid_set_column_spacing (GTK_GRID (grid),10);
  //gtk_grid_set_column_homogeneous (GTK_GRID (grid),TRUE);

  activateInputs ();
  activateStacks ();
  activateLables ();

  turnButtons(TRUE);

  gtk_widget_show_all (window);
}

//-----------------------------------------------------------------------------//
void loadInitial(){
  char line[MAX_LINE];
  line[0]='>';
  while(line[0] == '>'){
    fgets(line, MAX_LINE, stdin);
    parseLine(line);
  }
}

int main (int argc, char **argv) {
  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 400);
  gtk_window_set_title (GTK_WINDOW (window), "VMS-Projeto");
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  g_signal_connect (window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  activate();

  gtk_widget_show (window);
  loadInitial();
  gtk_main ();
  return 0;
}
