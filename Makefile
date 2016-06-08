all:
	gcc   -g    commands.c commands.h struct.h struct.c library.h library.c parser.h parser.c   main.c   -lreadline   -o terminal 

clean:
	$(RM) prog
