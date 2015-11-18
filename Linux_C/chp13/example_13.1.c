
#include <gtk/gtk.h>

int main(int argc, char *argv[])
{
  static GtkWidget *window = NULL;
  GtkWidget *main_vbox;
  GtkWidget *frame;
  GtkWidget *label;

  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  g_signal_connect(G_OBJECT (window), "destroy",G_CALLBACK (gtk_main_quit),NULL);
	gtk_window_set_title(GTK_WINDOW(window), "Label Demo");
	main_vbox = gtk_vbox_new(TRUE, 6);
  gtk_container_set_border_width (GTK_CONTAINER (main_vbox), 20);
  
	label = gtk_label_new ("Hello Label!");
  gtk_box_pack_start (GTK_BOX (main_vbox), label, FALSE, FALSE, 0);
  
	frame = gtk_frame_new ("Normal Label");
	label = gtk_label_new ("This is a Normal label");
	gtk_container_add (GTK_CONTAINER (frame), label);
  gtk_box_pack_start (GTK_BOX (main_vbox), frame, FALSE, FALSE, 0);

	frame = gtk_frame_new ("Multi-line Label");
  label = gtk_label_new ("This is a Multi-line label.\nSecond line.\nThird line.");
  gtk_container_add (GTK_CONTAINER (frame), label);
  gtk_box_pack_start (GTK_BOX (main_vbox), frame, FALSE, FALSE, 0);

	frame = gtk_frame_new ("Line wrapped label");
  label = gtk_label_new ("This is an example of a line-wrapped label. It " \
			 "should not be taking up the entire             " \
			 "width allocated to it, but automatically " \
			 "wraps the words to fit.  ");
  gtk_label_set_line_wrap (GTK_LABEL (label), TRUE);
  gtk_container_add (GTK_CONTAINER (frame), label);
  gtk_box_pack_start (GTK_BOX (main_vbox), frame, FALSE, FALSE, 0);

  gtk_container_add (GTK_CONTAINER (window), main_vbox);
	gtk_widget_show_all(window);
	gtk_main(); 
	return 0;
}

