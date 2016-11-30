all:
	 cc -I./hashish/murmur3 -I./hashish ./hashish/hashish.o Lexer.c main.c -o main
