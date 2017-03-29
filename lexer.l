%{
// James Murphy
// Taylor Dohmen
// CPSC 401 / Programming Languages
// magenta lexer

#include <stdio.h>
#include "parser.tab.h"

unsigned int linecount = 0;

%}

%option noyywrap

%%

"{"        {return BRACE_OPEN;    }
"}"        {return BRACE_CLOSE;   }
"="        {return ASSIGN;        }
":"        {return COLON;         }
";"        {return SEMICOLON;     }
","        {return COMMA;         }

"func"     {return TYPE_FUNCTION; }
"meth"     {return TYPE_METHOD;   }
"int"      {return TYPE_INTEGER;  }
"str"      {return TYPE_STRING;   }
"flt"      {return TYPE_FLOAT;    }
"type"     {return TYPE_TYPE;     }
"void"     {return TYPE_VOID;     }

"option"   {return OPTION;        }
"case"     {return CASE;          }
"if"       {return IF;       	  }
"else"     {return ELSE;     	  }

"for"      {return FOR_LOOP;      }
"from"     {return FROM;          }
"to"       {return TO;            }
"by"       {return BY;            }

"while"    {return WHILE_LOOP;    }
"in"       {return IN;            }

"break"    {return BREAK;         }
"next"     {return NEXT;          }
"return"   {return RETURN;        }
"pass"     {return PASS;          }

"."        {return ACCESS;        }
"["        {return BRACKET_OPEN;  }
"]"        {return BRACKET_CLOSE; }
"("        {return PAREN_OPEN;    }
")"        {return PAREN_CLOSE;   }

"**"       {return POWER;         }
"~"        {return LOG;           }

"//"       {return INT_DIVIDE;    }
"*"        {return TIMES;         }
"/"        {return DIVIDE;        }
"%"        {return MODULO;        }
"+"        {return PLUS;          }
"-"        {return MINUS;         }

"<<"       {return LEFT_SHIFT;    }
">>"       {return RIGHT_SHIFT;   }

"<"        {return LESS_THAN;     }
">"        {return GREATER_THAN;  }
"=="       {return EQUAL;         }
"!="       {return NOT_EQUAL;     }
">="       {return GREATER_EQUAL; }
"<="       {return LESS_EQUAL;    }

"and"      {return LOG_AND;       }
"or"       {return LOG_OR;        }
"not"      {return LOG_NOT;       }
"xor"      {return LOG_XOR;       }
"then"     {return LOG_IMPLIES;   }

"&"        {return BIT_AND;       }
"|"        {return BIT_OR;        }
"!"        {return BIT_NOT;       }
"^"        {return BIT_XOR;       }

"print"    {return PRINT;         }
"input"    {return INPUT;         }

"true" {
	yylval.ival = 1;
	return INTEGER_LITERAL;
}

"false" {
	yylval.ival = 0;
	return INTEGER_LITERAL;
}

[a-zA-Z_]+[0-9a-zA-Z_]* {
	yylval.str = yytext;
	return IDENTIFIER;
}

0|[1-9]+[0-9]* {
	yylval.ival = atoi(yytext);
	return INTEGER_LITERAL;
}

[0-9]*\.[0-9]+ {
	yylval.fval = atof(yytext);
	return FLOAT_LITERAL;
}

\"(\\.|[^"])*\" {
	yylval.str = yytext;
	return STRING_LITERAL;
}

'(\\.|[^'])*' {
	yylval.str = yytext;
	return STRING_LITERAL;
}

"#".*         {/* comment */     }
[ \t]+        {/* whitespace */  }
[[\r\n]\n\r]+ {linecount += 1;   }

%%
