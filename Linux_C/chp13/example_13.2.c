
#include <gtk/gtk.h>

/*«±«Ê«¶°º«ø«À°º/
void button_event(GtkWidget *widget,gpointer *data) 
{
	g_print("Button event:%s\n",(char*)data);
}

int main(int argc,char *argv[ ])
{
	GtkWidget *window;
	GtkWidget *button;

	gtk_init(&argc,&argv); /*«¢°º«≥«±«ø*/

	window=gtk_window_new(GTK_WINDOW_TOPLEVEL); /*«§«§«µ«}«§∆„«—°º/
	gtk_signal_connect(GTK_OBJECT(window),"delete_event",G_CALLBACK(gtk_main_quit),NULL);
	
	//«§«§«µ«}∆„«§«∆°E«~°u« °º«¬«±«Ê«¶°º«ø«À°º
	button=gtk_button_new_with_label("Button");
	gtk_signal_connect(GTK_OBJECT(button),"pressed",GTK_SIGNAL_FUNC(button_event),"pressed"); 
	gtk_signal_connect(GTK_OBJECT(button),"released",GTK_SIGNAL_FUNC(button_event),"released");
	gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(button_event),"clicked"); 
	gtk_signal_connect(GTK_OBJECT(button),"enter",GTK_SIGNAL_FUNC(button_event),"enter"); 
	gtk_signal_connect(GTK_OBJECT(button),"leave",GTK_SIGNAL_FUNC(button_event),"leave"); 
	
	gtk_container_add(GTK_CONTAINER(window),button);
	gtk_widget_show_all(window);

	gtk_main(); 

	return 0;
}

