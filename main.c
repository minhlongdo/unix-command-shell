#include "init/init.h"
#include "util/util.h"
#include "datastructure/env.h"
#include <gtk/gtk.h>

int main(int argc, char** argv) {
  /*
  GtkWidget *terminal;

  gtk_init(&argc, &argv);

  terminal = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_widget_show(terminal);
  gtk_main();
  */

  EnvVariable* env = (EnvVariable*)malloc(sizeof(EnvVariable));
  printf("Starting Unix Command Shell.\n");
  read_env_val("profile", &env);

  printf("PATH: %s\n", env->path);
  printf("HOME: %s\n", env->home);

  free(env);

  return 0;
}
