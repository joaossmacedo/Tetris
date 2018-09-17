all:
	@gcc -o tetris *.c -g -lncurses -Wall -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wdeclaration-after-statement -Wmissing-declarations -Wredundant-decls -Wcast-align -Wswitch-enum -Wformat -Wformat-security
clean:
	@rm -rf tetris tetris.dSYM