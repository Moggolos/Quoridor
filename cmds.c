#include <stdio.h>
#include <string.h>
#include <ctype.h>

void toLower(char *inpstring){

    int i;
    for(i=0; i<strlen(inpstring); i++) {
        inpstring[i]=tolower(inpstring[i]);
    }


}


void getCommands(char command[50],char **cmd){
    int i;
    char *p;
    for(i=0;i<50;i++){
        if (command[i] == '\t')
            command[i]=' ';
        if (command[i]=='#'){
            command[i]='\0';
            break;
        }
    }

    p = strtok(command," \n");
    if (p!= NULL)
        strcpy(cmd[0],p);
    for(i=1;i<4;i++){
        p = strtok(NULL," \n");
        if (p != NULL)
            strcpy(cmd[i],p);
        else
            strcpy(cmd[i],"\0"); //For initialization.
    }
}

