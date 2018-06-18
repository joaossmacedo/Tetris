all:
	@gcc -o tetris *.c -g -lncurses
clean:
	@rm -rf tetris tetris.dSYM