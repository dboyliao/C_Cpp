
#include <gtk/gtk.h>
	
int main(int argc,char *argv[ ])
{
	GtkWidget *window, *paned1, *paned2, *paned3;
	GtkWidget *button;

	gtk_init(&argc,&argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_signal_connect(GTK_OBJECT(window),"delete_event",G_CALLBACK(gtk_main_quit),NULL);

	paned1 = gtk_vpaned_new();
	gtk_container_add(GTK_CONTAINER(window), paned1);

	paned2 = gtk_hpaned_new();
	gtk_paned_add1(GTK_PANED(paned1),paned2);

	button = gtk_button_new_with_label("Button1");
	gtk_paned_add2(GTK_PANED(paned1),button);

	button = gtk_button_new_with_label("Button2");
	gtk_paned_add1(GTK_PANED(paned2),button);

	paned3 = gtk_vpaned_new();
	gtk_paned_add2(GTK_PANED(paned2),paned3);

	button = gtk_button_new_with_label("Button3");
	gtk_paned_add1(GTK_PANED(paned3),button);

	button = gtk_button_new_with_label("Button4");
	gtk_paned_add2(GTK_PANED(paned3),button);

	gtk_widget_show_all(window);
	gtk_main(); 

	return 0;
}
