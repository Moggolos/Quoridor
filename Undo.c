#include <stdio.h>
#include <stdlib.h>
#include "Utilities.h"

void makeboard(char **board,int position[2][2],int sizeBoard);

typedef struct move{
    int player;
    int moveChoice;
    int row;
    int column;
    int orientation;
    int moveCount;
    struct move* next;
}move;
int count = 1;

move *moveList_tail=NULL,*moveList_head=NULL;

void undo(char **board,int rows,int position[2][2],int walls[2],int times,int sizeBoard,int wallNum){
    int upToWhen;
    int i;
    move* tempHead = moveList_head;
    upToWhen = (count-1) - times;

    if (upToWhen<0){
        printf("? cannot undo\n\n");
        fflush(stdout);
        return;
    }
    else if(upToWhen==0){
        makeboard(board,position,sizeBoard);                                    /*Just makeboard no need to do anything else.*/
        walls[0] = walls[1] = wallNum;
        while(moveList_tail != NULL){
            extractMove();
        }
        printf("=\n\n");
        fflush(stdout);
        return;
    }
    else {
        makeboard(board,position,sizeBoard);
        walls[0] = walls[1] = wallNum;
    }

    for(i=0;i<times;i++){
        extractMove();
    }
    for(i=0;i<upToWhen;i++){
        if(tempHead->player==0){                                                /*Black*/
            if(tempHead->moveChoice==0){
                simpleMove(board,0,rows,tempHead->row,tempHead->column,position);
            }
            if(tempHead->moveChoice==1){
                simpleWall(board,tempHead->orientation,rows,tempHead->row,tempHead->column);
                walls[0]--;
            }
        }
        else{                                                                   /*White*/
            if(tempHead->moveChoice==0)
                simpleMove(board,1,rows,tempHead->row,tempHead->column,position);
            if(tempHead->moveChoice==1){
                simpleWall(board,tempHead->orientation,rows,tempHead->row,tempHead->column);
                walls[1]--;
            }
        }

        tempHead=tempHead->next;
    }
    printf("=\n\n");
    fflush(stdout);

}



