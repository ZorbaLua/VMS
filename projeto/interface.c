
#include <gtk/gtk.h> // code heap opstack call stack
#include <stdio.h>
#include <string.h>
#include "interface.h"

int mainVMS(char*);

//-Globais-//

char *filename;

GtkEntryBuffer *bufferS, *bufferConsole, *bufferInput;
GtkWidget *window;
GtkWidget *viewC;
GtkWidget *buttonR, *button1, *buttonN;

GtkListStore *storeCode, *storeHeap, *storeOP, *storeCall;

GtkWidget *labelPC, *labelFP, *labelSP, *labelGP;


int ii = 0;  // mais tarde substituido pelo indicador do num de linhas em cada stack
int n = 0;

//-----------------------------------------------------------------------------//

static char* GtkFileOpen () {
  GtkWidget *dialog;
  GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
  gint res;

  dialog = gtk_file_chooser_dialog_new ("Open File", GTK_WINDOW (window), action, ("Cancel"), GTK_RESPONSE_CANCEL, ("Open"), GTK_RESPONSE_ACCEPT, NULL);

  res = gtk_dialog_run (GTK_DIALOG (dialog));
  if (res == GTK_RESPONSE_ACCEPT) {
      GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
      filename = gtk_file_chooser_get_filename (chooser);
      //open_file (filename);
      gtk_widget_destroy (dialog);
      g_free (filename);
      return(filename);
    }
  gtk_widget_destroy (dialog);
  //return(NULL);
}

//-----------------------------------------------------------------------------//

static void selecionar (char *i) {

  GtkTreeIter iter;
  GtkTreePath *path;
  path = gtk_tree_path_new_from_string (i);
  gtk_tree_model_get_iter(GTK_TREE_MODEL(storeCode), &iter, path);

  gtk_tree_view_set_cursor (GTK_TREE_VIEW (viewC), path, NULL, FALSE);
}

static void turnOnButtons () {
  gtk_widget_set_sensitive (buttonR, TRUE);
  gtk_widget_set_sensitive (button1, TRUE);
  gtk_widget_set_sensitive (buttonN, TRUE);
}

static void bExe (GtkWidget *widget, gpointer data) {
  g_print ("Click Executar\n");
  char co = (char) n++;
  selecionar(co);
}

static void bExeT (GtkWidget *widget, gpointer data) {
  g_print ("Click Executar N\n");
  const gchar *vezes = gtk_entry_buffer_get_text(bufferS);
  g_print ("-> %s\n", vezes);
}

static void bLoadPFile (GtkWidget *widget, gpointer data) {
  g_print ("Click Load Programa\n");
  char* ficheiro = GtkFileOpen ();
  if (ficheiro != NULL) {
    mainVMS(ficheiro);
    turnOnButtons();
  }
}

static void bReloadFile (GtkWidget *widget, gpointer data) {
  mainVMS(filename);
  g_print ("Click Reload File\n");
}

static void bLoadIFile (GtkWidget *widget, gpointer data) {
  g_print ("Click Load Input\n");
  char* ficheiro = GtkFileOpen ();
}

//-----------------------------------------------------------------------------//

void actLabel (GtkWidget *grid, int lab, int value) {

  char l[10], b[5];
  sprintf(b, "%d", value);
  switch (lab) {
    case 0:
      strncpy(l, "PC:", 10); strcat(l,b);
      gtk_label_set_text (GTK_LABEL (labelPC), l);
    case 1:
      strncpy(l, "FP:", 10); strcat(l,b);
      gtk_label_set_text (GTK_LABEL (labelFP), l);
    case 2:
      strncpy(l, "SP:", 10); strcat(l,b);
      gtk_label_set_text (GTK_LABEL (labelSP), l);
    case 3:
      strncpy(l, "GP:", 10); strcat(l,b);
      gtk_label_set_text (GTK_LABEL (labelGP), l);
    default :
    g_print("Erro label invalido\n" );
  }
}

    //-----------------------------------------//

static void activateLables (GtkWidget *grid) {

  GtkWidget *label;

  label = gtk_label_new ("Code");
  gtk_grid_attach (GTK_GRID (grid), label, 0, 0, 3, 1);

  label = gtk_label_new ("Heap");
  gtk_grid_attach (GTK_GRID (grid), label, 3, 0, 3, 1);

  label = gtk_label_new ("Call Stack");
  gtk_grid_attach (GTK_GRID (grid), label, 6, 0, 3, 1);

  label = gtk_label_new ("OPStack");
  gtk_grid_attach (GTK_GRID (grid), label, 9, 0, 3, 1);

  //-------------------------------------------//

  labelPC = gtk_label_new ("PC:...");
  gtk_grid_attach (GTK_GRID (grid), labelPC, 12, 0, 1, 1);

  labelFP = gtk_label_new ("FP:...");
  gtk_grid_attach (GTK_GRID (grid), labelFP, 13, 0, 1, 1);

  labelSP = gtk_label_new ("SP:...");
  gtk_grid_attach (GTK_GRID (grid), labelSP, 14, 0, 1, 1);

  labelGP = gtk_label_new ("GP:...");
  gtk_grid_attach (GTK_GRID (grid), labelGP, 15, 0, 1, 1);

}

//-----------------------------------------------------------------------------//

static void activateInputs (GtkWidget *grid) {

  GtkWidget *entry;

  //gtk_widget_set_hexpand (entry, FALSE);
  //gtk_widget_set_vexpand (entry, FALSE);

  bufferS = gtk_entry_buffer_new ("-1", 2);
  entry = gtk_entry_new_with_buffer (bufferS);
  gtk_entry_set_max_length (GTK_ENTRY (entry), 2);
  gtk_grid_attach (GTK_GRID (grid), entry, 14, 2, 2, 1);

    //-----------------------------------------//

  GtkWidget *button;

  button1 = gtk_button_new_with_label ("Execute 1");
  g_signal_connect (button1, "clicked", G_CALLBACK (bExe), NULL);
  gtk_widget_set_sensitive (button1, FALSE);
  gtk_grid_attach (GTK_GRID (grid), button1, 12, 1, 4, 1);

  buttonN = gtk_button_new_with_label ("Execute N:");
  g_signal_connect (buttonN, "clicked", G_CALLBACK (bExeT), NULL);
  gtk_widget_set_sensitive (buttonN, FALSE);
  gtk_grid_attach (GTK_GRID (grid), buttonN, 12, 2, 2, 1);

  button = gtk_button_new_with_label ("Load Program File");
  g_signal_connect (button, "clicked", G_CALLBACK (bLoadPFile), NULL);
  gtk_grid_attach (GTK_GRID (grid), button, 12, 3, 2, 1);

  buttonR = gtk_button_new_with_label ("Reload File");
  g_signal_connect (button, "clicked", G_CALLBACK (bReloadFile), NULL);
  gtk_widget_set_sensitive (buttonR, FALSE);
  gtk_grid_attach (GTK_GRID (grid), buttonR, 14, 3, 2, 1);

  button = gtk_button_new_with_label ("Load Input File");
  g_signal_connect (button, "clicked", G_CALLBACK (bLoadIFile), NULL);
  gtk_grid_attach (GTK_GRID (grid), button, 12, 4, 4, 1);

    //-----------------------------------------//

  GtkWidget *scrolled_window;
  GtkWidget *view;

  scrolled_window = gtk_scrolled_window_new (NULL, NULL);

  gtk_widget_set_hexpand (scrolled_window, FALSE);
  gtk_widget_set_vexpand (scrolled_window, FALSE);

  bufferInput = gtk_entry_buffer_new ("Input", 25);

  view = gtk_text_view_new ();
  //view = gtk_text_view_new_with_buffer (GTK_TEXT_BUFFER(bufferInput)); // <- CORRIGIR
  gtk_text_view_set_editable (GTK_TEXT_VIEW (view), TRUE);
  gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW (view), TRUE);
  gtk_container_add (GTK_CONTAINER (scrolled_window), view);
  gtk_grid_attach (GTK_GRID (grid), scrolled_window, 12, 9, 4, 3);

    //-----------------------------------------//

  scrolled_window = gtk_scrolled_window_new (NULL, NULL);

  gtk_widget_set_hexpand (scrolled_window, FALSE);
  gtk_widget_set_vexpand (scrolled_window, FALSE);

  bufferConsole = gtk_entry_buffer_new ("Consola", 25);

  view = gtk_text_view_new ();
  //view = gtk_text_view_new_with_buffer (GTK_TEXT_BUFFER(bufferConsole));  // <- CORRIGIR
  gtk_text_view_set_editable (GTK_TEXT_VIEW (view), FALSE);
  gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW (view), FALSE);
  gtk_container_add (GTK_CONTAINER (scrolled_window), view);
  gtk_grid_attach (GTK_GRID (grid), scrolled_window, 12, 5, 4, 4);
}

//-----------------------------------------------------------------------------//

void remLinha(char *i, GtkListStore* a) {
  GtkTreeIter iter;
  GtkTreePath *path;
  path = gtk_tree_path_new_from_string (i);
  gtk_tree_model_get_iter(GTK_TREE_MODEL(a), &iter, path);
  gtk_list_store_remove (GTK_LIST_STORE(a), &iter);
}

  //-----------------------------------------//

void insCode(char *instr, int vA, int vB, int idx) {
  GtkTreeIter iter;
  enum stack {Index, Instruction, ValueA, ValueB, NUM_COLS };
  gtk_list_store_append(storeCode, &iter);
  gtk_list_store_set (storeCode, &iter, Index, idx, Instruction, instr, ValueA, vA, ValueB, vB, -1);
}

void insHeap(int val, char *tp, int idx) {
  GtkTreeIter iter;
  enum stack {Index, Value, Type, NUM_COLS };
  gtk_list_store_append(storeHeap, &iter);
  gtk_list_store_set (storeHeap, &iter, Index, idx, Value, val, Type, tp, -1);
}

void insOP(int pc, int fp, int idx) {
  GtkTreeIter iter;
  enum stack {Index, PcValue, FpValue, NUM_COLS };
  gtk_list_store_append(storeOP, &iter);
  gtk_list_store_set (storeOP, &iter, Index, idx, PcValue, pc, FpValue, fp, -1);
}

void insCall(int val, char *tp, int idx) {
  GtkTreeIter iter;
  enum stack {Index, Value, Type, NUM_COLS };
  gtk_list_store_append(storeCall, &iter);
  gtk_list_store_set (storeCall, &iter, Index, idx, Value, val, Type, tp, -1);
}

//-----------------------------------------------------------------------------//

static void criarJanela (GtkWidget *view, GtkWidget *grid, int x, int y, int xx, int yy) {

  GtkWidget *scrolled_window;
  scrolled_window = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_set_hexpand (scrolled_window, TRUE);
  gtk_widget_set_vexpand (scrolled_window, TRUE);
  gtk_container_add (GTK_CONTAINER (scrolled_window), view);
  gtk_grid_attach (GTK_GRID (grid), scrolled_window, x, y, xx, yy);
}

//-----------------------------------------------------------------------------//

static void activateSCode (GtkWidget *grid, int x, int y, int xx, int yy) {

  GtkCellRenderer *renderer;
  GtkTreeModel    *model;

  viewC = gtk_tree_view_new ();
  renderer = gtk_cell_renderer_text_new ();\

  enum stack {Index, Instruction, ValueA, ValueB, NUM_COLS };
  static const char *nomes[] = {"Index", "Instruction", "ValueA", "ValueB"};
  storeCode = gtk_list_store_new (NUM_COLS, G_TYPE_INT, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT );

  for (int coluna = Index; coluna < NUM_COLS; coluna++) {
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (viewC), -1, nomes[coluna], renderer, "text", coluna, NULL);
  }

  model = GTK_TREE_MODEL (storeCode);
  gtk_tree_view_set_model (GTK_TREE_VIEW (viewC), model);

  criarJanela(viewC, grid, x, y, xx, yy);
}

  //-----------------------------------------//

static void activateSHeap (GtkWidget *grid, int x, int y, int xx, int yy) {

  GtkWidget       *view;
  GtkCellRenderer *renderer;
  GtkTreeModel    *model;

  view = gtk_tree_view_new ();
  renderer = gtk_cell_renderer_text_new ();\

  enum stack {Index, Value, Type, NUM_COLS };
  static const char *nomes[] = {"Index", "Value", "Type"};
  storeHeap = gtk_list_store_new (NUM_COLS, G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING);

  for (int coluna = Index; coluna < NUM_COLS; coluna++) {
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view), -1, nomes[coluna], renderer, "text", coluna, NULL);
  }

  model = GTK_TREE_MODEL (storeHeap);
  gtk_tree_view_set_model (GTK_TREE_VIEW (view), model);

  criarJanela(view, grid, x, y, xx, yy);
}

  //-----------------------------------------//

static void activateSOP (GtkWidget *grid, int x, int y, int xx, int yy) {

  GtkWidget       *view;
  GtkCellRenderer *renderer;
  GtkTreeModel    *model;

  view = gtk_tree_view_new ();
  renderer = gtk_cell_renderer_text_new ();\

  enum stack {Index, PcValue, FpValue, NUM_COLS };
  static const char *nomes[] = {"Index", "PcValue", "FpValue"};
  storeOP = gtk_list_store_new (NUM_COLS, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT);

  for (int coluna = Index; coluna < NUM_COLS; coluna++) {
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view), -1, nomes[coluna], renderer, "text", coluna, NULL);
  }

  model = GTK_TREE_MODEL (storeOP);
  gtk_tree_view_set_model (GTK_TREE_VIEW (view), model);

  criarJanela(view, grid, x, y, xx, yy);
}

    //-----------------------------------------//

static void activateSCall (GtkWidget *grid, int x, int y, int xx, int yy) {

  GtkWidget       *view;
  GtkCellRenderer *renderer;
  GtkTreeModel    *model;

  view = gtk_tree_view_new ();
  renderer = gtk_cell_renderer_text_new ();\

  enum stack {Index, Value, Type, NUM_COLS };
  static const char *nomes[] = {"Index", "Value", "Type"};
  storeCall= gtk_list_store_new (NUM_COLS, G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING);

  for (int coluna = Index; coluna < NUM_COLS; coluna++) {
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view), -1, nomes[coluna], renderer, "text", coluna, NULL);
  }

  model = GTK_TREE_MODEL (storeCall);
  gtk_tree_view_set_model (GTK_TREE_VIEW (view), model);

  criarJanela(view, grid, x, y, xx, yy);
}

//-----------------------------------------------------------------------------//

void activateStacks (GtkWidget *grid) {
  activateSCode (grid, 0, 1, 3, 11);
  activateSHeap (grid, 3, 1, 3, 11);
  activateSOP   (grid, 6, 1, 3, 11);
  activateSCall (grid, 9, 1, 3, 11);

  GtkTreeSelection x;

}

//-----------------------------------------------------------------------------//

static void activate (GtkApplication *app, gpointer user_data) {

  GtkWidget *grid;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "VMS-Projeto");
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  grid = gtk_grid_new ();
  gtk_container_add (GTK_CONTAINER (window), grid);
  gtk_grid_set_row_spacing (GTK_GRID (grid),10);
  gtk_grid_set_column_spacing (GTK_GRID (grid),10);
  //gtk_grid_set_column_homogeneous (GTK_GRID (grid),TRUE);

    //-----------------------------------------//

  activateInputs (grid);
  activateStacks (grid);
  activateLables (grid);

    //-----------------------------------------//

  gtk_widget_show_all (window);

}

//-----------------------------------------------------------------------------//

int main (int argc, char **argv) {

  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);


  return status;
}
