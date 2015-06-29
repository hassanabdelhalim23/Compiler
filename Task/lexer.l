%{
#include "data_types.h"
%}
%option yylineno

%%
"int"												return _INT;
"float"												return _FLOAT;
"void"												return _void;
"while"												return _WHILE;
"if"												return _IF;
"("													return LEFT_PAREN;
")"													return RIGHT_PAREN;
"{"													return LEFT_CURLY_BRACKET;
"}"													return RIGHT_CURLY_BRACKET;
"/*"([^*]|\*+[^*/])*\*+"/"							return COMMENT;
\/\/.*$												return COMMENT;
","													return COMMA;
";"													return SEMI_COLON;
"=="												return CMP_EQUAL;
"="													return EQUAL;
">"													return CMP_GT;
">="												return CMP_GT_EQUAL;
"<"													return CMP_LT;
"<="												return CMP_LT_EQUAL;
"-"													return MINUS;
"+"													return PLUS;
"*"													return MULTIPLY;
"/"													return DIVIDE;
[a-zA-Z][a-zA-Z0-9_]*								return IDENTIFIER;
[0-9][0-9]*											return INT_VAL;
[-+]?[0-9]*\.?[0-9]+([eE][-+]?[0-9]+)?				return FLOAT_VAL;
[ \t\n]												;
.													printf("unexpected character\n");


%%

int yywrap(void)
{
	return 1;
}