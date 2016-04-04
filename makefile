ipquoridor.15-063.15-064 : main.o cmds.o playingCmds.o createMatrices.o bfs.o undo.o Utilities.o minimax.o
	gcc -o ipquoridor.15-063.15-064 main.o cmds.o playingCmds.o createMatrices.o bfs.o undo.o Utilities.o minimax.o
main.o : main.c mainUtilities.h matricesUtilities.h
	gcc -c main.c
cmds.o : cmds.c 
	gcc -c cmds.c
playingCmds.o : playingCmds.c Utilities.h matricesUtilities.h
	gcc -c playingCmds.c
createMatrices.o : createMatrices.c
	gcc -c createMatrices.c
bfs.o : bfs.c Utilities.h
	gcc -c bfs.c 
undo.o : undo.c Utilities.h
	gcc -c undo.c
Utilities.o : Utilities.c
	gcc -c Utilities.c
minimax.o : minimax.c Utilities.h bfsUtilities.h matricesUtilities.h
	gcc -c minimax.c
clean :
	rm main.o cmds.o playingCmds.o createMatrices.o bfs.o undo.o Utilities.o minimax.o
