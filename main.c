#include "Lexer.h"


int lex(char *src) {
	Lexer l = NewLexer(src, strlen(src)); 
	char c = Accept(&l, " \t\n");
	putchar(c);
	return 0;
}

int main(int argc, char *argv[]) {
	lex("         \t\t\n    hello, world");
	return 0;	
}
