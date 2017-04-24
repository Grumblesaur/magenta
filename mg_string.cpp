#include <iostream>
#include <string>
#include <cstdlib>
#include "mg_string.h"
#include "mg_error.h"

extern unsigned linecount;

using std::cerr;
using std::endl;
using std::string;

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
			error(
				"unsupported escape sequence `\\'" + string(1, escaped),
				linecount
			);
	}
}


// if reps > 0 return value == s repeated reps times
// 	"abc" * 3 == "abcabcabc"
// if reps < 0 return value == reversed s repeated reps times
// 	"abc" * -3 == "cbacbacba""
// if reps == 0 return value == ""
string str_multiply(string s, int reps) {
	int len = s.length();
	int new_len = len * reps;
	if (reps > 0) {
		char temp[new_len];
		for (int i = 0; i < new_len; i++) {
			temp[i] = s[i % len];
		}
		return string(temp, new_len);
	} else if (reps < 0) {
		new_len = new_len * (-1);
		char temp[new_len];
		for (int i = new_len - 1; i > -1; i--) {
			temp[new_len - i - 1] = s[i % len];
		}
		return string(temp, new_len);
	}
	return "";
}
