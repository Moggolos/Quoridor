
int check_Special_Move(char **board,int rows,int columns,int targetRow,int targetCol,int positionRow,int positionCol);
int check_Legal_Move(char **board,int rows,int columns,int targetRow,int targetCol,int positionRow,int positionCol);
int check_Legal_Wall(char **board,int rows,int columns,int targetRow,int targetCol,int isHorizontal,int remainingWalls);
int tryWall(char **board,int rows,int columns,int targetRow,int targetCol,int position[2][2],int choice,int player,int **visited,int walls[2],int winningRow);
void simpleMove(char **board,int player,int rows,int targetRow,int targetCol,int position[2][2]);
void simpleWall(char **board,int orientation,int rows,int targetRow,int targetCol);
int insertMove(int inpPlayer,int inpMoveChoice,int inpRow,int inpColumn, int inpOrientation);
void extractMove();
void emptyMoves();
