// James Murphy
// CPSC 401 / Programming Languages
// magenta lexer token list
// Intended to be a temporary test file until parser.tab.h can be used


#define BRACE_OPEN      100
#define BRACE_CLOSE     101
#define ASSIGN          102
#define COLON           103

#define TYPE_FUNCTION   110
#define TYPE_INTEGER    111
#define TYPE_STRING     112
#define TYPE_FLOAT      113
#define TYPE_COMPOUND   114
#define OPTION_STMT     115
#define CASE_STMT       116
#define IF_STMT         117
#define ELIF_STMT       118
#define ELSE_STMT       119
#define FOR_LOOP        120
#define WHILE_LOOP      121

#define ACCESS          130
#define BRACKET_OPEN    131
#define BRACKET_CLOSE   132
#define PAREN_OPEN      133
#define PAREN_CLOSE     134
#define POWER           135
#define LOG             136
#define TIMES           137
#define DIVIDE          138
#define MODULO          139
#define PLUS            140
#define CONCAT          141
#define MINUS           142

#define LESS_THAN       150
#define GREATER_THAN    151
#define EQUAL           152
#define NOT_EQUAL       153
#define GREATER_EQUAL   154
#define LESS_EQUAL      155

#define LOG_AND         160
#define LOG_OR          161
#define LOG_NOT         162
#define LOG_XOR         163
#define LOG_IMPLIES     164

#define BIT_AND         165
#define BIT_OR          166
#define BIT_NOT         167
#define BIT_XOR         168
#define BIT_IMPLIES     169

#define IDENTIFIER      170
#define NUMERIC_LITERAL 171
#define STRING_LITERAL  172
