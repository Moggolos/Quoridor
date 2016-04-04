#include <stdio.h>
#include <stdlib.h>


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~BFS needed matrix dependencies ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int** createVisited(int rows,int columns){
    int i,j,**visited;
    visited=malloc(rows/2 * sizeof(int *));
    if (visited==NULL){
        printf("Not Enough Memory.Exiting\n\n");
        exit(0);
    }
    for (i=0;i<rows/2;i++){
        visited[i]=malloc((columns/4) * sizeof(int));
        if (visited[i]==NULL) {
            printf("Not Enough Memory.Exiting.\n\n");
            exit(0);
        }
    }
    for (i=0;i<rows/2;i++){
        for (j=0;j<columns/4;j++){
            visited[i][j] = 0;
        }
    }
return visited;
}

void resetVisited(int **visited,int rows,int columns){
    int i,j;
    for (i=0;i<rows/2;i++){
        for (j=0;j<columns/4;j++){
            visited[i][j] = 0;
        }
    }
}
void freeVisited(int **visited,int rows){
    int i;
    for (i=0;i<rows/2;i++){
        free(visited[i]);
    }
    free(visited);

}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Board dependencies ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


void freeboard(char** board,int sizeBoard){
    int i;
    for (i=0;i<2*sizeBoard+1;i++)
        free(board[i]);
    free(board);

}

char** mallocboard(int sizeBoard){
    char** board;
    int i;
    board = malloc((2*sizeBoard + 1) * sizeof(char *));
    if (board == NULL){
        printf("Not Enough Memory.Exiting\n\n");
        exit(0);
    }
    for (i=0;i< 2*sizeBoard + 1  ;i++){
        board[i] = malloc(4*sizeBoard + 1  * sizeof(char));
        if (board[i] == NULL) {
            printf("Not Enough Memory.Exiting.\n\n");
            exit(0);
        }
    }
    return board;
}



void makeboard(char **board,int position[2][2],int sizeBoard) {
    int i,j;

    position[0][0] = 1;                                     /*Position initialization.*/
    position[0][1] = (4*sizeBoard) / 2;
    position[1][0] = (2*sizeBoard) - 1;
    position[1][1] = (4*sizeBoard) / 2;

    for (i=0;i<2*sizeBoard + 1;i++){                        /*Filling the game board.*/
        for (j=0;j<4*sizeBoard + 1;j++){
            if (i % 2 == 0){
                if (j % 4 == 0){
                    board[i][j] = '+';
                }
                else{
                    board[i][j] = '-';
                    }
            }
            else{
                if (j % 4 == 0){
                    board[i][j] = '|';
                }
                else{
                    board[i][j] = ' ';
                }
            }
        }
    }
board[1][((4*sizeBoard) / 2)] = 'B';
board[(2*sizeBoard) - 1][(4*sizeBoard) / 2] = 'W';          /*Ends here.*/

}



