#include <stdio.h>
#include<string.h>

void encode_nrzi(char*,char*,int);
void decode_nrzi(char*,char*,int);

int main()
{
    char byte[10] ,k[10],temp1, encoded[10],decoded[10];
    int i,val,prev,flag,temp=0,j;

    scanf("%s",byte);
    encode_nrzi(byte,encoded,10);
    decode_nrzi(encoded,decoded,10);
    printf("%s",decoded);

    /* for(j = 0;j<9;j++){
        printf("\n%d\n",byte[j]);
        temp=0;
        for(i = 0; i <= 9; i ++){
            
            val = (byte[j] >> i) & 0x01;
            if(i==0){
                prev = val;
                temp = (prev<<i);
            }
            else{
                if(val == 0){
                    temp = temp+(prev<<i);
                }
                if(val == 1){
                    if(prev == 0)
                        prev =1;
                    else
                        prev = 0;
                    temp = temp+(prev<<i);
                }
            }
            printf("%d",prev);
        }
        k[j] = temp;
    }
    printf("%s",byte);

    for(j = 0;j<9;j++){
        printf("\n%c\n",k[j]);
        temp=0;
        for(i = 0; i <= 7; i ++){
            
            val = (k[j] >> i) & 0x01;
            if(i==0){
                prev = val;
                temp = prev;
            }
            else{
                if(val == prev){
                    temp = temp+(0<<i);
                    prev = val;
                    printf("g");
                }
                else{
                    temp = temp+(1<<i);
                    prev = val;
                }
            }
            printf("%d%d ",val,temp);
        }
        printf("\n%d\n",temp);
        
        byte[j] = temp;
    }
    printf("%s",byte); */

    return 0;
}

void encode_nrzi(char *byte, char *encoded, int size){
    int i,j, temp, prev, val;
    for(j = 0;j<size;j++){
        temp=0;
        for(i = 0; i <= 7; i ++){
            
            val = (byte[j] >> i) & 0x01;
            if(i==0){
                prev = val;
                temp = (prev<<i);
            }
            else{
                if(val == 0){
                    temp = temp+(prev<<i);
                }
                if(val == 1){
                    if(prev == 0)
                        prev =1;
                    else
                        prev = 0;
                    temp = temp+(prev<<i);
                }
            }
        }
        encoded[j] = temp;
    }
}

void decode_nrzi(char *encoded, char *decoded, int size){
    int i,j,val,prev,temp;
    for(j = 0;j<size;j++){
        temp=0;
        for(i = 0; i <= 7; i ++){
            
            val = (encoded[j] >> i) & 0x01;
            if(i==0){
                prev = val;
                temp = prev;
            }
            else{
                if(val == prev){
                    temp = temp+(0<<i);
                    prev = val;
                }
                else{
                    temp = temp+(1<<i);
                    prev = val;
                }
            }
        }
        decoded[j] = temp;
    }
}