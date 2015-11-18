
#include <stdio.h>
#include <gtk/gtk.h>

int main( int   argc,char *argv[] )
{

    GtkWidget *window;
    GtkWidget *h_box;
    GtkWidget *menu_item,*root_menuitem;
    GtkWidget *menu;
    GtkWidget *menu_bar;

		gtk_init(&argc,&argv);
		window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
		gtk_widget_set_usize(window,400,200);
		g_signal_connect(GTK_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);

		h_box=gtk_vbox_new(FALSE,5);
		gtk_container_add(GTK_CONTAINER(window),h_box);

		menu_bar=gtk_menu_bar_new();
		gtk_box_pack_start(GTK_BOX(h_box),menu_bar,FALSE,TRUE,0);
	
		menu = gtk_menu_new();
		menu_item = gtk_menu_item_new_with_label("Open");
		gtk_menu_append(GTK_MENU(menu), menu_item);
    menu_item = gtk_menu_item_new_with_label("Save");
    gtk_menu_append(GTK_MENU(menu), menu_item);
    menu_item = gtk_menu_item_new_with_label("Quit");
    gtk_menu_append(GTK_MENU(menu), menu_item);
    g_signal_connect(GTK_OBJECT(menu_item),"activate",G_CALLBACK(gtk_main_quit),NULL);
    
		root_menuitem = gtk_menu_item_new_with_label("File");
		gtk_menu_item_set_submenu (GTK_MENU_ITEM (root_menuitem),menu);				
		gtk_menu_bar_append(GTK_MENU_BAR (menu_bar), root_menuitem);
		
		root_menuitem = gtk_menu_item_new_with_label("Edit");
		gtk_menu_bar_append(GTK_MENU_BAR (menu_bar), root_menuitem);
		root_menuitem = gtk_menu_item_new_with_label("Help");
		gtk_menu_bar_append(GTK_MENU_BAR (menu_bar), root_menuitem);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
