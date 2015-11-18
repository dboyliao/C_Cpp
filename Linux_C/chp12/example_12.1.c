
#include <gtk/gtk.h>
int main( int   argc, char *argv[] )
{
    	GtkWidget *window;
     
		gtk_init(&argc, &argv);
     
		window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
		g_signal_connect(G_OBJECT(window),"delete_event",
G_CALLBACK(gtk_main_quit),NULL);
		gtk_window_set_title(GTK_WINDOW(window),"Hello World!");
		gtk_widget_show(window);
     
		gtk_main();
     
		return 0;
}
