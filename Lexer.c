#include "Lexer.h"
#define LEXER_OVERFLOW(l) (l->last && (l->len > l->last))

Lexer NewLexer(char *src, unsigned int last) {
	Lexer lexer;
	lexer.src = lexer.start = src;
	lexer.last = last;
	lexer.len = 0;

	return lexer;
}

// next pops the next letter out of our lexer
char Next(Lexer *lexer) {
	char c = *(lexer->start + lexer->len);
	lexer->len += 1;

	if (LEXER_OVERFLOW(lexer)) {
		lexer->len = lexer->last;
		return '\0';
	}

	return c;
}

// look back at the last letter
char Prev(Lexer *lexer) {
	if (lexer->len <= 0) return '\0';
	return *(lexer->start + lexer->len - 1);
}

// Peek takes a little look-ahead so we know what the next letter is
char Peek(Lexer *lexer) {
	if (lexer->last && ((lexer->len + 1) > lexer->last)) return '\0';
	return *(lexer->start + lexer->len);
}

// looks back a number of steps in the current token, we can't look
// beyond the start otherwise we get a null char
char PrevSteps(Lexer *lexer, unsigned int steps) {
	char *c = lexer->start - steps;
	if (c < lexer->start) return '\0';
	return *c;
}


// accepts a string of the characters that we can just wash over
static int accept(Lexer *lexer, char *valid) {
	char c = Next(lexer);
	for (; *valid != '\0'; valid++) {
		if(c == *valid) return YES;
	}

	return NO;
}

char Accept(Lexer *lexer, char *valid) {
	while (accept(lexer, valid)) {
		char c = Peek(lexer);
		if (END_OF_STRING(c)) return c;
	}
	return Prev(lexer);
}

char Deny(Lexer *lexer, char *valid) {
	while (!accept(lexer, valid)) {
		char c = Peek(lexer);
		if (END_OF_STRING(c)) return c;
	}
	return Prev(lexer);
}

int Match(Lexer *lexer, char *valid) {
	/*  start-1 so we can match patterns "true", "false" and "null" */
	return !(strncmp(valid, lexer->start-1, strlen(valid)));
}

/* moves the lexer's forward */
void Ditch(Lexer *lexer) {
	lexer->start += lexer->len;
	lexer->len = 0;
}

#undef LEXER_OVERFLOW
