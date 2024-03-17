#include "code_editor.h"
#include <stdio.h>
code_editor_t editor;
static void code_text_buffer_changed(GtkWidget *widget, GdkEventKey *event);

static void init_code()
{
	editor.code_view.textview = gtk_builder_get_object(editor.builder, "code_view");
	editor.code_view.buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(editor.code_view.textview));
	editor.analysis.textview = gtk_builder_get_object(editor.builder, "analysis");
	editor.analysis.buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(editor.analysis.textview));
	g_signal_connect(GTK_TEXT_BUFFER(editor.code_view.buffer), "changed", G_CALLBACK(code_text_buffer_changed), NULL);
}

static void init_app()
{
	editor.window = gtk_builder_get_object(editor.builder, "window");
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
	gtk_text_buffer_get_bounds(editor.code_view.buffer, &editor.code_view.start, &editor.code_view.end);
	char *text = gtk_text_buffer_get_text(editor.code_view.buffer, &editor.code_view.start, &editor.code_view.end, TRUE);
	gtk_text_buffer_set_text(editor.analysis.buffer, "", 0);
	
	int count = 0;

	list_t *tokens = NULL;
	int ret = tokenize(text, &tokens);
	list_t *tokens_bak = tokens;

	if (ret)
	{
#ifdef LEX_DBG
		char *tokens_str = token_collection_to_str(&tokens);
		gtk_text_buffer_set_text(editor.analysis.buffer, tokens_str, strlen(tokens_str));
		free(tokens_str);
#endif
	//gtk_text_buffer_apply_tag_by_name(editor.analysis_view.buffer, fonts[2], &editor.analysis_view.start, &editor.analysis_view.end);

	}
#ifndef LEX_DBG
	parser_t parser;
	parser.state = INVALID;
	tokens = tokens_bak;
	int error = 0;
	
	while (tokens != NULL)
	{
		parse(&parser, *((token_t *)tokens->data), &error);
		if (error)
			gtk_text_buffer_set_text(editor.analysis.buffer, "Parsing ERROR", strlen("Parsing ERROR"));
		tokens = tokens->next;
	}
#endif
	delete(tokens_bak, dispose_token);
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
