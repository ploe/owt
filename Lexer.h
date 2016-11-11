#ifndef OWT_LEXER
#define OWT_LEXER
#include <stdio.h>
#include <string.h>

/*	The Lexer is the type that maintains the object we're parsing at
	the mo. It has a few methods for reading its state. They're for
	legibility because the values could be obtained by directly 
	fussing with start and len.

	The Grammar module is what uses the Lexer.

	Delimiters are the delimiters we've counted in 
	the current parsed object	*/

typedef struct Lexer {
	char *src, *start;
	unsigned int last, len;
} Lexer;

/*	Lexer methods	*/

Lexer NewLexer(char *src, unsigned int last);
char Next(Lexer *lexer);
char Prev(Lexer *lexer);
char Peek(Lexer *lexer);
char PrevSteps(Lexer *lexer, unsigned int steps);
char Accept(Lexer *lexer, char *valid);
char Deny(Lexer *lexer, char *valid);
int Match(Lexer *lexer, char *valid);
void Ditch(Lexer *lexer);

/* Lexer macros	*/

#define END_OF_STRING(c) ((c == EOF) || (c == '\0'))
enum {
	YES = -1,
	NO
};


#endif
