#include "code_editor.h"
#include <stdio.h>
code_editor_t editor;
static void code_text_buffer_changed(GtkWidget *widget, GdkEventKey *event);
static gboolean code_key_pressed(GtkWidget *widget, GdkEventKey *event);
static void init_code()
{
	editor.code_view.textview = gtk_builder_get_object(editor.builder, "code_view");
	editor.code_view.buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(editor.code_view.textview));
	editor.analysis.textview = gtk_builder_get_object(editor.builder, "analysis");
	editor.analysis.buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(editor.analysis.textview));
	g_signal_connect(GTK_TEXT_BUFFER(editor.code_view.buffer), "changed", G_CALLBACK(code_text_buffer_changed), NULL);
	g_signal_connect(GTK_TEXT_VIEW(editor.code_view.textview), "key-press-event", G_CALLBACK(code_key_pressed), NULL);
}

static void init_app()
{
	editor.window = gtk_builder_get_object(editor.builder, "window");
	editor.tokens = NULL;
	editor.tokens_bak = NULL;
	init_code();	

}

static void activate(GtkApplication *app, gpointer user_data)
{
	editor.builder = gtk_builder_new();
	gtk_builder_add_from_file(editor.builder, "resources/main_window.ui", NULL);	
	editor.window = gtk_builder_get_object(editor.builder, "window");
	init_app();
	gtk_window_set_application(GTK_WINDOW(editor.window), app);
gtk_widget_set_visible(GTK_WIDGET(editor.window), TRUE);
}

static void code_text_buffer_changed(GtkWidget *widget, GdkEventKey *event)
{
	delete(editor.tokens_bak, dispose_token);
	gtk_text_buffer_get_bounds(editor.code_view.buffer, &editor.code_view.start, &editor.code_view.end);
	char *text = gtk_text_buffer_get_text(editor.code_view.buffer, &editor.code_view.start, &editor.code_view.end, TRUE);
	gtk_text_buffer_set_text(editor.analysis.buffer, "", 0);
	
	int count = 0;

	int ret = tokenize(text, &editor.tokens);

	editor.tokens_bak = editor.tokens;

	if (ret)
	{
#ifdef LEX_DBG
		char *tokens_str = token_collection_to_str(&editor.tokens);
		gtk_text_buffer_set_text(editor.analysis.buffer, tokens_str, strlen(tokens_str));
		free(tokens_str);
#endif
	//gtk_text_buffer_apply_tag_by_name(editor.analysis_view.buffer, fonts[2], &editor.analysis_view.start, &editor.analysis_view.end);

	}
#ifndef LEX_DBG
	parser_t parser;
	parser.state = STATE_INVALID;
	editor.tokens = editor.tokens_bak;
	int error = 0;
	
	while (editor.tokens != NULL)
	{
		parse(&parser, *((token_t *)editor.tokens->data), &error);
		if (error)
			gtk_text_buffer_set_text(editor.analysis.buffer, "Parsing ERROR", strlen("Parsing ERROR"));
		editor.tokens = editor.tokens->next;
	}
#endif
}

void autocomplete();

static gboolean code_key_pressed(GtkWidget *widget, GdkEventKey *event)
{
	switch (event->keyval)
	{
		case GDK_KEY_Control_L:
			MODIFIER_ACTION(LCTRL, 1);
			break;
		case GDK_KEY_Control_R:
			MODIFIER_ACTION(RCTRL, 1);
			break;
		case GDK_KEY_Shift_L:
			MODIFIER_ACTION(LSHIFT, 1);
			break;
		case GDK_KEY_Shift_R:
			MODIFIER_ACTION(RSHIFT, 1);
			break;
		case GDK_KEY_Alt_L:
			MODIFIER_ACTION(LALT, 1);
			break;
		case GDK_KEY_Alt_R:
			MODIFIER_ACTION(RALT, 1);
		case GDK_KEY_Tab:
			delete(editor.tokens_bak, dispose_token);
			gtk_text_buffer_get_bounds(editor.code_view.buffer, &editor.code_view.start, &editor.code_view.end);
			char *text = gtk_text_buffer_get_text(editor.code_view.buffer, &editor.code_view.start, &editor.code_view.end, TRUE);
			int ret = tokenize(text, &editor.tokens);
			editor.tokens_bak = editor.tokens;
			autocomplete();
			return TRUE;
	}
	return FALSE;
}

void autocomplete()
{
	while (editor.tokens != NULL)
	{
		if (editor.tokens->next == NULL)
		{
			g_print("tokens->last=%s\n", ((token_t *)editor.tokens->data)->value);
			for (int i = 0; i < KEYWORDS_COUNT; i++)
			{
				g_print("comp(%s, %s)=%d\n", ((token_t *)editor.tokens->data)->value, keywords_list[i], 
						strcmp(((token_t *)editor.tokens->data)->value, keywords_list[i]));
			}
			
		}
		editor.tokens = editor.tokens->next;
	}
	
}

int main(int argc, char **argv)
{
#ifdef RELEASE
	GtkApplication *app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect (app, "activate", G_CALLBACK(activate), app);
	
	int status = g_application_run(G_APPLICATION(app), argc, argv);
	
	g_object_unref(app);
	g_object_unref(editor.builder);
	
	return status;
	
#else

	list_t *tokens = NULL;
	list_t *tokens_bak = tokens;
	int ret = tokenize("Oper op = (int x) -> x + 2;", &tokens);

	if (ret)
	{
		char *tokens_str = token_collection_to_str(&tokens);
		g_print(tokens_str);
		free(tokens_str);

	}
	delete(tokens_bak, dispose_token);
#endif

}
