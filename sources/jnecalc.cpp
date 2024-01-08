// aplikasi_fullscreen.cpp
#include <gtk/gtk.h>

static void on_window_closed(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "KALKULATOR JNE PACKING KAYU GTK+");

    g_signal_connect(window, "destroy", G_CALLBACK(on_window_closed), NULL);

    GdkScreen *screen = gtk_window_get_screen(GTK_WINDOW(window));
    gint screen_width = gdk_screen_get_width(screen);
    gint screen_height = gdk_screen_get_height(screen);

    gtk_window_fullscreen(GTK_WINDOW(window));

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
