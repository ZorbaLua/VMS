
#include <gtk/gtk.h> // code heap opstack call stack

// gcc -o interface interface.c $(pkg-config --cflags --libs gtk+-3.0)

//-Globais-//

GtkEntryBuffer *buffer;
GtkWidget *window;

GtkListStore *storeCode, *storeHeap, *storeOP, *storeCall;

//-----------------------------------------------------------------------------//

static void bExe (GtkWidget *widget, gpointer data) {
  g_print ("Click Executar\n");
}

static void bExeT (GtkWidget *widget, gpointer data) {
  gtk_entry_buffer_get_text(buffer);
  g_print ("Click Executar N\n");
}

static void bLoadPFile (GtkWidget *widget, gpointer data) {
  g_print ("Click Load Programa\n");
}

static void bLoadIFile (GtkWidget *widget, gpointer data) {
  g_print ("Click Load Input\n");
}

//-----------------------------------------------------------------------------//

static void activateInputs (GtkWidget *grid) {

  GtkWidget *entry;

  buffer = gtk_entry_buffer_new ("-1", 25);
  entry = gtk_entry_new_with_buffer (buffer);
  gtk_grid_attach (GTK_GRID (grid), entry, 6, 2, 1, 1);

    //-----------------------------------------//

  GtkWidget *button;

  button = gtk_button_new_with_label ("Execute 1");
  g_signal_connect (button, "clicked", G_CALLBACK (bExe), NULL);
  gtk_grid_attach (GTK_GRID (grid), button, 5, 1, 2, 1);

  button = gtk_button_new_with_label ("Execute N:");
  g_signal_connect (button, "clicked", G_CALLBACK (bExeT), NULL);
  gtk_grid_attach (GTK_GRID (grid), button, 5, 2, 1, 1);

  button = gtk_button_new_with_label ("Load Program File");
  g_signal_connect (button, "clicked", G_CALLBACK (bLoadPFile), NULL);
  gtk_grid_attach (GTK_GRID (grid), button, 5, 3, 2, 1);

  button = gtk_button_new_with_label ("Load Input File");
  g_signal_connect (button, "clicked", G_CALLBACK (bLoadIFile), NULL);
  gtk_grid_attach (GTK_GRID (grid), button, 5, 4, 2, 1);

    //-----------------------------------------//

  GtkWidget *scrolled_window;
  GtkWidget *view;

  scrolled_window = gtk_scrolled_window_new (NULL, NULL);

  gtk_widget_set_hexpand (scrolled_window, TRUE);
  gtk_widget_set_vexpand (scrolled_window, TRUE);

  view = gtk_text_view_new ();

  gtk_text_view_set_editable (GTK_TEXT_VIEW (view), TRUE);
  gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW (view), TRUE);

  gtk_container_add (GTK_CONTAINER (scrolled_window), view);

  gtk_grid_attach (GTK_GRID (grid), scrolled_window, 5, 5, 2, 1);

}

//-----------------------------------------------------------------------------//

static void activateStacks (GtkListStore *store, GtkWidget *grid, int x, int y) {

  enum { C1, C2, C3, C4, NUM_COLS };

  GtkWidget       *view;
  GtkCellRenderer *renderer;
  GtkTreeModel    *model;

  view = gtk_tree_view_new ();

  renderer = gtk_cell_renderer_text_new ();
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view), -1, "C1", renderer, "text", C1, NULL);
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view), -1, "C2", renderer, "text", C2, NULL);
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view), -1, "C3", renderer, "text", C3, NULL);
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view), -1, "C4", renderer, "text", C4, NULL);

  store = gtk_list_store_new (NUM_COLS, G_TYPE_INT, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT);

  model = GTK_TREE_MODEL (store);
  gtk_tree_view_set_model (GTK_TREE_VIEW (view), model);

    //-----------------------------------------//

  GtkWidget *scrolled_window;

  scrolled_window = gtk_scrolled_window_new (NULL, NULL);

  gtk_widget_set_hexpand (scrolled_window, TRUE);
  gtk_widget_set_vexpand (scrolled_window, TRUE);

  gtk_container_add (GTK_CONTAINER (scrolled_window), view);
  gtk_grid_attach (GTK_GRID (grid), scrolled_window, x, y, 1, 5);

  GtkTreeIter iter;

  for (int i=0; i<50; i++){
    gtk_list_store_append (store, &iter);
    gtk_list_store_set (store, &iter, C1, i, C2, "a", C3, i+i, C4, i*i, -1);
  }

}

//-----------------------------------------------------------------------------//

static void activate (GtkApplication *app, gpointer user_data) {

  GtkWidget *grid;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "VMS-Projeto");
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  grid = gtk_grid_new ();
  gtk_container_add (GTK_CONTAINER (window), grid);
  gtk_grid_set_row_spacing (GTK_GRID (grid),10);
  gtk_grid_set_column_spacing (GTK_GRID (grid),10);

    //-----------------------------------------//

  activateInputs (grid);

    //-----------------------------------------//

  activateStacks (storeCode, grid, 1, 1);
  activateStacks (storeCode, grid, 2, 1);
  activateStacks (storeCode, grid, 3, 1);
  activateStacks (storeCode, grid, 4, 1);

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
