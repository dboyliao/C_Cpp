
#include <gtk/gtk.h>

void file_ok_sel( GtkWidget *w,GtkFileSelection *fs )
{
    g_print ("%s\n", gtk_file_selection_get_filename (GTK_FILE_SELECTION (fs)));
}

int main( int   argc,char *argv[] )
{
    GtkWidget *filesel;
    
    gtk_init (&argc, &argv);

    filesel = gtk_file_selection_new ("File selection");
    
    g_signal_connect (G_OBJECT (filesel), "destroy",G_CALLBACK (gtk_main_quit), NULL);

    g_signal_connect (G_OBJECT (GTK_FILE_SELECTION (filesel)->ok_button),
		      "clicked", G_CALLBACK (file_ok_sel), (gpointer) filesel);
    
    g_signal_connect_swapped (G_OBJECT (GTK_FILE_SELECTION (filesel)->cancel_button),
	                      "clicked", G_CALLBACK (gtk_widget_destroy),G_OBJECT (filesel));
    
    gtk_file_selection_set_filename(GTK_FILE_SELECTION(filesel), "gnome.png");
    
    gtk_widget_show(filesel);
    gtk_main();
    return 0;
}
