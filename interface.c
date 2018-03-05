
#include <gtk/gtk.h>

enum { C1, C2, C3, C4, NUM_COLS } ;

static void bExe (GtkWidget *widget, gpointer data) {
  g_print ("Click Executar\n");
}

static void bExeT (GtkWidget *widget, gpointer data) {
  g_print ("Click Executar Tudo\n");
}

static void bLoadFile (GtkWidget *widget, gpointer data) {
  g_print ("Click Executar Ficheiros\n");
}

//-----------------------------------------------------------------------------//

static void activate (GtkApplication *app, gpointer user_data) {

  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;

    //-----------------//

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

    //-----------------//

  grid = gtk_grid_new ();
  gtk_container_add (GTK_CONTAINER (window), grid);

    //-----------------//

  button = gtk_button_new_with_label ("Execute");
  g_signal_connect (button, "clicked", G_CALLBACK (bExe), NULL);
  gtk_grid_attach (GTK_GRID (grid), button, 0, 0, 1, 1);

  button = gtk_button_new_with_label ("Execute All");
  g_signal_connect (button, "clicked", G_CALLBACK (bExeT), NULL);
  gtk_grid_attach (GTK_GRID (grid), button, 0, 1, 1, 1);

  button = gtk_button_new_with_label ("Load File");
  g_signal_connect (button, "clicked", G_CALLBACK (bLoadFile), NULL);
  gtk_grid_attach (GTK_GRID (grid), button, 0, 2, 1, 1);

    //-----------------//

  GtkListStore* store;
  GtkTreeIter   iter;

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

  gtk_list_store_append (store, &iter);
	gtk_list_store_set (store, &iter, C1, 1, C2, "a", C3, 1, C4, 1, -1);
  gtk_list_store_append (store, &iter);
	gtk_list_store_set (store, &iter, C1, 2, C2, "b", C3, 2, C4, 2, -1);

  model = GTK_TREE_MODEL (store);
  gtk_tree_view_set_model (GTK_TREE_VIEW (view), model);

  gtk_grid_attach (GTK_GRID (grid), view, 1, 0, 1, 1);

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

// Tirar a grid porque nao vai funcionar
