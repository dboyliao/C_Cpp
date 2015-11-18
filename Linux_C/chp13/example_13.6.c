
#include <gtk/gtk.h>

void button_event(GtkWidget *widget, gpointer *data);
void show_info_dialog(GtkWidget *widget, gpointer window);
void show_warning_dialog(GtkWidget *widget, gpointer window);

int main(int argc,char *argv[])
{
	GtkWidget *window;
	GtkWidget *button;
	GtkWidget *v_box;

	gtk_init(&argc,&argv);
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_signal_connect(GTK_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL); 

	v_box = gtk_vbox_new(FALSE,6);
  gtk_container_add(GTK_CONTAINER(window),v_box);
	
	button=gtk_button_new_with_label("Exit");
	gtk_box_pack_start(GTK_BOX(v_box),button,TRUE,TRUE,0);
	gtk_signal_connect(GTK_OBJECT(button),"clicked",G_CALLBACK(button_event),NULL);
	gtk_widget_show(button);
	
	button = gtk_button_new_with_label("Infor");
	gtk_box_pack_start(GTK_BOX(v_box),button,TRUE,TRUE,0);
	g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(show_info_dialog), (gpointer) window); 
	gtk_widget_show(button);
	
  button = gtk_button_new_with_label("Warning");	
  gtk_box_pack_start(GTK_BOX(v_box),button,TRUE,TRUE,0);
  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(show_warning_dialog), (gpointer) window); 
	gtk_widget_show(button);
 
	gtk_widget_show_all(window);
	gtk_main();

}

void destroy(GtkWidget *widget, gpointer *data)
{
    gtk_widget_destroy(GTK_WIDGET(data));
}

void button_event(GtkWidget *widget, gpointer *data)
{
    GtkWidget *dialog;
		GtkWidget *button;

    dialog=gtk_dialog_new();
    gtk_window_set_title(GTK_WINDOW(dialog), "Normal Dialog");
    
    button=gtk_button_new_with_label("Yes");
		gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->action_area),button,TRUE,TRUE,0);
    gtk_signal_connect(GTK_OBJECT(button),"clicked",G_CALLBACK(gtk_main_quit),NULL);
    gtk_widget_show(button);
    
    button=gtk_button_new_with_label("No");
    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->action_area),button,TRUE,TRUE,0);
    gtk_signal_connect(GTK_OBJECT(button),"clicked",G_CALLBACK(destroy),dialog);
    gtk_widget_show(button);
    
		gtk_widget_show(dialog);

}
void show_info_dialog(GtkWidget *widget, gpointer window)
{
  GtkWidget *dialog;
  dialog = gtk_message_dialog_new(window,
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            "Information to Show", "title");
  gtk_window_set_title(GTK_WINDOW(dialog), "Information");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
}

void show_warning_dialog(GtkWidget *widget, gpointer window)
{
  GtkWidget *dialog;
  dialog = gtk_message_dialog_new(window,
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_OK,
            "Warning Information");
  gtk_window_set_title(GTK_WINDOW(dialog), "Warning");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
}

