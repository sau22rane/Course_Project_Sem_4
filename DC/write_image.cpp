#include<stdio.h>
int main(){
    FILE *fp;
    char dataToBeRead[2];
    fp = fopen("Images/trial.jpg","rb");
    fread ( dataToBeRead, sizeof(dataToBeRead),1, fp );
    printf("%s\n",dataToBeRead);
    fclose(fp);
    return 0;
}