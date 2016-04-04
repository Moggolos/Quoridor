int findPath(char **board,int **visited,int playerRow,int playerCol,int rows,int columns,int winningRow,int distance,int *distanceMin);
int insert(int currRow,int currCol,int distance);
int extract(void);
void emptyQueue(void);
