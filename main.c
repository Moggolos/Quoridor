#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mainUtilities.h"
#include "matricesUtilities.h"



int main(void){
    int sizeBoard = 9,wallNum = 10,winner = -1,i;         /*Standard size 9x9 , Standard walls 10.*/
    int rows,columns,walls[2] = {wallNum,wallNum};
    int depth = 2;



    char **board,command[50],**cmd;
    int position[2][2];


    cmd = malloc(4*sizeof(char*));
    if (cmd == NULL){
        printf("Not Enough Memory.Exiting\n");
        exit(0);
    }
    for(i=0;i<4;i++){
        cmd[i] = malloc(50 * sizeof(char));
        if (cmd[i] == NULL){
            printf("Not Enough Memory.Exiting\n");
            exit(0);
        }
    }

    rows=sizeBoard;
    columns=sizeBoard;
    rows *= 2;
    columns *= 4;


    board = mallocboard(sizeBoard);
    makeboard(board,position,sizeBoard);
    getMoves(sizeBoard);



    while (1){


        fgets(command,50,stdin);

        if (strcmp(command,"\n") == 0){
            printf("");
            fflush(stdout);
            continue;
        }
        getCommands(command,cmd);



        if (strcmp(cmd[0],"showboard") == 0){
            printf("=\n\n");
            showboard(board,sizeBoard,walls);
        }
        else if (strcmp(cmd[0],"playmove") == 0){
            toLower(cmd[1]);
            if (strcmp(cmd[1],"black") == 0 || strcmp(cmd[1],"b") == 0){
                strcpy(cmd[1],"0");
                playmove(board,position,sizeBoard,cmd);
            }
            else if (strcmp(cmd[1],"white") == 0 || strcmp(cmd[1],"w") == 0){
                strcpy(cmd[1],"1");
                playmove(board,position,sizeBoard,cmd);
            }
            else {
                printf("? wrong syntax\n\n");
                fflush(stdout);
                continue;
            }

            if (position[0][0] == rows -1)
                winner = 1;
            else if (position[1][0] == 1)
                winner = 2;
        }
        else if (strcmp(cmd[0],"playwall") == 0){
            toLower(cmd[1]);
            if (strcmp(cmd[1],"black") == 0 || strcmp(cmd[1],"b") == 0){
                strcpy(cmd[1],"0");
                playwall(board,sizeBoard,walls,position,cmd);
            }
            else if (strcmp(cmd[1],"white") == 0 || strcmp(cmd[1],"w") == 0){
                strcpy(cmd[1],"1");
                playwall(board,sizeBoard,walls,position,cmd);
            }
            else {
                printf("? wrong syntax\n\n");
                fflush(stdout);
                continue;
            }

        }
        else if (strcmp(cmd[0],"genmove") == 0){
            int maxPL;
            toLower(cmd[1]);
            if(winner != -1){
                printf("Game is already over.\n");                                                      /*Panic situation,Game is finished can't generate any more moves.*/
                continue;
            }
            if (strcmp(cmd[1],"black") == 0 || strcmp(cmd[1],"b") == 0){
                   maxPL = 0;
            }
            else if (strcmp(cmd[1],"white") == 0 || strcmp(cmd[1],"w") == 0){
                    maxPL = 1;
            }
            if (walls[maxPL] == 0)
                genmove(board,sizeBoard,position,walls,1,maxPL,1);
            else
                genmove(board,sizeBoard,position,walls,depth,maxPL,1);
            if (position[0][0] == rows -1)
                 winner = 1;
            else if (position[1][0] == 1)
                 winner = 2;
        }
        else if (strcmp(cmd[0],"clear_board") == 0){
            makeboard(board,position,sizeBoard);
            walls[0] = walls[1] = wallNum;
            emptyMoves();
            winner = -1;
            printf("=\n\n");
            fflush(stdout);
        }
        else if (strcmp(cmd[0],"name")==0){
            printf("= Wall-e\n\n");
            fflush(stdout);
        }
        else if (strcmp(cmd[0],"protocol_version")==0){
            printf("= 2.0\n\n");
            fflush(stdout);
        }
        else if (strcmp(cmd[0],"version")==0){
            printf("= Kappa\n\n");
            fflush(stdout);

        }
        else if (strcmp(cmd[0],"list_commands")==0){
            listcmd();
        }
        else if (strcmp(cmd[0],"known_command")==0){
            knowncmd(cmd[1]);

        }
        else if (strcmp(cmd[0],"boardsize") == 0){
            int oldSize=sizeBoard;

            if (atoi(cmd[1])<=25 && atoi(cmd[1]) % 2 == 1 ){
                sizeBoard = atoi(cmd[1]);
                freeboard(board,oldSize);                                                              /*We must re-initialize the whole game.*/
                rows=sizeBoard;
                columns=sizeBoard;
                rows *= 2;
                columns *= 4;
                emptyMoves();
                board = mallocboard(sizeBoard);
                makeboard(board,position,sizeBoard);
                walls[0] = walls[1] = wallNum;
                getMoves(sizeBoard);
                depth = depthSelect(sizeBoard);
                winner = -1;
                printf("= \n\n");
                fflush(stdout);
            }
            else
                printf("? unacceptable size\n\n");
        }
        else if (strcmp(cmd[0],"walls") == 0){
            wallNum = atoi(cmd[1]);
            walls[0] = walls[1] = wallNum;
            printf("= \n\n");
            fflush(stdout);
        }
        else if ((strcmp(cmd[0],"winner") == 0)){
            if (winner == 1){
                printf("= true black\n\n");
                fflush(stdout);
            }
            else if (winner == 2){
                printf("= true white\n\n");
                fflush(stdout);
            }
            else{
                printf("false\n\n");
                fflush(stdout);
            }
        }
        else if ((strcmp(cmd[0],"undo") == 0)){
            int times=1;
            times = atoi(cmd[1]);
            if (times == 0)
                times = 1;
            winner = -1;
            undo(board,rows,position,walls,times,sizeBoard,wallNum);
        }
        else if (strcmp(cmd[0],"quit") == 0){
            printf("=\n\n");

            for(i=0;i<4;i++)
                free(cmd[i]);
            free(cmd);
            freeboard(board,sizeBoard);

            return 0;
        }


        else
            printf("? unknown command\n\n");


    }
return 0;
}
