/* 
 * @FILENAME    cb-gui.c
 * @DESCRIPTION functions about gui
 * @AUTHOR      hejiyan
 * @VERSION     0.1
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "main.h"
#include "cb-gui.h"

extern cb_db_dataset Dat;

GtkWidget *g_txt_start_time,
          *g_txt_end_time,
          *g_txt_del_id,
          *g_txt_time,
          *g_txt_money,
          *g_txt_text,
          *g_text_display;

/*
 * helper functions
 */
void insert_text_without_ln(const gchar* text, GtkWidget *w)
{
	GtkTextBuffer *buffer;
	GtkTextMark *mark;
    GtkTextIter iter;

    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (w));

    mark = gtk_text_buffer_get_insert (buffer);
    gtk_text_buffer_get_iter_at_mark (buffer, &iter, mark);
    gtk_text_buffer_insert (buffer, &iter, text, -1);
}

void insert_text(const gchar* text, GtkWidget *w)
{
	insert_text_without_ln(text, w);
	//insert_text_without_ln("\n", w);
}

void clear_text(GtkWidget* w)
{
	GtkTextBuffer *buffer;

    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (w));

    gtk_text_buffer_set_text (buffer, "", -1);
}

void display_db(time_t start_time, time_t end_time)
{
	char buff[2*MAX_TEXT_LEN];
	clear_text(g_text_display);

	char time_str[MAX_TEXT_LEN];
	int i = 0;
	int total = 0;

	sprintf(buff, "* [id]                [time]                      [money]     [text]\n");
	insert_text(buff, g_text_display);

	for (node* p = Dat.head; p ; p = p -> next)
	{
		time_t pt = p->v->time;
		if (start_time <= pt && pt <= end_time)
		{
			time_to_str(p->v->time, time_str);
			sprintf(buff, "* [%3d] | %s | %15d | %20s\n", i, time_str, p->v->money, p->v->text);
			insert_text(buff, g_text_display);
		}
		i++;
		total += p->v->money;
	}

	sprintf(buff, "* Items: %d, Total money: %d.\n", Dat.n, total);
	insert_text(buff, g_text_display);
}

void display_db_default()
{
	display_db(0, UINT_MAX);
}
/*
 * signal functions 
 */

void on_btn_query_clicked()
{
	const gchar* s_start_time = gtk_entry_get_text(GTK_ENTRY(g_txt_start_time));
	const gchar* s_end_time = gtk_entry_get_text(GTK_ENTRY(g_txt_end_time));
	

	time_t t1, t2;
	if (s_start_time[0] == '0') t1 = 0;
	else t1 = str_to_time(s_start_time);
	
	if (s_end_time[0] == '0') t2 = UINT_MAX;
	else t2 = str_to_time(s_end_time);

	display_db(t1, t2);
}

void on_btn_del_clicked()
{
	const gchar* s_del_id = gtk_entry_get_text(GTK_ENTRY(g_txt_del_id));
	int id;
	if ( 1 == sscanf(s_del_id, "%d", &id))
	{
		del_item(id);
		on_btn_query_clicked();
	}
}

void on_btn_add_clicked()
{
	const gchar* s_time = gtk_entry_get_text(GTK_ENTRY(g_txt_time));
	const gchar* s_money = gtk_entry_get_text(GTK_ENTRY(g_txt_money));
	const gchar* s_text = gtk_entry_get_text(GTK_ENTRY(g_txt_text));

	time_t add_time;
	if (s_time[0] == '0') add_time = get_cur_time();
	else add_time = str_to_time(s_time);
	int money;
	if (1 == sscanf(s_money, "%d", &money))
	{
		add_item(add_time, money, s_text);
		on_btn_query_clicked();
	}
}

void on_window_main_destroy()
{
    gtk_main_quit();
    exit(0);
}

/*
 * gui main
 */
void cb_gui_init(int argc, char *argv[])
{
    GtkBuilder      *builder; 
    GtkWidget       *window;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "res/main.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    
    //connect signal functions
    gtk_builder_connect_signals(builder, NULL);
    
    //get some points
    g_txt_start_time = GTK_WIDGET (gtk_builder_get_object(builder, "txt_start_time"));
    g_txt_end_time   = GTK_WIDGET (gtk_builder_get_object(builder, "txt_end_time"));
    g_txt_del_id     = GTK_WIDGET (gtk_builder_get_object(builder, "txt_del_id"));
    g_txt_time       = GTK_WIDGET (gtk_builder_get_object(builder, "txt_time"));
    g_txt_money      = GTK_WIDGET (gtk_builder_get_object(builder, "txt_money"));
    g_txt_text       = GTK_WIDGET (gtk_builder_get_object(builder, "txt_text"));
    g_text_display   = GTK_WIDGET (gtk_builder_get_object(builder, "text_display"));

    //set some default value
    char time_str[MAX_TEXT_LEN];
    time_to_str(get_cur_time(), time_str);
    gtk_entry_set_text (GTK_ENTRY(g_txt_start_time), "2016/01/01-00:00:00");
    gtk_entry_set_text (GTK_ENTRY(g_txt_end_time), "0");
    gtk_entry_set_text (GTK_ENTRY(g_txt_time), "0");
    gtk_entry_set_text (GTK_ENTRY(g_txt_money), "100");
    gtk_entry_set_text (GTK_ENTRY(g_txt_text), "some reason");

    g_object_unref (builder);

    gtk_widget_show (window);                
    gtk_main();
}
