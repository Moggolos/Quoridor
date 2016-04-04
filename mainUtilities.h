int playmove(char **board,int position[2][2],int sizeBoard,char **cmd);
void playwall(char **board,int sizeBoard,int walls[2],int position[2][2],char **cmd);
void genmove(char **board,int sizeBoard,int position[2][2],int walls[2],int depth,int maxPL,int maxPlayer);
int showboard(char **board,int size,int walls[2]);
void undo(char **board,int rows,int position[2][2],int walls[2],int times,int sizeBoard,int wallNum);
int **getMoves(int sizeBoard);


void listcmd();
void knowncmd(char command[50]);
void toLower(char *inpstring);
void getCommands(char command[50],char **cmd);
int depthSelect(int sizeBoard);
