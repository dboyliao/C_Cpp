// example_13.8.3.c

#include <gtk/gtk.h>
	
int main(int argc,char *argv[ ])
{
	GtkWidget *window, *notebook;
	GtkWidget *label;

	gtk_init(&argc,&argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_signal_connect(GTK_OBJECT(window),"delete_event",G_CALLBACK(gtk_main_quit),NULL);

	notebook = gtk_notebook_new();
	gtk_container_add(GTK_CONTAINER(window),notebook);

	label = gtk_label_new("Content of Page 1.");
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook),label,NULL);

	label = gtk_label_new("Content of Page 2.");
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook),label,NULL);

	label = gtk_label_new("Content of Page 3.");
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook),label,NULL);

	gtk_widget_show_all(window);
	gtk_main(); 

	return 0;
}
