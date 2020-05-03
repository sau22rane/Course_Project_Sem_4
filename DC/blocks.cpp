#include<stdio.h>
int main(){
    int i = 0;
    loop:{
    for (;i<4;i++){
        int j = 0;
        while(j < 2){
            printf("%d%d ",i,j);
            if(i==2){
            break loop;
            j++;
        }
    }
    }
}