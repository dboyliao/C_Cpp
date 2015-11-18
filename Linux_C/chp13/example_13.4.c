
#include<gtk/gtk.h>

int main(int argc, char **argv)
{
    GtkWidget *window;
    GtkWidget *image;
    GtkWidget *v_box;
    
    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

		v_box = gtk_vbox_new(FALSE,0);
    gtk_container_add(GTK_CONTAINER(window),v_box);
	
    image = gtk_image_new_from_file("gnome.png");
    gtk_box_pack_start(GTK_BOX(v_box),image,TRUE,TRUE,0);

		image = gtk_image_new_from_stock(GTK_STOCK_HELP,GTK_ICON_SIZE_MENU);
		gtk_box_pack_start(GTK_BOX(v_box),image,TRUE,TRUE,0);
		
    gtk_widget_show_all(window);
    gtk_main();
    
    return 0;
}
