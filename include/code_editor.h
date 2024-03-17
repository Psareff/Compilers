#include "parser.h"
#include <gtk/gtk.h>
#include "dynamic_fonts.h"

#ifndef CODE_EDITOR_H_
#define CODE_EDITOR_H_


typedef struct code_editor_textview
{
	GObject *textview;
	GtkTextBuffer *buffer;
	GtkTextIter start,
		    end;

} code_editor_textview_t;

typedef struct code_editor
{
	GtkBuilder *builder;
	GObject *window,
		*status;

	FILE *fp;
	char is_saved;
	code_editor_textview_t code_view,
			       analysis;
	
	char *copied_text;	
} code_editor_t;

typedef struct lexeme_color
{
	const char *color;
	const char *lexeme;
} lexeme_color_t;

#define LEXEME_COLORS_COUNT 12

const lexeme_color_t colors[LEXEME_COLORS_COUNT] =
{
	#include "lexeme_colors.h"
};

#define LSHIFT (1 << 0)
#define RSHIFT (1 << 1)
#define LCTRL  (1 << 2)
#define RCTRL  (1 << 3)
#define LALT   (1 << 4)
#define RALT   (1 << 5)

char current_modifier_condition = 0x0;

#define MODIFIER_ACTION(modifier, action) \
{ \
	if (action) current_modifier_condition |= modifier; \
	else current_modifier_condition &= !modifier \
} 

#endif // CODE_EDITOR_H_
