#include "list.h"

#ifndef LEXER_H_
#define LEXER_H_

#define KEYWORDS_COUNT 8

const char* keywords_list[KEYWORDS_COUNT] = {
	"Operation", "short", "int", "long", "float", "double", "boolean", "char"
};

typedef enum token_type 
{ 
	KEYWORD, 
	IDENT, 
	EQUALS, 
	NUMBER,
	WHITESPACE, 
	OPERATION, 
	ASSIGNMENT, 
	OPEN_PAREN, 
	CLOSE_PAREN,
	OPEN_BRACE, 
	CLOSE_BRACE, 
	COMMA, 
	SEMICOLON,
	NEWLINE,
	INVALID
} token_type_e;

#define TOKEN_TYPE_TO_STR(type) \
{ \
	switch(type) \
	{ \
		case KEYWORD: \
			return "KEYWORD"; \
		case IDENT: \
			return "IDENT"; \
		case EQUALS: \
			return "EQUALS"; \
		case NUMBER: \
			return "NUMBER"; \
		case WHITESPACE: \
			return "WHITESPACE"; \
		case OPERATION: \
			return "OPERATION"; \
		case ASSIGNMENT: \
			return "ASSIGNMENT"; \
		case OPEN_PAREN: \
			return "OPEN_PAREN"; \
		case CLOSE_PAREN: \
			return "CLOSE_PAREN"; \
		case OPEN_BRACE: \
			return "OPEN_BRACE"; \
		case CLOSE_BRACE: \
			return "CLOSE_BRACE"; \
		case COMMA: \
			return "COMMA"; \
		case SEMICOLON: \
			return "SEMICOLON"; \
		case NEWLINE: \
			return "NEWLINE"; \
		case INVALID: \
			return "INVALID"; \
	} \
}

typedef struct token
{
	char *value;
	unsigned start,
	         end;
	token_type_e type;

} token_t;

int tokenize(const char *expr, list_t **tokens);
static token_t *create_token(const char *expr, int start, int end, token_type_e type);
char *token_to_str(token_t *token);
char *token_collection_to_str(list_t **tokens);
void dispose_token(token_t *token);

#endif // LEXER_H_
