#include <iostream>
#include <cstring>
#include <cstdlib>
#include "tree.h"
#include "parser.tab.h"

// copy a target string taken in by the lexer which represents a string
// literal and remove the leading and trailing double-quotes for use by
// the interpreter.
// return the number of characters copied. This function should never be
// called on anything but a string literal node.
int strnqcpy(char * destination, char * target) {
	char delim;
	if (!strlen(target)) {
		return 0;
	}
	
	if (target[0] == '"') {
		delim = '"';
	} else if (target[0] == '\'') {
		delim = '\'';
	} else {
		return -1; // not a string literal
	}
	
	if (target[strlen(target)-1] != delim) {
		return -1; // improperly matched quotes or missing final quote
	}
	target++;
	int c = 0;
	while (target[c] != delim) {
		destination[c] = target[c++];
	}
	destination[c] = '\0'; // write in the null-terminator
	return c;
}

std::string escape(char * str) {
	std::string s;
	while (*str) {
		if (*str == '\\') {
			switch (*(str + 1)) {
				case 'n' : s += "\n"; break;
				case 'r' : s += "\r"; break;
				case 'f' : s += "\f"; break;
				case 't' : s += "\t"; break;
				case '"' : s += "\""; break;
				case '\'': s += "'" ; break;
				case '\\': s += "\\"; break;
			}
			str++;
		} else {
			s += std::string(1, *str);
		}
		str++;
	}
	return s;
}


struct node* make_node(int token, void* value) {
	struct node* n = new struct node;
	n->token = token;

	if (value != NULL) {
		if (token == STRING_LITERAL) {
			// drop two characters from the array because we're not
			// allocating space for the quotes
			n->value = new char[strlen((char*)value)-1];
			strnqcpy((char*) n->value, (char*)value);
			// process escape sequences and resize character array
			std::string temp = escape((char *)n->value);
			delete [] (char *) n->value;
			n->value = new char[temp.length()];
			strcpy((char *)n->value, temp.c_str());
		} else if (token == IDENTIFIER) {
			n->value = new char[strlen((char*)value)+1];
			strcpy((char*)n->value, (char*)value);
		} else if (token == INTEGER_LITERAL) {
			n->value = new int(*(int*)value);
		} else if (token == FLOAT_LITERAL) {
			n->value = new double(* (double *) value);
		}
	}

	n->num_children = 0;
	for (int i = 0; i < MAX_CHILDREN; i++) {
		n->children[i] = NULL;
	}
	return n;
}

void attach(struct node* parent, struct node* child) {
	parent->children[parent->num_children] = child;
	parent->num_children++;
}

void print(struct node* node, int tabs) {
	if(!node) return;

	/* print leading tabs */
	for(int i = 0; i < tabs; i++) {
		std::cout << "    ";
 	}
	
	switch (node->token) {
		// unholy
		using std::cout; using std::endl;
		case BRACE_OPEN:    cout << "BRACE_OPEN"    << endl; break;
		case BRACE_CLOSE:   cout << "BRACE_CLOSE"   << endl; break;
		case ASSIGN:        cout << "ASSIGN"        << endl; break;
		case COLON:         cout << "COLON"         << endl; break;
		case SEMICOLON:     cout << "SEMICOLON"     << endl; break;
		case COMMA:         cout << "COMMA"         << endl; break;
		
		case TYPE_FUNCTION: cout << "TYPE_FUNCTION" << endl; break;
		case TYPE_METHOD:   cout << "TYPE_METHOD"   << endl; break;
		case TYPE_INTEGER:  cout << "TYPE_INTEGER"  << endl; break;
		case TYPE_STRING:   cout << "TYPE_STRING"   << endl; break;
		case TYPE_FLOAT:    cout << "TYPE_FLOAT"    << endl; break;
		case TYPE_TYPE:     cout << "USER TYPE"     << endl; break;
		case TYPE_VOID:     cout << "TYPE_VOID"     << endl; break;
		case OPTION:        cout << "OPTION"        << endl; break;
		case CASE:          cout << "CASE"          << endl; break;
		case IF:            cout << "IF"            << endl; break;
		case ELSE:          cout << "ELSE"          << endl; break;
		case FOR_LOOP:      cout << "FOR"           << endl; break;
		case WHILE_LOOP:    cout << "WHILE"         << endl; break;
		case IN:            cout << "IN"            << endl; break;
		case BREAK:         cout << "BREAK"         << endl; break;
		case NEXT:          cout << "NEXT"          << endl; break;
		
		case ACCESS:        cout << "ACCESS"        << endl; break;
		case BRACKET_OPEN:  cout << "BRACKET_OPEN"  << endl; break;
		case BRACKET_CLOSE: cout << "BRACKET_CLOSE" << endl; break;
		case PAREN_OPEN:    cout << "PAREN_OPEN"    << endl; break;
		case PAREN_CLOSE:   cout << "PAREN_CLOSE"   << endl; break;
		case POWER:         cout << "POWER"         << endl; break;
		case LOG:           cout << "LOG"           << endl; break;
		case TIMES:         cout << "TIMES"         << endl; break;
		case DIVIDE:        cout << "DIVIDE"        << endl; break;
		case MODULO:        cout << "MODULO"        << endl; break;
		case PLUS:          cout << "PLUS"          << endl; break;
		case MINUS:         cout << "MINUS"         << endl; break;
		case LEFT_SHIFT:    cout << "LEFT_SHIFT"    << endl; break;
		case RIGHT_SHIFT:   cout << "RIGHT_SHIFT"   << endl; break;
		
		case LESS_THAN:     cout << "LESS_THAN"     << endl; break;
		case GREATER_THAN:  cout << "GREATER_THAN"  << endl; break;
		case EQUAL:         cout << "EQUAL"         << endl; break;
		case NOT_EQUAL:     cout << "NOT_EQUAL"     << endl; break;
		case GREATER_EQUAL: cout << "GREATER_EQUAL" << endl; break;
		case LESS_EQUAL:    cout << "LESS_EQUAL"    << endl; break;
		
		case LOG_AND:       cout << "LOG_AND"       << endl; break;
		case LOG_OR:        cout << "LOG_OR"        << endl; break;
		case LOG_NOT:       cout << "LOG_NOT"       << endl; break;
		case LOG_XOR:       cout << "LOG_XOR"       << endl; break;
		case LOG_IMPLIES:   cout << "LOG_IMPLIES"   << endl; break;
		
		case BIT_AND:       cout << "BIT_AND"       << endl; break;
		case BIT_OR:        cout << "BIT_OR"        << endl; break;
		case BIT_NOT:       cout << "BIT_NOT"       << endl; break;
		case BIT_XOR:       cout << "BIT_XOR"       << endl; break;
		case BIT_IMPLIES:   cout << "BIT_IMPLIES"   << endl; break;
		
		case IDENTIFIER:
			cout << "IDENTIFIER: " << (char*)node->value << endl;
			break;
		case INTEGER_LITERAL:
			cout << *(int*)node->value << endl;
			break;
		case FLOAT_LITERAL:
			cout << *(double*)node->value << endl;
			break;
		case STRING_LITERAL:
			cout << std::string((char *)node->value) << endl;
			break;
		
		case STATEMENT:     cout << "STATEMENT:"    << endl; break;
		case ARGUMENT:      cout << "ARGUMENT:"     << endl; break;
		case PRINT:         cout << "PRINT:"        << endl; break;
		case INPUT:         cout << "INPUT"         << endl; break;
		
		default:
			cout << "Invalid token: " << node->token << endl; break;
	}

	for(int i = 0; i < node->num_children; i++) {
    	print(node->children[i], tabs + 1);
  	}
}
