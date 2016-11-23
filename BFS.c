#include <stdio.h>
#include <stdlib.h>
#include "Utilities.h"

       /* COLUMNS: {RowMod,ColMod,RowRes,ColRes,isSpecial,RowIneqMulti,ColIneqMulti} */

int moves[12][7] =            { {-2,0,1,-1,0,1,1},                              /* Up.           */
                                {2,0,0,-1,0,1, 1},                              /* Down.         */
                                {0,4,-1,0,0,1, 1},                              /* Right.        */
                                {0,-4,-1,2,0,1,1},                              /* Left.         */
                                {-4,0,3,-1,1,1,1},                              /* Double up.    */
                                {4,0,0,-1,1,-1,1},                              /* Double down.  */
                                {0,8,-1,0,1,1,-1},                              /* Double right. */
                                {0,-8,-1,6,1,1,1},                              /* Double left.  */
                                {-2,-4,1,2,0,1,1},                              /* Up left.      */
                                {-2,4,1,0,0,1, 1},                              /* Up right.     */
                                {2,-4,0,2,0,1, 1},                              /* Down left.    */
                                {2,4,0,0,0, 1, 1}  };                           /* Down right.   */






struct Listnode{
    int row,column,distance;
    struct Listnode *next;
};
struct Listnode *list_head=NULL, *list_tail=NULL;


int insert(int currRow,int currCol,int distance){
    struct Listnode *node;
    if ((node = malloc(sizeof(struct Listnode))) == NULL){
        printf("Not Enough Memory.Exiting.");
        exit(0);
    }

    node->row = currRow;
    node->column = currCol;
    node->distance = distance;
    if (list_tail != NULL)
        list_tail->next = node;
    node->next = NULL;
    list_tail = node;
    if (list_head == NULL)
        list_head = list_tail;
    return 0;
}

int extract(){
   struct Listnode *temp;
    if(list_head == NULL){
        printf("Empty list!\n");
        return -1;
    }
    temp = list_head->next;
    free(list_head);
    list_head = temp;
    return 0;
}


void emptyQueue(void){
    while (list_head!=NULL)
        extract();
    list_head = NULL;
    list_tail = NULL;
}




int findPath(char **board,int **visited,int playerRow,int playerCol,int rows,int columns,int winningRow,int distance,int *distanceMin){
        int x=0;
        int flag = 0;
        int i;
        while (list_head != NULL){
            if (list_head->row == winningRow){
                *distanceMin = distance;
                return 1;
            }
            for (i=0;i<12;i++){
                if (moves[i][4] == 0){
                    if(playerRow != moves[i][2] && playerCol != moves[i][3]&&
                       (check_Legal_Move(board,rows,columns,playerRow + moves[i][0],playerCol + moves[i][1],playerRow,playerCol)) &&
                                visited[(playerRow+moves[i][0])/2][(playerCol+moves[i][1])/4]==0){

                                    visited[(playerRow+moves[i][0])/2][(playerCol+moves[i][1])/4]=1;
                                    insert(playerRow+moves[i][0],playerCol+moves[i][1],distance+1);
                    }
                }
                else if (moves[i][4] == 1){
                    if((playerRow*moves[i][5] > moves[i][2]*moves[i][5])&&(playerCol*moves[i][6] > moves[i][3]*moves[i][6])&&
                       (check_Legal_Move(board,rows,columns,playerRow + moves[i][0],playerCol + moves[i][1],playerRow,playerCol)) &&
                                visited[(playerRow+moves[i][0])/2][(playerCol+moves[i][1])/4]==0){

                                    visited[(playerRow+moves[i][0])/2][(playerCol+moves[i][1])/4]=1;
                                    insert(playerRow+moves[i][0],playerCol+moves[i][1],distance+1);
                    }
                }
            }

            /*Special case of BFS where someone blocks all available paths.*/
            for (i=0;i<4;i++){

                    if (playerRow != moves[i][2] && playerCol != moves[i][3] &&
                        (board[playerRow + moves[i][0]][playerCol+moves[i][1]] == 'W' || board[playerRow + moves[i][0]][playerCol+moves[i][1]] == 'B') &&
                        (board[playerRow + moves[i][0]/2][playerCol + moves[i][1] / 2] == '-' || board[playerRow + moves[i][0]/2][playerCol + moves[i][1] / 2] == '|')
                        && visited[(playerRow+moves[i][0])/2][(playerCol+moves[i][1])/4]==0){
                            visited[(playerRow+moves[i][0])/2][(playerCol+moves[i][1])/4]=1;
                            insert(playerRow+moves[i][0],playerCol+moves[i][1],distance);
                            break;
                    }
            }
            /*Ends here.*/
            extract();
            if (list_head == NULL)
                return 0;

            x = findPath(board,visited,list_head->row,list_head->column,rows,columns,winningRow,list_head->distance,distanceMin);
            if (x==1)
                return 1;
        }
return x;
}



