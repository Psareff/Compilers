#ifndef PARSER_H_
#define PARSER_H_

#include "lexer.h"

typedef struct parser
{
	token_type_e state;
} parser_t;

void parse(parser_t *parser, token_t token, int *is_error);

#endif // PARSER_H_
