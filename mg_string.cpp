#include <iostream>
#include "mg_string.h"

using std::cerr;
using std::endl;

// Lookup table for ASCII escape sequences. All sequences are two characters
// long, beginning with a backslash `\` and ending with another character.
// This will return the numeric ASCII value to be inserted into a char[ ] or
// assigned to an index in a string.

char ascii_lookup(char escaped) {
	switch (escaped) {
		case '0' : return 0;  // null
		case 'a' : return 7;  // alarm / bell
		case 'b' : return 8;  // backspace
		case 't' : return 9;  // (horizontal) tab
		case 'n' : return 10; // newline / line feed
		case 'v' : return 11; // vertical tab
		case 'f' : return 12; // form feed (who uses this? I do.)
		case 'r' : return 13; // carriage return (lol windows/mac)
		case 'e' : return 27; // escape character
		case '"' : return 34; // double quote
		case '\'': return 39; // apostrophe
		case '\\': return 92; // backslash
		// for now, there will be no support for octal or hex escapes
		default:
			cerr << "unsupported escape sequence: `\\'" << escaped << "`.";
			cerr << endl;
			exit(EXIT_FAILURE);
	}
}
