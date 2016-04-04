#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct move{
    int player;
    int moveChoice;
    int row;
    int column;
    int orientation;
    int moveCount;
    struct move* next;
}move;

extern int count;
extern move *moveList_tail;
extern move *moveList_head;
extern int moves[12][7];


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Play move dependencies ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int check_Special_Move(char **board,int rows,int columns,int targetRow,int targetCol,int positionRow,int positionCol){

    int temp = targetCol;

    if ((targetRow == positionRow - 4 && positionCol==temp)){            /*Double up*/
        if (((board[positionRow - 2][positionCol] == 'B' || board[positionRow - 2][positionCol] == 'W' )) && board[positionRow - 3][positionCol] == '-' && board[positionRow - 1][positionCol] == '-')
            return 1;
    }
    else if ((targetRow == positionRow + 4 && positionCol==temp)){       /*Double down*/
        if (((board[positionRow + 2][positionCol] == 'B' || board[positionRow + 2][positionCol] == 'W' )) && board[positionRow + 3][positionCol] == '-' && board[positionRow + 1][positionCol] == '-')
            return 1;
    }
    else if (targetRow == positionRow && positionCol + 8 == temp){       /*Double right*/
        if (((board[positionRow][positionCol + 4] == 'B' || board[positionRow][positionCol + 4] == 'W' )) && board[positionRow][positionCol + 6] == '|' && board[positionRow][positionCol + 2] == '|')
            return 1;
    }
    else if (targetRow == positionRow && positionCol - 8 == temp){       /*Double left*/
        if (((board[positionRow][positionCol - 4] == 'B' || board[positionRow][positionCol - 4] == 'W' )) && board[positionRow][positionCol - 6] == '|' && board[positionRow][positionCol - 2] == '|')
            return 1;
    }
    else if (targetRow == positionRow - 2 && positionCol + 4 == temp){   /*Diagonally right up*/
        if (((board[positionRow - 2][positionCol] == 'B' || board[positionRow - 2][positionCol] == 'W' )) && (board[positionRow - 3][positionCol] == '=' || positionRow - 3 == 0) && board[positionRow - 2][positionCol + 2] == '|' && board[positionRow - 1][positionCol] == '-')
            return 1;
        if (((board[positionRow][positionCol + 4] == 'B' || board[positionRow][positionCol + 4] == 'W' )) && (board[positionRow][positionCol + 6] == 'H' || positionCol + 6 == columns) && board[positionRow - 1][positionCol + 4] == '-' && board[positionRow][positionCol + 2] == '|')
            return 1;
    }
    else if (targetRow == positionRow - 2 && positionCol - 4 == temp){  /*Diagonally left up*/
        if (((board[positionRow - 2][positionCol] == 'B' || board[positionRow - 2][positionCol] == 'W' )) && (board[positionRow - 3][positionCol] == '=' || positionRow - 3 == 0) && board[positionRow - 2][positionCol - 2] == '|' && board[positionRow - 1][positionCol] == '-')
            return 1;
        if (((board[positionRow][positionCol - 4] == 'B' || board[positionRow][positionCol - 4] == 'W' )) && (board[positionRow][positionCol - 6] == 'H' || positionCol - 6 == 0) && board[positionRow - 1][positionCol - 4] == '-' && board[positionRow][positionCol - 2] == '|')
            return 1;
    }
    else if (targetRow == positionRow + 2 && positionCol + 4 == temp){  /*Diagonally right down*/
        if (((board[positionRow][positionCol + 4] == 'B' || board[positionRow][positionCol + 4] == 'W' )) && (board[positionRow][positionCol + 6] == 'H' || positionCol + 6 == columns) && board[positionRow + 1][positionCol + 4] == '-' && board[positionRow + 2][positionCol + 2] == '|')
            return 1;
        if (((board[positionRow + 2][positionCol] == 'B' || board[positionRow + 2][positionCol] == 'W' )) && (board[positionRow + 3][positionCol] == '=' || positionRow + 3 == rows) && board[positionRow + 2][positionCol + 2] == '|'  && board[positionRow + 1][positionCol] == '-')
            return 1;
    }
    else if (targetRow == positionRow + 2 && positionCol - 4 == temp){  /*Diagonally left down*/
        if (((board[positionRow + 2][positionCol] == 'B' || board[positionRow + 2][positionCol] == 'W' )) && (board[positionRow + 3][positionCol] == '=' || positionRow + 3 == rows) && board[positionRow + 2][positionCol - 2] == '|' && board[positionRow + 1][positionCol] == '-')
            return 1;
        if (((board[positionRow][positionCol - 4] == 'B' || board[positionRow][positionCol - 4] == 'W' )) && (board[positionRow][positionCol - 6] == 'H' || positionCol - 6 == 0) && board[positionRow + 1][positionCol - 4] == '-' && board[positionRow][positionCol - 2] == '|')
            return 1;
    }
    else
        return 0;

}



int check_Legal_Move(char **board,int rows,int columns,int targetRow,int targetCol,int positionRow,int positionCol){

    int flag=0,x;


    if (targetRow == positionRow - 2  && positionCol == targetCol ){      /*Up*/
        if (board[positionRow -1][positionCol] == '=' || (board[positionRow - 2][positionCol] == 'W' || board[positionRow - 2][positionCol] == 'B')){
          flag = 1;
        }
    }
    else if ((targetRow == positionRow + 2 && positionCol== targetCol)){  /*Down*/
        if (board[positionRow + 1][positionCol] == '=' ||  (board[positionRow + 2][positionCol] == 'W' || board[positionRow +2][positionCol] == 'B'))
            flag = 1;
    }
    else if (targetRow == positionRow && positionCol + 4 == targetCol){   /*Right*/
        if (board[positionRow][positionCol + 2] == 'H' || (board[positionRow ][positionCol + 4] == 'W' || board[positionRow][positionCol + 4] == 'B'))
            flag = 1;
    }
    else if (targetRow == positionRow && positionCol - 4 == targetCol ){  /*Left*/
        if (board[positionRow][positionCol - 2] == 'H' || (board[positionRow][positionCol - 4] == 'W' || board[positionRow][positionCol - 4] == 'B'))
            flag = 1;
    }
	else if ((x = check_Special_Move(board,rows,columns,targetRow,targetCol,positionRow,positionCol)) == 1)
            return 1;
	else
        flag = 1;
if (flag == 0) return 1;
return 0;

}





/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Play wall dependencies ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int check_Legal_Wall(char **board,int rows,int columns,int targetRow,int targetCol,int isHorizontal,int remainingWalls){
    int flag=0,i=0;

    if (isHorizontal){
        if (targetCol + 5 > columns || targetRow  == rows - 1  || targetRow < 1 )
            flag = 1;
        while(flag == 0 && i < 7){
            if (board[(targetRow + 1)][(targetCol -1) + i] == '=' || board[(targetRow + 1)][(targetCol -1) + i] == 'H')
                flag = 1;
            i++;
        }
    }
    else{
        if (targetCol + 2 >=  columns || targetRow  == rows - 1)
            flag = 1;
        while(flag == 0 && i < 3){
            if (board[targetRow + i][(targetCol + 2)] == '=' || board[targetRow + i][(targetCol + 2)] =='H')
                flag = 1;
                i++;
        }
    }
    if (flag == 0)
        return 1;
return 0;
}


int tryWall(char **board,int rows,int columns,int targetRow,int targetCol,int position[2][2],int choice,int player,int **visited,int walls[2],int winningRow){
    int legal=0,i;
    int *distanceMin;
    if ((distanceMin = malloc(sizeof(int))) == NULL)
        exit(0);
    if (choice == 0){
        insert(position[player][0],position[player][1],0);
        visited[position[player][0]/2][position[player][1]/4] = 1;
        for (i=0;i<3;i++)                                                                                               /*Placing wall in order to check if its legal.*/
            board[targetRow + i][(targetCol + 2)] = 'H';
        legal = findPath(board,visited,position[player][0],position[player][1],rows,columns,winningRow,0,distanceMin);  /*Checking with BFS.*/
        emptyQueue();
        resetVisited(visited,rows,columns);
        free(distanceMin);
        if (legal == 0){
            for (i=0;i<3;i++){                                                                                          /*If not undo it.*/
                if (i % 2 == 1)
                    board[targetRow + i][targetCol + 2] = '+';
                else
                    board[targetRow + i][targetCol + 2] = '|';
            }
            return 0;
        }
        else
            return 1;
    }
    else if (choice == 1){
        insert(position[player][0],position[player][1],0);
        visited[position[player][0]/2][position[player][1]/4] = 1;
        for (i=0;i<7;i++)
            board[targetRow + 1][(targetCol - 1) + i] = '=';
        legal = findPath(board,visited,position[player][0],position[player][1],rows,columns,winningRow,0,distanceMin);
        emptyQueue();
        resetVisited(visited,rows,columns);
        free(distanceMin);

        if (legal == 0){
            for (i=0;i<7;i++)
                if (i == 3)
                    board[targetRow + 1][(targetCol - 1) + i] = '+';
                else
                    board[targetRow + 1][(targetCol - 1) + i] = '-';
            return 0;
        }
        else {
            return 1;
        }
    }

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Simple moves~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void simpleMove(char **board,int player,int rows,int targetRow,int targetCol,int position[2][2]){
    if (player == 0)
        board[targetRow][targetCol] = 'B';
    if (player == 1)
        board[targetRow][targetCol] = 'W';
    board[position[player][0]][position[player][1]] = ' ';
    position[player][0] = targetRow;
    position[player][1] = targetCol;
}


void simpleWall(char **board,int orientation,int rows,int targetRow,int targetCol){
    int i;
    if (orientation == 1){
        for (i=0;i<7;i++)
            board[targetRow + 1][(targetCol - 1) + i] = '=';

    }
    else if (orientation == 0){
        for (i=0;i<3;i++)
            board[targetRow + i][(targetCol + 2)] = 'H';

    }

}



/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Move list dependencies ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


int insertMove(int inpPlayer,int inpMoveChoice,int inpRow,int inpColumn, int inpOrientation){

    move * newMove;
    if ((newMove = malloc(sizeof(move))) == NULL){
        printf("Not Enough Memory.Exiting.");
        exit(0);
    }
    newMove->player = inpPlayer;
    newMove->moveChoice = inpMoveChoice;
    newMove->row = inpRow;
    newMove->column = inpColumn;
    newMove->orientation = inpOrientation;
    newMove->moveCount = count;
    if (moveList_tail != NULL)
        moveList_tail->next = newMove;
    newMove->next = NULL;
    moveList_tail = newMove;
    if (moveList_head == NULL)
        moveList_head = moveList_tail;
    count++;
    return 0;
}



void extractMove(){
    move* tempHead = moveList_head;
    if (tempHead->next==NULL){
        free(tempHead);
        moveList_tail = moveList_head = NULL;
    }
    else{
        while(((tempHead->next)->next)!=NULL){
            tempHead = tempHead->next;
        }
        free(tempHead->next);
        tempHead->next = NULL;
        moveList_tail = tempHead;
    }
    count--;
}


void emptyMoves(){
    while (moveList_tail != NULL)
        extractMove();
    moveList_head = moveList_tail = NULL;
    count = 1;

}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Commands dependencies ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void listcmd(void){
    printf("=\n\nprotocol_version->Info about a tournament.\n\n");
    printf("name -> Name of the program :D\n\n");
    printf("version -> Prints version of the program(not really!)\n\n");
    printf("known_command-> Enter : known_command 'command' to check if command is valid e.g. known_command showboard.\n\n");
    printf("list_commands-> Prints all valid commands.\n\n");
    printf("quit-> Exit.\n\n");
    printf("boardsize-> Enter: boardsize '3-25'. e.g boardsize 9.\n\n");
    printf("clear_board-> Resets the game.\n\n");
    printf("From now on where player is stated it means black/b or white/w.\n\n");
    printf("walls   -> Enter:   'walls number' to set the remaining walls of both players. e.g walls 10.\n\n");
    printf("playmove-> Enter :  'playmove player coordinates' where coordinates are board positions in order to move e.g. playmove white C2.\n\n");
    printf("playwall-> Enter :  'playwall player coordinates orientation'\nwhere coordinates are the same as in playmove and orientation is horizontal or vertical in order to place a wall. e.g playwall white d2 vertical.\n\n");
    printf("genmove -> Enter :  'genmove player' where player is the same as in playmove.Program decides a move for the corresponding player. e.g. genmove white.\n\n");
    printf("undo    -> Enter :  'undo number' where number is the amount of moves to undo. e.g undo 5.\n\n");
    printf("winner  -> Enter :  'winner player' to check if corresponding player has won e.g. winner white.\n\n");
    printf("showboard-> prints the playing board.\n\n");
}

void knowncmd(char command[50]){
    int flag=0;
    if (strcmp(command,"protocol_version")==0||strcmp(command,"name")==0||strcmp(command,"version")==0){
        flag=1;
    }
    else if (strcmp(command,"known_command")==0||strcmp(command,"list_commands")==0||strcmp(command,"quit")==0){
        flag=1;
    }
    else if (strcmp(command,"boardsize")==0||strcmp(command,"clear_board")==0||strcmp(command,"walls")==0){
        flag=1;
    }
    else if(strcmp(command,"playmove")==0||strcmp(command,"playwall")==0||strcmp(command,"genmove")==0){
        flag=1;
    }
    else if(strcmp(command,"undo")==0||strcmp(command,"winner")==0||strcmp(command,"showboard")==0){
        flag=1;
    }
    if (flag)
        printf("= true\n\n");
    else printf("? false\n\n");
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Misc dependencies ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/



int **getMoves(int sizeBoard){

    moves[1][2] =  moves[10][2] = moves[11][2] = 2*sizeBoard - 1;
    moves[2][3] = moves[9][3] = moves [11][3] = 4*sizeBoard - 2;
    moves[5][2] = 2*sizeBoard - 3;
    moves[6][3] = 4*sizeBoard - 6;


}


int depthSelect(int size){
    switch(size) {

    case 3 :
        return 6;
    case 5 :
        return 4;
    case 7 :
        return 3;
    case 9 :
        return 2;
    case 11 :
        return 2;
    case 13 :
        return 1;
    case 15 :
        return 1;
    }

    if (size > 15) return 1;



}



