#include <stdio.h>
#include <stdlib.h>
#include "Utilities.h"
#include "BFSUtilities.h"
#include "MatricesUtilities.h"

#define SPP 0.8
#define SPO 0.8
#define RD  0.1
#define MDP 0.1



#define INFINITY 1000


typedef struct scoreMoves{
    int row;
    int col;
    int isMove;
    int ori;
    double value;

}MOVE;

typedef struct possibleWalls{
	int row;
	int col;
}Walls;

extern int moves[12][7];


double evaluateMove(char **board,int position[2][2],int sizeBoard,int walls,int player,int initialDepth){
    int **visited;
    double value;
    int maxDist = sizeBoard*sizeBoard - (sizeBoard+1);
    int manDist;
    int maxManDist = sizeBoard - 1;
    visited = createVisited(2*sizeBoard,4*sizeBoard);
    int *myDistance,*opDistance;
    myDistance = malloc(sizeof(int));
    opDistance = malloc(sizeof(int));
    if (myDistance == NULL || opDistance == NULL){
        printf("Not Enough Memory.Exiting.\n");
        exit(0);
    }
    int myWinningRow,opWinningRow;
    if (player == 0){
        myWinningRow = 2 *sizeBoard -1;
        opWinningRow = 1;
    }
    else{
        myWinningRow = 1;
        opWinningRow = 2 * sizeBoard -1;
    }

    insert(position[player][0],position[player][1],0);
    visited[position[player][0]/2][position[player][1]/4] = 1;
    findPath(board,visited,position[player][0],position[player][1],2 *sizeBoard,4*sizeBoard,myWinningRow,0,myDistance);             /*BFS to find minimum distance till win.*/
    emptyQueue();
    resetVisited(visited,2 * sizeBoard,4*sizeBoard);


    insert(position[(player+1)%2][0],position[(player+1)%2][1],0);
    visited[position[(player+1)%2][0]/2][position[(player+1)%2][1]/4] = 1;
    findPath(board,visited,position[(player+1)%2][0],position[(player+1)%2][1],2 *sizeBoard,4*sizeBoard,opWinningRow,0,opDistance); /*BFS to find minimum distance till win.*/
    emptyQueue();
    resetVisited(visited,2 * sizeBoard,4*sizeBoard);


    manDist = ((player+1)%2)*((2*sizeBoard - position[player][0])/2) + player*((position[player][0]-1)/2);

    value  = SPP * ((maxDist-(*myDistance))/(double)maxDist) - SPO *((maxDist-(*opDistance))/(double)maxDist);
    value += RD * (((*opDistance) - (*myDistance))/(double)maxDist) + MDP * ((maxManDist - manDist)/(double)maxManDist);

    if (initialDepth % 2 == 1){
        if ((*myDistance)  == 0){
            value = -(INFINITY/2);                                                                                                  /*Those adjustments must be made in order to forbid opponent from winning.They are bound of depth because it's not always the same player choosing a move. */
        }
        if ((*opDistance)  == 1 && initialDepth == 1){
            value = -(INFINITY/2);
        }

    }
    else{
        if ((*opDistance)  == 0){
            value = -(INFINITY/2);
        }
    }
    if (walls == 0){
        value = SPP * ((maxDist-(*myDistance))/(double)maxDist);
    }



    free(myDistance);
    free(opDistance);
    freeVisited(visited,2*sizeBoard);
    return value;


}



MOVE* getLegitMoves(char ** board,int rows,int columns,int playerRow,int playerCol,int player,int position[2][2],int walls[2]){
    int i,j,k,l,counter=0,myWinningRow,opWinningRow,moveNumber;
    MOVE* moveArray;
    moveNumber = 12+2*((rows/2)-1)*((rows/2)-1);
    moveArray = malloc(moveNumber*sizeof(MOVE));
    if (moveArray == NULL){
        printf("Not Enough Memory.Exiting.\n");
        exit(0);
    }
    Walls** possibleWalls;

    if (player == 0){
        myWinningRow = rows -1;
        opWinningRow = 1;
    }
    else{
        myWinningRow = 1;
        opWinningRow = rows -1;
    }

    for(i=0;i<moveNumber;i++){
            moveArray[i].row = 0;
            moveArray[i].col = 0;
            moveArray[i].value = 0;
            moveArray[i].isMove = 0;
            moveArray[i].ori = 0;

    }

    possibleWalls = malloc(((rows/2) -1) * sizeof(Walls *));
    if (possibleWalls == NULL){
        printf("Not Enough Memory.Exiting.\n");
        exit(0);
    }
	for (i=0;i<(rows/2) -1;i++){
		possibleWalls[i] = malloc(((rows/2) -1)*sizeof(Walls));
		if (possibleWalls[i] == NULL){
            printf("Not Enough Memory.Exiting.\n");
            exit(0);
		}
	}
	for(i=0,k=1;i<(rows/2)-1;i++,k+=2){
		for(j=0,l=2;j<(rows/2)-1;j++,l+=4){
			possibleWalls[i][j].row = k;
			possibleWalls[i][j].col = l;
		}
	}


    for (i=0;i<12;i++){
        if (moves[i][4] == 0){
            if(playerRow != moves[i][2] && playerCol != moves[i][3]&&
               (check_Legal_Move(board,rows,columns,playerRow + moves[i][0],playerCol + moves[i][1],playerRow,playerCol))){
                    moveArray[counter].row = playerRow + moves[i][0];
                    moveArray[counter].col = playerCol + moves[i][1];
                    moveArray[counter].value = -2;
                    moveArray[counter].isMove = 1;
                    moveArray[counter].ori = -1;
                    counter++;
            }
        }
        else if (moves[i][4] == 1){
            if((playerRow*moves[i][5] > moves[i][2]*moves[i][5])&&(playerCol*moves[i][6] > moves[i][3]*moves[i][6])&&
               (check_Legal_Move(board,rows,columns,playerRow + moves[i][0],playerCol + moves[i][1],playerRow,playerCol))){
                    moveArray[counter].row = playerRow + moves[i][0];
                    moveArray[counter].col = playerCol + moves[i][1];
                    moveArray[counter].value = -2;
                    moveArray[counter].isMove = 1;
                    moveArray[counter].ori = -1;
                    counter++;
            }
        }
    }

    int legal = 0;
    int **visited;
    visited = createVisited(rows,columns);

        for (i=0;i<(rows/2) -1;i++){
            for(j=0;j<(rows/2) -1;j++){
                if (walls[player] > 0){
                    legal = check_Legal_Wall(board,rows,columns,possibleWalls[i][j].row,possibleWalls[i][j].col,0,walls[player]);   //0 means vertical,1 means horizontal
                    if (legal)
                        legal = tryWall(board,rows,columns,possibleWalls[i][j].row,possibleWalls[i][j].col,position,0,player,visited,walls,myWinningRow); //For me
                    if (legal)
                        legal = tryWall(board,rows,columns,possibleWalls[i][j].row,possibleWalls[i][j].col,position,0,(player+1)%2,visited,walls,opWinningRow); //For opponent
                    if (legal){
                         moveArray[counter].row = possibleWalls[i][j].row;
                         moveArray[counter].col = possibleWalls[i][j].col;
                         moveArray[counter].ori = 0;
                         moveArray[counter].isMove = 0;
                         moveArray[counter].value = -2;
                         counter++;
                        for (l=0;l<3;l++){
                            if (l % 2 == 1)
                                board[possibleWalls[i][j].row + l][possibleWalls[i][j].col + 2] = '+';
                            else
                                board[possibleWalls[i][j].row + l][possibleWalls[i][j].col + 2] = '|';
                        }
                    }
                }


                if (walls[player] > 0){
                    legal = check_Legal_Wall(board,rows,columns,possibleWalls[i][j].row,possibleWalls[i][j].col,1,walls[player]);   /*0 means vertical,1 means horizontal.*/
                    if (legal)
                        legal = tryWall(board,rows,columns,possibleWalls[i][j].row,possibleWalls[i][j].col,position,1,player,visited,walls,myWinningRow); /* For me. */
                    if (legal)
                        legal = tryWall(board,rows,columns,possibleWalls[i][j].row,possibleWalls[i][j].col,position,1,(player+1)%2,visited,walls,opWinningRow); /* For opponent. */
                    if (legal){
                         moveArray[counter].row = possibleWalls[i][j].row;
                         moveArray[counter].col = possibleWalls[i][j].col;
                         moveArray[counter].ori = 1;
                         moveArray[counter].isMove = 0;
                         moveArray[counter].value = -2;
                         counter++;
                        for (l=0;l<7;l++)
                            if (l == 3)
                                board[possibleWalls[i][j].row + 1][(possibleWalls[i][j].col - 1) + l] = '+';
                            else
                                board[possibleWalls[i][j].row + 1][(possibleWalls[i][j].col - 1) + l] = '-';
                    }
                }

            }

        }
        for (i=0;i<(rows/2) -1;i++)
            free(possibleWalls[i]);
        free(possibleWalls);

        freeVisited(visited,rows);
        return moveArray;


}

void alphaBetaUndo(char** board,int position[2][2],int maxPL,int oldRow,int oldCol,int isMove,int ori,int targetRow,int targetCol){
    int l;
    if(isMove){
        if(maxPL == 0){
            board[position[maxPL][0]][position[maxPL][1]] = ' ';
            board[oldRow][oldCol] = 'B';
        }
        else{
            board[position[maxPL][0]][position[maxPL][1]] = ' ';
            board[oldRow][oldCol] = 'W';
        }

        position[maxPL][0] = oldRow;
        position[maxPL][1] = oldCol;
    }

    else{
        if(!ori){
            for (l=0;l<3;l++)
                if (l % 2 == 1)
                    board[targetRow + l][targetCol + 2] = '+';
                else
                    board[targetRow + l][targetCol + 2] = '|';
        }
        else {
            for (l=0;l<7;l++)
                if (l == 3)
                    board[targetRow + 1][(targetCol - 1) + l] = '+';
                else
                    board[targetRow + 1][(targetCol - 1) + l] = '-';
        }
    }
}


int checkWinner(int rows,int currentRow,int player){
if ((player == 0 && currentRow == rows -1) || (player == 1 && currentRow == 1))
    return 1;
return 0;
}

MOVE alphaBeta(char **board,int sizeBoard,int position[2][2],int walls[2],int depth,const int initialDepth,int maxPL,int maximizingPlayer,double alpha,double beta,int maximizer){
    int i;

    MOVE* moveArray;
    MOVE bestMove;
    MOVE tempMove;
    int oldRow,oldCol;
    oldRow = oldCol = 0;
    if(depth == 0 || checkWinner(2*sizeBoard,position[maximizer][0],maximizer)){
        tempMove.value = evaluateMove(board,position,sizeBoard,walls[maximizer],maximizer,initialDepth);
        return tempMove;
    }
    if(maximizingPlayer){
        bestMove.value = -INFINITY;
        bestMove.row = bestMove.col = -1;
        moveArray = getLegitMoves(board,2*sizeBoard,4*sizeBoard,position[maxPL][0],position[maxPL][1],maxPL,position,walls);
        for(i=0;moveArray[i].row != 0;i++){

            if(moveArray[i].isMove){
                oldRow = position[maxPL][0];
                oldCol = position[maxPL][1];


                simpleMove(board,maxPL,2*sizeBoard,moveArray[i].row,moveArray[i].col,position);
                tempMove = alphaBeta(board,sizeBoard,position,walls,depth-1,initialDepth,(maxPL+1)%2,0,alpha,beta,maximizer);
                if (tempMove.value > bestMove.value){
                    bestMove.value = tempMove.value;
                    bestMove.row = moveArray[i].row;
                    bestMove.col = moveArray[i].col;
                    bestMove.isMove = 1;
                    bestMove.ori = moveArray[i].ori;
                }
                if (tempMove.value > alpha){
                    alpha = tempMove.value;
                }
                alphaBetaUndo(board,position,maxPL,oldRow,oldCol,1,-1,moveArray[i].row,moveArray[i].col); //1=isMove, -1=orientation of current move(has no meaning)
                if (beta <= alpha){
                    break;
                }


            }
            else{
                simpleWall(board,moveArray[i].ori,2 * sizeBoard,moveArray[i].row,moveArray[i].col);
                tempMove = alphaBeta(board,sizeBoard,position,walls,depth-1,initialDepth,(maxPL+1)%2,0,alpha,beta,maximizer); //minPlayer == 0
                if (tempMove.value > bestMove.value){
                    bestMove.value = tempMove.value;
                    bestMove.row = moveArray[i].row;
                    bestMove.col = moveArray[i].col;
                    bestMove.isMove = 0;
                    bestMove.ori = moveArray[i].ori;
                }
                if (tempMove.value > alpha){
                    alpha = tempMove.value;
                }

                alphaBetaUndo(board,position,maxPL,oldRow,oldCol,0,moveArray[i].ori,moveArray[i].row,moveArray[i].col); //1=isMove, -1=orientation of current move(has no meaning)

                if (beta <= alpha){
                    break;
                }
            }
        }
        free(moveArray);
        return bestMove;

    }
    else{
        bestMove.value = INFINITY;
        bestMove.row = bestMove.col = -1;
        moveArray = getLegitMoves(board,2*sizeBoard,4*sizeBoard,position[maxPL][0],position[maxPL][1],maxPL,position,walls);
        for(i=0;moveArray[i].row != 0;i++){
            if(moveArray[i].isMove){
                oldRow = position[maxPL][0];
                oldCol = position[maxPL][1];

                simpleMove(board,maxPL,2*sizeBoard,moveArray[i].row,moveArray[i].col,position);
                tempMove = alphaBeta(board,sizeBoard,position,walls,depth-1,initialDepth,(maxPL+1)%2,1,alpha,beta,maximizer);
                if (tempMove.value < bestMove.value){
                    bestMove.value = tempMove.value;
                    bestMove.row = moveArray[i].row;
                    bestMove.col = moveArray[i].col;
                    bestMove.isMove = 1;
                    bestMove.ori = moveArray[i].ori;
                }
                if (tempMove.value < beta){
                    beta = tempMove.value;
                }
                alphaBetaUndo(board,position,maxPL,oldRow,oldCol,1,-1,moveArray[i].row,moveArray[i].col); //1=isMove, -1=orientation of current move(has no meaning)
                if (beta <= alpha){
                    break;
                }
            }
            else{
                simpleWall(board,moveArray[i].ori,2 * sizeBoard,moveArray[i].row,moveArray[i].col);
                tempMove = alphaBeta(board,sizeBoard,position,walls,depth-1,initialDepth,(maxPL+1)%2,1,alpha,beta,maximizer); //minPlayer == 0
                if (tempMove.value < bestMove.value){
                    bestMove.value = tempMove.value;
                    bestMove.row = moveArray[i].row;
                    bestMove.col = moveArray[i].col;
                    bestMove.isMove = 0;
                    bestMove.ori = moveArray[i].ori;
                }
                if (tempMove.value < beta){
                    beta = tempMove.value;
                }
                alphaBetaUndo(board,position,maxPL,oldRow,oldCol,0,moveArray[i].ori,moveArray[i].row,moveArray[i].col); //1=isMove, -1=orientation of current move(has no meaning)
                if (beta <= alpha){
                   break;
                }
            }
        }
        free(moveArray);
        return bestMove;
    }
}




















