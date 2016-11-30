#include "Lexer.h"
#include "hashish/hashish.h"

typedef struct App {
	ish_Map *modules;	
} App;

App app;

int lex(char *src) {
	Lexer l = NewLexer(src, strlen(src)); 
	char c = Accept(&l, " \t\n");
	putchar(c);
	return 0;
}

int main(int argc, char *argv[]) {
	app.modules = ish_MapNew();

	lex("         \t\t\n    hello, world");
	return 0;	
}
