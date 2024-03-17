#include "lexer.h"
#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <gtk/gtk.h>

#define KEYWORDS_COUNT 8

const char* keywords_list[KEYWORDS_COUNT] = {
	"Operation", "short", "int", "long", "float", "double", "boolean", "char"
};

#define IS_KEYWORD(token) \
	{ \
		printf("%s\n", token->value); \
		if (memcmp(token->value, "Operation", strlen(token->value)) == 0) \
		{ \
			token->type = KEYWORD; \
		} \
	}
	
token_t *create_token(const char *expr, int start, int end, token_type_e type)
{
	token_t *tok = malloc(sizeof(token_t));
	tok->start = start;
	tok->end = end;
	tok->value = expr;
	tok->type = type;
	//IS_KEYWORD(tok);
}

char *token_type_to_str(token_type_e type)
{
	TOKEN_TYPE_TO_STR(type);
}

char *token_to_str(token_t *token)
{
#define TOKEN_PRINT_FORMAT "%20s | [%4d - %4d] | %20s" 
	int count = snprintf(NULL, 0, TOKEN_PRINT_FORMAT, token->value,
			token->start,
			token->end,
			token_type_to_str(token->type)) + 1;
	char *buff = malloc(count);
	snprintf(buff, count, TOKEN_PRINT_FORMAT, token->value,
			token->start,
			token->end,
			token_type_to_str(token->type));
	return buff;

}
void dispose_token(token_t *token)
{
	free(token->value);
	free(token);
}

int tokenize (const char *expr, list_t **tokens)
{

	if (expr == "")
		return 0;
	char *buffer = malloc(strlen(expr) + 1);
	strcpy(buffer, expr);

	char *beginning = buffer;

	int start, 
	    end = 0;
	int count = 0;

	token_type_e type = INVALID;

	for (; *buffer != '\0'; buffer++)
	{
		start = end;
		switch (*buffer)
		{
			case 'A' ... 'Z':
			case 'a' ... 'z':
				while (buffer++ && 
				      (*buffer >= 'A' && *buffer <= 'Z') ||
				      (*buffer >= 'a' && *buffer <= 'z') ||
					  (*buffer >= '0' && *buffer <= '9'))
				{
					end++;
				}
				buffer--;
				type = IDENT;
				break;
			case '0' ... '9':
number_recognition:
				while (buffer++ &&
				      (*buffer >= '0' && *buffer <= '9') || *buffer == '.')
				{
					end++;
				}
				buffer--;
				type = NUMBER;
				break;
			case ' ':
				type = WHITESPACE;
				break;
			case '(':
				type = OPEN_PAREN;
				break;
			case ')':
				type = CLOSE_PAREN;
				break;
			case '{':
				type = OPEN_BRACE;
				break;
			case '}':
				type = CLOSE_BRACE;
				break;
			case '=':
				type = EQUALS;
				break;
			case '-':
				buffer++;
				switch (*buffer)
				{
					case '>':
						type = ASSIGNMENT;
						end++;
						break;
					case '0' ... '9':
						goto number_recognition;
					default:
						type = OPERATION;
						buffer--;
				}
				break;
			case '+':
			case '*':
			case '/':
				type = OPERATION;
				break;
			case ';':
				type = SEMICOLON;
				break;
			case '\n':
			case '\r':
				type = NEWLINE;
				goto newline;
				break;
			default:
				goto emergency;
		}

		char *token_value = malloc(end - start + 2);
		memcpy(token_value, beginning + start, end - start + 1);
		token_value[end - start + 1] = '\0';

		token_t *tok = create_token(token_value, start, end, type);
		goto non_newline;
newline:
		tok = create_token("\\n", start, end, type);
non_newline:
		*tokens = push(*tokens, tok);
		count++;
		end++;

	}

emergency:
	free(beginning);
	return count;
}

char *token_collection_to_str(list_t **tokens)
{
	if (*tokens == NULL)
		return "";

	char *token_collection_str = malloc(10240);
	for (int i = 0; i < 10240; i++)
	{
		token_collection_str[i] = 0;
	}
	while (*tokens != NULL)

	{
		char *tok_str = token_to_str((*tokens)->data);

		strcpy(token_collection_str + strlen(token_collection_str), tok_str);
		token_collection_str[strlen(token_collection_str)] = '\n';
		/*
		token_collection_str = realloc(token_collection_str, 
				strlen(token_collection_str) + strlen(tok_str));
		strcpy(token_collection_str + strlen(token_collection_str), tok_str);
*/
		g_print("%s\n", token_collection_str);
		free(tok_str);
		*tokens = (*tokens)->next;
	}
	//token_collection_str[strlen(token_collection_str)] = '\0';
	return token_collection_str;

}

