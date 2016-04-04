#include <stdio.h>
#include <string.h>
#include "Utilities.h"
#include "matricesUtilities.h"
#define INFINITY 1000



typedef struct scoreMoves{
    int row;
    int col;
    int isMove;
    int ori;
    double value;

}MOVE;

MOVE alphaBeta(char **board,int sizeBoard,int position[2][2],int walls[2],int depth,const int initialDepth,int maxPL,int maximizingPlayer,double alpha,double beta,int maximizer);
extern int moves[12][7];


int playmove(char **board,int position[2][2],int sizeBoard,char **cmd) {

    int player=atoi(cmd[1]);
    int targetRow,targetCol,legal=0;
    char temp;
    int rows = 2* sizeBoard,columns = 4 * sizeBoard;
    char *tempCmd;



        temp = cmd[2][0];
        tempCmd = &(cmd[2][1]);
        targetRow = atoi(tempCmd);


        if (temp >= 'A' && temp <= 'Z')
			temp += 'a' - 'A';
        if (targetRow <= 0 ||  targetRow > rows / 2 || temp - 'a' < 0 || temp - 'a' >= columns / 4 ){
            printf("? illegal move\n\n");
            return 0;
        }

        targetRow = rows - (2*targetRow) + 1;
        targetCol = 4 *(temp - 'a') + 2;

        legal = check_Legal_Move(board,rows,columns,targetRow,targetCol,position[player][0],position[player][1]);
        if (legal){
            simpleMove(board,player,rows,targetRow,targetCol,position);
            printf("=\n\n");
			fflush(stdout);
			insertMove(player,0,targetRow,targetCol,-1);
        }
        else
            printf("? illegal move\n\n");


return 0;

}


void playwall(char **board,int sizeBoard,int walls[2],int position[2][2],char **cmd){
    char temp;
    int targetRow,targetCol,legal,player;
    int rows = 2 * sizeBoard,columns = 4 * sizeBoard,wallOrientation;
    int **visited;
    char *tempCmd;


    player = atoi(cmd[1]);
    temp = cmd[2][0];
    tempCmd = &(cmd[2][1]);
    targetRow = atoi(tempCmd);


	if (temp >= 'A' && temp <= 'Z')
		temp += 'a' - 'A';

	targetRow = rows - (2*targetRow) + 1;
    targetCol = 4 *(temp - 'a') + 2;

    visited = createVisited(rows,columns);
    toLower(cmd[3]);
    if (cmd[3] != NULL && ((strcmp(cmd[3],"horizontal") == 0) || strcmp(cmd[3],"h") == 0))
        wallOrientation = 1;
    else if (cmd[3] != NULL && strcmp(cmd[3],"vertical") == 0 || strcmp(cmd[3],"v") == 0)
        wallOrientation = 0;
    else{
        printf("? illegal move\n\n");
        fflush(stdout);
        return;
    }


    if (walls[player]>0){
        legal = check_Legal_Wall(board,rows,columns,targetRow,targetCol,wallOrientation,walls[0]);
        if (legal)
            legal = tryWall(board,rows,columns,targetRow,targetCol,position,wallOrientation,0,visited,walls,rows-1); //black
        if (legal)
            legal = tryWall(board,rows,columns,targetRow,targetCol,position,wallOrientation,1,visited,walls,1);      //white
        if (legal){
            printf("=\n\n");
            walls[player] -= 1;
            fflush(stdout);
            insertMove(player,1,targetRow,targetCol,wallOrientation);
        }
        else
            printf("? illegal move\n\n");
    }
    else if (player != 1 && player != 0)
        printf("? wrong syntax\n\n");
    else if (walls[player] == 0)
        printf("? illegal move\n\n");

    freeVisited(visited,rows);
}



void genmove(char **board,int sizeBoard,int position[2][2],int walls[2],int depth,int maxPL,int maxPlayer){
    MOVE bestMove;
    int rows = 2*sizeBoard;
    int columns = 4* sizeBoard;
    int winningRow,flag=0,i;
    double alpha,beta;
    const int initialDepth = depth;
    alpha = -INFINITY;
    beta = INFINITY;
    if (maxPL)
        winningRow = 1;
    else
        winningRow = 2*sizeBoard -1;

    /*Checks if there is an immediate move that makes the player win.If there is,there is no need to run alphaBeta.*/
    for (i=0;i<12;i++){
        if (moves[i][4] == 0){
            if(position[maxPL][0] != moves[i][2] && position[maxPL][1] != moves[i][3] &&
               (check_Legal_Move(board,rows,columns,position[maxPL][0] + moves[i][0],position[maxPL][1] + moves[i][1],position[maxPL][0],position[maxPL][1])) &&
                        position[maxPL][0] + moves[i][0] == winningRow ){

                        flag = 1;
                        break;
            }
        }
        else if (moves[i][4] == 1){
            if((position[maxPL][0]*moves[i][5] > moves[i][2]*moves[i][5])&&(position[maxPL][1]*moves[i][6] > moves[i][3]*moves[i][6])&&
               (check_Legal_Move(board,rows,columns,position[maxPL][0] + moves[i][0],position[maxPL][1] + moves[i][1],position[maxPL][0],position[maxPL][1])) &&
                        position[maxPL][0] + moves[i][0] == winningRow){

                        flag = 1;
                        break;
            }
        }
    }




    if (flag == 1){
        bestMove.isMove =1;
        bestMove.row = position[maxPL][0] + moves[i][0];
        bestMove.col = position[maxPL][1] + moves[i][1];
    }
    else
        bestMove = alphaBeta(board,sizeBoard,position,walls,depth,initialDepth,maxPL,1,alpha,beta,maxPL);

    if(bestMove.isMove == 1){
        simpleMove(board,maxPL,rows,bestMove.row,bestMove.col,position);
        insertMove(maxPL,0,bestMove.row,bestMove.col,-1);
        printf("= %c%d\n\n",(position[maxPL][1]-2)/4 + 'a',(rows - position[maxPL][0] + 1)/2);
        fflush(stdout);
    }
    else if (bestMove.isMove == 0){
        simpleWall(board,bestMove.ori,rows,bestMove.row,bestMove.col);
        insertMove(maxPL,1,bestMove.row,bestMove.col,bestMove.ori);
        if (bestMove.ori == 0){
            printf("= %c%d vertical\n\n",(bestMove.col-2)/4 + 'a',(rows - bestMove.row + 1)/2);
            fflush(stdout);
        }
        else{
            printf("= %c%d horizontal\n\n",(bestMove.col-2)/4 + 'a',(rows - bestMove.row + 1)/2);
            fflush(stdout);
        }
        walls[maxPL]--;
    }
    else printf("TO THE NOPEVILLE!!!! \n\n");

}


int showboard(char **board,int size,int walls[2]) {
    int i,j,k,counter;

    counter = 1;
    for (i=0;i<8;i++)
        putchar(' ');
    putchar('A');                                                                       /*Printing Letters indicating columns.*/
    for (i=0;i<7;i++)
        putchar(' ');
    for (j=0;j<2 *(4*size-2) -4 ;j++){
        if (j % 8 == 0){
           putchar('A' + counter);
           counter++;
        }
        else
            putchar(' ');
    }
    putchar('\n');                                                                      /*Ends here.*/
    for (i=0;i<2*size +1 ;i++){
            putchar(' ');
            putchar(' ');
            putchar(' ');
        for (j=0;j<4*size +1;j++){
            if (j == 0 && i % 2 == 1){                                                  /*Printing each line.*/
                    if ((2*size/2)-(i/2) < 10)
                        printf("\b%d ",(2*size/2)-(i/2));
                    else
                        printf("\b\b%d ",(2*size/2)-(i/2));
            }
            else
                putchar(' ');
            printf("%c",board[i][j]);
        }
        putchar(' ');
        if (j == 4*size +1 && i % 2 == 1){
            printf("%d",(2*size/2)-(i/2));
            if (i==1)
                printf(" black walls: %d",walls[0]);
            if (i==3)
                printf(" white walls: %d",walls[1]);
        }
        putchar('\n');


   }
    counter = 1;
    for (i=0;i<8;i++)
        putchar(' ');
    putchar('A');
    for (i=0;i<7;i++)
        putchar(' ');
    for (j=0;j<2 * (4*size-2) -4;j++){
        if (j % 8 == 0){
           putchar('A' + counter);
           counter++;                                                                   /*Printing letters once again.*/
        }
        else
            putchar(' ');
    }

    putchar('\n');
return 0;
}
