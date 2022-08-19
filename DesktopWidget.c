
#include<gtk/gtk.h>

//_________________________________________________________________________________________________

GtkWidget *window;
GtkWidget *workArea;

GtkWidget *bClose;

GdkVisual *visual;
GdkScreen *screen;

GtkWidget *dialog;

FILE *fp;

int res, t_out=0;

gulong e_hid, l_hid;

//_________________________________________________________________________________________________

void terminal()
{
	fp = popen("gnome-terminal", "r");
}

void lock()
{
	fp = popen("gnome-lock", "r");
}

void restart()
{
	dialog = gtk_dialog_new_with_buttons("Are you sure?", GTK_WINDOW(window), GTK_DIALOG_MODAL, 						"_Yes", GTK_RESPONSE_ACCEPT, "_No", GTK_RESPONSE_REJECT, NULL);
	res = gtk_dialog_run(GTK_DIALOG(dialog));
	
	if(res == GTK_RESPONSE_ACCEPT)
		fp = popen("reboot", "r");
	gtk_widget_destroy(dialog);
}

void poweroff()
{
	dialog = gtk_dialog_new_with_buttons("Are you sure?", GTK_WINDOW(window), GTK_DIALOG_MODAL, 						"_Yes", GTK_RESPONSE_ACCEPT, "_No", GTK_RESPONSE_REJECT, NULL);
//	gtk_message_dialog_set_markup(GTK_MESSAGE_DIALOG(dialog), "Are You Sure?");
	res = gtk_dialog_run(GTK_DIALOG(dialog));
	
	if(res == GTK_RESPONSE_ACCEPT)
		fp = popen("poweroff", "r");	
	gtk_widget_destroy(dialog);
}

//_________________________________________________________________________________________________

void trans(GtkWidget *widget)
{
	gtk_widget_set_app_paintable(widget, TRUE);
	screen = gtk_widget_get_screen(widget);
	visual = gdk_screen_get_rgba_visual(screen);
	gtk_widget_set_visual(widget, visual);
	//gtk_widget_set_opacity(window, 0.5);
}

void hide()
{
	//printf("in hide\n");
	gtk_widget_set_visible(bClose, FALSE);
	gtk_widget_set_opacity(window, 0.5);
}

gboolean incr()
{
	t_out+=1;
	//printf("t_out: %d\n", t_out);
	if(t_out>=3)
	{
		t_out=0;
		hide();
		//return FALSE;
	}
	return TRUE;
}

void show()
{
	//printf("in show\n");
	gtk_widget_set_visible(bClose, TRUE);
	gtk_widget_set_opacity(window, 1.0);
}

void opq()
{
	gtk_widget_set_opacity(window, 1.0);
	gtk_widget_show(bClose);
}

void tra()
{
	//e_hid = g_signal_connect_object(G_OBJECT(window), "enter-notify-event", G_CALLBACK(show), NULL, G_CONNECT_AFTER);
	//l_hid = g_signal_connect_object(G_OBJECT(window), "leave-notify-event", G_CALLBACK(hide), NULL, G_CONNECT_AFTER);
	gtk_widget_set_opacity(window, 0.5);
	gtk_widget_hide(bClose);
}

//_________________________________________________________________________________________________

int main()
{
	gtk_init(NULL,NULL);

	GtkWidget *iTerminal, *iPowerOff, *iRestart, *iSysLock;
	GtkWidget *bTerminal, *bPowerOff, *bRestart, *bSysLock;
//-------------------------------------------------------------------------------------------------
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_move(GTK_WINDOW(window), 1150, 50);
	gtk_container_set_border_width (GTK_CONTAINER(window), 5);
	gtk_window_set_decorated(GTK_WINDOW(window), FALSE);
	gtk_window_set_default_size(GTK_WINDOW(window), 160, 150);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	gtk_window_set_modal(GTK_WINDOW(window), TRUE);
	
	trans(window);
	
	e_hid = g_signal_connect_object(G_OBJECT(window), "enter-notify-event", G_CALLBACK(show), NULL, G_CONNECT_AFTER);
	//l_hid = g_signal_connect_object(G_OBJECT(window), "leave-notify-event", G_CALLBACK(hide), NULL, G_CONNECT_AFTER);
	
	workArea = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window), workArea);
//-------------------------------------------------------------------------------------------------
	iTerminal = gtk_image_new_from_file("/home/aditya/workspace/SystemProgramming/img/terminal.png");
	iPowerOff = gtk_image_new_from_file("/home/aditya/workspace/SystemProgramming/img/poweroff.png");
	iRestart = gtk_image_new_from_file("/home/aditya/workspace/SystemProgramming/img/restart.png");
	iSysLock = gtk_image_new_from_file("/home/aditya/workspace/SystemProgramming/img/lock.png");
//-------------------------------------------------------------------------------------------------
	bTerminal = gtk_button_new_with_label(NULL);
	gtk_button_set_image(GTK_BUTTON(bTerminal), iTerminal);
	gtk_fixed_put(GTK_FIXED(workArea), bTerminal, 5, 5);
	g_signal_connect(G_OBJECT(bTerminal), "clicked", G_CALLBACK(terminal), NULL);
	g_signal_connect(G_OBJECT(bTerminal), "enter", G_CALLBACK(opq), bTerminal);
	//g_signal_connect(G_OBJECT(bTerminal), "leave", G_CALLBACK(tra), bTerminal);

	bSysLock = gtk_button_new_with_label(NULL);
	gtk_button_set_image(GTK_BUTTON(bSysLock), iSysLock);
	gtk_fixed_put(GTK_FIXED(workArea), bSysLock, 80, 5);
	g_signal_connect(G_OBJECT(bSysLock), "clicked", G_CALLBACK(lock), NULL);
	g_signal_connect(G_OBJECT(bSysLock), "enter", G_CALLBACK(opq), NULL);
	//g_signal_connect(G_OBJECT(bSysLock), "leave", G_CALLBACK(tra), bTerminal);

	bRestart = gtk_button_new_with_label(NULL);
	gtk_button_set_image(GTK_BUTTON(bRestart), iRestart);
	gtk_fixed_put(GTK_FIXED(workArea), bRestart, 10, 80);
	g_signal_connect(G_OBJECT(bRestart), "clicked", G_CALLBACK(restart), NULL);
	g_signal_connect(G_OBJECT(bRestart), "enter", G_CALLBACK(opq), NULL);
	//g_signal_connect(G_OBJECT(bRestart), "leave", G_CALLBACK(tra), bTerminal);
	
	bPowerOff = gtk_button_new_with_label(NULL);
	gtk_button_set_image(GTK_BUTTON(bPowerOff), iPowerOff);
	gtk_fixed_put(GTK_FIXED(workArea), bPowerOff, 80, 80);
	g_signal_connect(G_OBJECT(bPowerOff), "clicked", G_CALLBACK(poweroff), NULL);
	g_signal_connect(G_OBJECT(bPowerOff), "enter", G_CALLBACK(opq), NULL);
	//g_signal_connect(G_OBJECT(bPowerOff), "leave", G_CALLBACK(tra), bTerminal);

	bClose = gtk_button_new_with_label("X");
	gtk_fixed_put(GTK_FIXED(workArea), bClose, 160, 5);
	g_signal_connect(G_OBJECT(bClose), "clicked", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(G_OBJECT(bClose), "enter", G_CALLBACK(opq), NULL);
	//g_signal_connect(G_OBJECT(bClose), "leave", G_CALLBACK(tra), bTerminal);
//-------------------------------------------------------------------------------------------------
	gtk_widget_show_all(window);
	gtk_widget_hide(bClose);
	g_timeout_add_seconds(3, incr, NULL);	
//-------------------------------------------------------------------------------------------------
	gtk_main();
	return 0;
}

