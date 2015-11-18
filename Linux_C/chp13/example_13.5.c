
#define GTK_ENABLE_BROKEN
#include <gtk/gtk.h>

static void entry_toggle_visibility( GtkWidget *checkbutton,
                                     GtkWidget *entry )
{
  gtk_entry_set_visibility (GTK_ENTRY (entry),
			    GTK_TOGGLE_BUTTON (checkbutton)->active);
}

void text_toggle_editable (GtkWidget *checkbutton,
			   GtkWidget *text)
{
  gtk_text_set_editable (GTK_TEXT (text),
			 GTK_TOGGLE_BUTTON (checkbutton)->active);
}

int main( int   argc,char *argv[] )
{

    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *entry;
    GtkWidget *vscrollbar;
  	GtkWidget *text;
  	GtkWidget *table;
  	GtkWidget *check;

    gtk_init (&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Demo_Entry_Text");
    g_signal_connect (G_OBJECT (window), "destroy",G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect_swapped (G_OBJECT (window), "delete_event", G_CALLBACK (gtk_widget_destroy), G_OBJECT (window));

    vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add (GTK_CONTAINER (window), vbox);
		
		entry = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (entry), 30);
    gtk_entry_set_text(GTK_ENTRY (entry), "hello");
    gtk_box_pack_start (GTK_BOX (vbox), entry, TRUE, TRUE, 0);
		
		check = gtk_check_button_new_with_label ("Visible");
    gtk_box_pack_start (GTK_BOX (vbox), check, TRUE, TRUE, 0);
    g_signal_connect (G_OBJECT (check), "toggled",
	              G_CALLBACK (entry_toggle_visibility), (gpointer) entry);
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (check), TRUE);
    
    
		table = gtk_table_new (2, 2, FALSE);
  	gtk_box_pack_start (GTK_BOX (vbox), table, TRUE, TRUE, 0);
  	
		text = gtk_text_new (NULL, NULL);
  	gtk_text_set_editable (GTK_TEXT (text), TRUE);
  	gtk_table_attach (GTK_TABLE (table), text, 0, 1, 0, 1,
		    GTK_EXPAND | GTK_SHRINK | GTK_FILL,
		    GTK_EXPAND | GTK_SHRINK | GTK_FILL, 0, 0);

		vscrollbar = gtk_vscrollbar_new (GTK_TEXT (text)->vadj);
  	gtk_table_attach (GTK_TABLE (table), vscrollbar, 1, 2, 0, 1,
		    GTK_FILL, GTK_EXPAND | GTK_SHRINK | GTK_FILL, 0, 0);
    
    check = gtk_check_button_new_with_label ("Editable");
  	gtk_box_pack_start (GTK_BOX (vbox), check, FALSE, FALSE, 0);
  	g_signal_connect (G_OBJECT (check), "toggled",
                    G_CALLBACK (text_toggle_editable), text);
 	  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (check), TRUE);


		gtk_widget_show_all(window);
		gtk_main();

	return 0;
}
