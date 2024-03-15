#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"
#include <gtk/gtk.h>

char* keywords[KEYWORDS_COUNT] = {
	"byte", "short", "int", "long", "float", "double", "boolean", "char", "Operation"
};

static char *type_to_str(token_type_e type)
{
	TYPE_TO_STR(type);
}

static token_t *create_token(char *expr, int start, int end, token_type_e type)
{
	token_t *token = malloc(sizeof(token_t));
	token->lexeme = malloc(end - start + 1);
	token->lexeme_start = start;
	token->lexeme_end = end;
	token->type = type;
	token->lexeme[end - start + 1] = '\0';
	strncpy(token->lexeme, expr + start, end - start + 1);
	IS_KEYWORD(token);
	return token;

}


token_t *tokenize(const char *expr, int *count)
{

	char *buffer  = malloc(strlen(expr) + 1);
	memcpy(buffer, expr, strlen(expr) + 1);

	int lexeme_start, lexeme_end = 0;
	token_type_e type = INVALID;
	*count = 0;

	token_t *tokens = malloc(sizeof(token_t));

	for(; *expr != '\0'; expr++)
	{
		lexeme_start = lexeme_end;
		switch(*expr)
		{
			case 65 ... 90:
			case 97 ... 122:
				while (*expr >= 65 && *expr <= 90 ||
				       *expr >= 97 && *expr <= 122 ||
				       *expr >= 48 && *expr <= 57)
				{
					expr++;
					lexeme_end++;
				}
				expr--;
				lexeme_end--;
				type = IDENT;
				break;
			case ' ':
			case '\0':
			case '\n':
			case '\t':
				type = WHITESPACE;
				break;
			case 48 ... 57:
				lexeme_end--;
number_recognition:
				while (*expr >= 48 && *expr <= 57 || *expr == '.')
				{
					expr++;
					lexeme_end++;
				}
				expr--;
				type = NUMBER;
				break;
			case '=':
				type = EQUALS;
				break;
			case '+':
			case '*':
			case '/':
			case '^':
				type = OPERATION;
				break;
			case '-':
				switch (*++expr)
				{
					case '>':
						type = ASSIGNMENT;
						break;
					case 48 ... 57:
						goto number_recognition;
					default:
						type = OPERATION;
				}
				lexeme_end++;
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
			case ',':
				type = COMMA;
				break;
			case ';':
				type = SEMICOLON;
				break;
			default:
				type = INVALID;
				goto emergency_exit;
		}

		token_t *t = create_token(buffer, lexeme_start, lexeme_end, type);
		memcpy(&tokens[*count], t, sizeof(token_t));
		*count = *count + 1;
		tokens = realloc(tokens, sizeof(token_t) * (*count + 1));
		lexeme_end++;
	}
	for (int i = 0; i < *count; i++)
	g_print(token_stringize(tokens[i]));
/*
	parser_t parser;
	parser.state = INVALID;
	int is_error = 0;
	for (int i = 0; i < *count; i++)
	{
		is_error = 0;
		parse(&parser, tokens[i], &is_error);
		if (is_error)
			printf(token_stringize(tokens[i]));
	}

*/
	return tokens;

emergency_exit:
	//printf("%s\n", buffer);
	//printf("%*c -here\n", lexeme_start + 1, '^');
	//fprintf(stderr, "ERROR=%d, Invalid symbol at [%d]!\n", CRITICAL, lexeme_start);
	*count = -1;
	return NULL;
}

static char *token_stringize(token_t token)
{
	int count = snprintf(NULL, 0, "%20s | %4d - %4d | %20s\n", token.lexeme, 
	                                                   token.lexeme_start, 
	                                                   token.lexeme_end, 
	                                                   type_to_str(token.type));
	
	char *buff = malloc(count + 1);


	snprintf(buff, count + 1, "%20s | %4d - %4d | %20s\n", token.lexeme,
	                                       token.lexeme_start,
	                                       token.lexeme_end,
	                                       type_to_str(token.type));
	return buff;
}

char *expr_to_tokens_str(char *expr)
{
	int count = 0;
	char *token_str;
	token_t *tokens = tokenize(expr, &count);
	int fin_len = 0;
/*
	if (count == -1)
	{
		fin_len= snprintf(NULL, 0, "%s\n%*c -here\nERROR=%d! Invalid symbol at [%d]!\n", expr, strlen(expr), '^', CRITICAL, strlen(expr));
		token_str = malloc(fin_len + 1);
		snprintf(token_str, fin_len + 1, "%s\n%*c -here\nERROR=%d! Invalid symbol at [%d]!\n", expr, strlen(expr), '^', CRITICAL, strlen(expr));
		return token_str;
	}
	*/
	if (count == -1 || count == 0)
		return NULL;

	for(int i = 0; i < count; i++)
	{
		char *ch = token_stringize(tokens[i]); 
		fin_len += strlen(ch);
	}
	token_str = malloc(fin_len) + 1;

	int pos = 0;
	for(int i = 0; i < count; i++)
	{
		char *ch = token_stringize(tokens[i]); 
		pos += sprintf(&token_str[pos], "%s", ch);
	}
	free(tokens);
	return token_str;
}
