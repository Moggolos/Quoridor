quoridor : main.o Cmds.o PlayingCmds.o CreateMatrices.o BFS.o Undo.o Utilities.o Minimax.o
	gcc -o quoridor main.o Cmds.o PlayingCmds.o CreateMatrices.o BFS.o Undo.o Utilities.o Minimax.o
main.o : main.c MainUtilities.h MatricesUtilities.h
	gcc -c main.c
Cmds.o : Cmds.c 
	gcc -c Cmds.c
PlayingCmds.o : PlayingCmds.c Utilities.h MatricesUtilities.h
	gcc -c PlayingCmds.c
CreateMatrices.o : CreateMatrices.c
	gcc -c CreateMatrices.c
BFS.o : BFS.c Utilities.h
	gcc -c BFS.c 
Undo.o : Undo.c Utilities.h
	gcc -c Undo.c
Utilities.o : Utilities.c
	gcc -c Utilities.c
Minimax.o : Minimax.c Utilities.h BFSUtilities.h MatricesUtilities.h
	gcc -c Minimax.c
clean :
	rm main.o Cmds.o PlayingCmds.o CreateMatrices.o BFS.o Undo.o Utilities.o Minimax.o
