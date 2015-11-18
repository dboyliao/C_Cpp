
#include <gtk/gtk.h>

//«¶√º°º«Ê«¶°º«ø«À°º
void click_button(GtkWidget *widget,gpointer *data)
{
		g_print("%s ",(char *)data);
		if(GTK_TOGGLE_BUTTON(widget)->active)
			g_print("state is active\n");
    	else
	    	g_print("state is not active\n");
}
int main(int argc,char **argv)
{ 
	GtkWidget  *window;
	GtkWidget       *v_box;
	GSList          *group;
	GtkWidget       *check,*radio;
	gtk_init(&argc,&argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_signal_connect(GTK_OBJECT(window),"delete_event",G_CALLBACK(gtk_main_quit),NULL);
	
	gtk_container_border_width(GTK_CONTAINER(window),60);
	//« °º« «›«±«´°º«≠«‰«|v_box«…«Ô««°º
	v_box = gtk_vbox_new(FALSE,0);
    gtk_container_add(GTK_CONTAINER(window),v_box);
	//«›«‡«⁄«¿« °º« «Ω«µ«´°ºheck∆„«§«∆°E°v«ﬂ«µ«•«Œ°º«»«≥«ﬁ«…°º«µv_box«…«Ô««°º«€
    check = gtk_check_button_new_with_label("Check Button1");
    g_signal_connect(GTK_OBJECT(check),"clicked",GTK_SIGNAL_FUNC(click_button),"check button1");
    gtk_box_pack_start(GTK_BOX(v_box),check,TRUE,TRUE,0);
	gtk_widget_show(check);
    check = gtk_check_button_new_with_label("Check Button2");
	g_signal_connect(GTK_OBJECT(check),"clicked",GTK_SIGNAL_FUNC(click_button),"check button2");
    gtk_box_pack_start(GTK_BOX(v_box),check,TRUE,TRUE,0);
    gtk_widget_show(check);
	//«›«‡«⁄«¿« °º« 3«´°ºadio∆„«§«∆°E 
radio = gtk_radio_button_new_with_label(NULL,"Red");
    g_signal_connect(GTK_OBJECT(radio),"clicked",GTK_SIGNAL_FUNC(click_button),"Red");    
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio),TRUE);    
	gtk_box_pack_start(GTK_BOX(v_box),radio,TRUE,TRUE,0);
	gtk_widget_show(radio);group = gtk_radio_button_group(GTK_RADIO_BUTTON(radio));
	radio = gtk_radio_button_new_with_label(group,"Yellow");
	g_signal_connect(GTK_OBJECT(radio),"clicked",GTK_SIGNAL_FUNC(click_button),"Yellow");
	gtk_box_pack_start(GTK_BOX(v_box),radio,TRUE,TRUE,0);
	gtk_widget_show(radio);
	group = gtk_radio_button_group(GTK_RADIO_BUTTON(radio));
	radio = gtk_radio_button_new_with_label(group,"Green");
	g_signal_connect(GTK_OBJECT(radio),"clicked",GTK_SIGNAL_FUNC(click_button),"Green");
  gtk_box_pack_start(GTK_BOX(v_box),radio,TRUE,TRUE,0);
    
	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
