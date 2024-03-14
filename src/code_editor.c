#include "code_editor.h"
#include "lexer.h"
code_editor_t editor;

static void activate(GtkApplication *app, gpointer user_data)
{
	editor.builder = gtk_builder_new();
	gtk_builder_add_from_file(editor.builder, "resources/main_window.ui", NULL);	
	editor.window = gtk_builder_get_object(editor.builder, "window");
	gtk_window_set_application(GTK_WINDOW(editor.window), app);
	gtk_widget_set_visible(GTK_WIDGET(editor.window), TRUE);
}

int main(int argc, char **argv)
{
	/*GtkApplication *app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect (app, "activate", G_CALLBACK(activate), app);
	
	int status = g_application_run(G_APPLICATION(app), argc, argv);
	
	g_object_unref(app);
	g_object_unref(editor.builder);
	
	return status;
	*/
	char *ch = expr_to_tokens_str("Operation op = (int x) -> { x + 2 }");
	printf(ch);
}
