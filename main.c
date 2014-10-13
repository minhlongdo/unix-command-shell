#include "init/init.h"
#include <gtk/gtk.h>

int main(int argc, char** argv) {
  GtkWidget *terminal;

  gtk_init(&argc, &argv);

  terminal = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_widget_show(terminal);
  gtk_main();

  return 0;
}
