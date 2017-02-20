%{
// James Murphy
// Taylor Dohmen
// CPSC 401 / Programming Languages
// magenta lexer

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "tokens.h" // temporary until tab.parser.h becomes available

%}

%option noyywrap

%%

"{"        {return BRACE_OPEN;    }
"}"        {return BRACE_CLOSE;   }
"="        {return ASSIGN;        }
":"        {return COLON;         }

"func"     {return TYPE_FUNCTION; }
"meth"     {return TYPE_METHOD;   }
"int"      {return TYPE_INTEGER;  }
"str"      {return TYPE_STRING;   }
"flt"      {return TYPE_FLOAT;    }
"type    " {return TYPE_COMPOUND; }

"option"   {return OPTION_STMT;   }
"case"     {return CASE_STMT;     }

"if"       {return IF_STMT;       }
"elif"     {return ELIF_STMT;     }
"else"     {return ELSE_STMT;     }

"for"      {return FOR_LOOP;      }
"while"    {return WHILE_LOOP;    }

"@"        {return ACCESS;        }
"["        {return BRACKET_OPEN;  }
"]"        {return BRACKET_CLOSE; }
"("        {return PAREN_OPEN;    }
")"        {return PAREN_CLOSE;   }
"**"       {return POWER;         }
"//"       {return LOG;           }
"*"        {return TIMES;         }
"/"        {return DIVIDE;        }
"%"        {return MODULO;        }
"+"        {return PLUS;          }
"."        {return CONCAT;        }
"-"        {return MINUS;         }

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

"et"       {return BIT_AND;       }
"aut"      {return BIT_OR;        }
"non"      {return BIT_NOT;       }
"xaut"     {return BIT_XOR;       }
"imp"      {return BIT_IMPLIES;   }

[a-zA-Z_]+[0-9a-zA-Z_]* {
	return IDENTIFIER;
}

[0-9]*\.?[0-9]+ {
	return NUMERIC_LITERAL;
}

\".*\"     {return STRING_LITERAL;}

"#".*      {/* comment */         }
[ \t\n]+   {/* whitespace */      }

%%
