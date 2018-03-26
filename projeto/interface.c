
#include <gtk/gtk.h> // code heap opstack call stack

// gcc -o interface interface.c $(pkg-config --cflags --libs gtk+-3.0)

//-Globais-//

GtkEntryBuffer *bufferS, *bufferConsole, *bufferInput;
GtkWidget *window;

GtkListStore *storeCode, *storeHeap, *storeOP, *storeCall;

//-----------------------------------------------------------------------------//

static char GtkFileOpen () {
  GtkWidget *dialog;
  GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
  gint res;

  dialog = gtk_file_chooser_dialog_new ("Open File", GTK_WINDOW (window), action, ("Cancel"), GTK_RESPONSE_CANCEL, ("Open"), GTK_RESPONSE_ACCEPT, NULL);

  res = gtk_dialog_run (GTK_DIALOG (dialog));
  if (res == GTK_RESPONSE_ACCEPT) {
      char *filename;
      GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
      filename = gtk_file_chooser_get_filename (chooser);
      //open_file (filename);
      gtk_widget_destroy (dialog);
      g_free (filename);
      return(*filename);
    }
  gtk_widget_destroy (dialog);
}

//-----------------------------------------------------------------------------//

static void bExe (GtkWidget *widget, gpointer data) {
  g_print ("Click Executar\n");
  //gtk_tree_view_set_cursor (GtkTreeView *tree_view, GtkTreePath *path, GtkTreeViewColumn *focus_column, gboolean start_editing);
}

static void bExeT (GtkWidget *widget, gpointer data) {
  const gchar *vezes = gtk_entry_buffer_get_text(bufferS);
  g_print ("Click Executar N\n");
  g_print ("-> %s\n", vezes);
}

static void bLoadPFile (GtkWidget *widget, gpointer data) {
  char ficheiro = GtkFileOpen ();
  g_print ("Click Load Programa\n");
}

static void bLoadIFile (GtkWidget *widget, gpointer data) {
  char ficheiro = GtkFileOpen ();
  g_print ("Click Load Input\n");
}

//-----------------------------------------------------------------------------//

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

  label = gtk_label_new ("PC:0");
  gtk_grid_attach (GTK_GRID (grid), label, 12, 0, 1, 1);

  label = gtk_label_new ("FP:0");
  gtk_grid_attach (GTK_GRID (grid), label, 13, 0, 1, 1);

  label = gtk_label_new ("SP:0");
  gtk_grid_attach (GTK_GRID (grid), label, 14, 0, 1, 1);

  label = gtk_label_new ("GP:0");
  gtk_grid_attach (GTK_GRID (grid), label, 15, 0, 1, 1);

}

//-----------------------------------------------------------------------------//

static void activateInputs (GtkWidget *grid) {

  GtkWidget *entry;

  //gtk_widget_set_hexpand (entry, FALSE);
  //gtk_widget_set_vexpand (entry, FALSE);

  bufferS = gtk_entry_buffer_new ("-1", 3);
  entry = gtk_entry_new_with_buffer (bufferS);
  gtk_entry_set_max_length (GTK_ENTRY (entry), 5);
  gtk_grid_attach (GTK_GRID (grid), entry, 14, 2, 2, 1);

    //-----------------------------------------//

  GtkWidget *button;

  button = gtk_button_new_with_label ("Execute 1");
  g_signal_connect (button, "clicked", G_CALLBACK (bExe), NULL);
  gtk_grid_attach (GTK_GRID (grid), button, 12, 1, 4, 1);

  button = gtk_button_new_with_label ("Execute N:");
  g_signal_connect (button, "clicked", G_CALLBACK (bExeT), NULL);
  gtk_grid_attach (GTK_GRID (grid), button, 12, 2, 2, 1);

  button = gtk_button_new_with_label ("Load Program File");
  g_signal_connect (button, "clicked", G_CALLBACK (bLoadPFile), NULL);
  gtk_grid_attach (GTK_GRID (grid), button, 12, 3, 4, 1);

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

static void activateStacks (GtkListStore *store, int stack, GtkWidget *grid, int x, int y, int ll) {

  enum stack {Index, C2, C3, C4, NUM_COLS };
  static const char *nomes[] = {"Index", "C2", "C3", "C4"};

  switch(stack){ //ESQUECIME QUE ISTO NAO DA PARA FAZER ASSIM, (AS VARIAVEIS SO ESTAO DECLARADAS DENTRO DO SWITCH...)
    case 0: { enum stack {Index, Intruction, ValueA, ValueB, NUM_COLS }; // g_print ("0\n");
      static const char *nomes[] = {"Index", "Intruction", "ValueA", "ValueB"};
      store = gtk_list_store_new (NUM_COLS, G_TYPE_INT, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT ); break; }
    case 1: { enum stack {Index, Value, Type, NUM_COLS }; // g_print ("1\n");
      static const char *nomes[] = {"Index", "Value", "Type"};
      store = gtk_list_store_new (NUM_COLS, G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING); break; }
    case 2: { enum stack {Index, PcValue, FpValue, NUM_COLS }; // g_print ("2\n");
      static const char *nomes[] = {"Index", "PcValue", "FpValue"};
      store = gtk_list_store_new (NUM_COLS, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT); break; }
    case 3: { enum stack {Index, Value, Type, NUM_COLS }; // g_print ("3\n");
      static const char *nomes[] = {"Index", "Value", "Type"};
      store = gtk_list_store_new (NUM_COLS, G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING); break; }
    default:{ g_print ("ERRO INTERFACE STACKS\n");  enum fuck {C1, C2, C3, C4, NUM_COLS };
          static const char *nomes[] = {"C1", "C2", "C3", "C4"}; break; }
  }

  GtkWidget       *view;
  GtkCellRenderer *renderer;
  GtkTreeModel    *model;

  view = gtk_tree_view_new ();
  renderer = gtk_cell_renderer_text_new ();

  for (int coluna = Index; coluna < NUM_COLS; coluna++){
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view), -1, nomes[coluna], renderer, "text", coluna, NULL);
  }

  /*
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view), -1, "Index", renderer, "text", Index, NULL);
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view), -1, "C2", renderer, "text", C2, NULL);
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view), -1, "C3", renderer, "text", C3, NULL);
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view), -1, "C4", renderer, "text", C4, NULL);
  */

  store = gtk_list_store_new (NUM_COLS, G_TYPE_INT, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT);

  model = GTK_TREE_MODEL (store);
  gtk_tree_view_set_model (GTK_TREE_VIEW (view), model);

    //-----------------------------------------//

  GtkWidget *scrolled_window;

  scrolled_window = gtk_scrolled_window_new (NULL, NULL);

  gtk_widget_set_hexpand (scrolled_window, TRUE);
  gtk_widget_set_vexpand (scrolled_window, TRUE);

  gtk_container_add (GTK_CONTAINER (scrolled_window), view);
  gtk_grid_attach (GTK_GRID (grid), scrolled_window, x, y, 3, 11);

  GtkTreeIter iter;

  for (int i=0; i<ll; i++){
    gtk_list_store_append (store, &iter);
    gtk_list_store_set (store, &iter, Index, i, C2, "teste", C3, i+i, C4, i*i, -1);
  }

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

  activateStacks (storeCode, 0, grid, 0, 1, 100);
  activateStacks (storeHeap, 1, grid, 3, 1, 2);
  activateStacks (storeOP  , 2, grid, 6, 1, 43);
  activateStacks (storeCall, 3, grid, 9, 1, 10);

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
