int** createVisited(int rows,int columns);
void resetVisited(int **visited,int rows,int columns);
void freeVisited(int **visited,int rows);
void freeboard(char** board,int sizeBoard);
char** mallocboard(int sizeBoard);
void makeboard(char **board,int position[2][2],int sizeBoard);
