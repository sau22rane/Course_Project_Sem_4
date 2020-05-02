#include <stdio.h>
#include<string.h>

void encode_nrzi(char*,char*,int);
void decode_nrzi(char*,char*,int);
void encode_manchester(char*,char*,int);
void decode_manchester(char*,char*,int);
void encode_diff_manchester(char*,char*,int);
void decode_diff_manchester(char*,char*,int);

int main()
{
    char byte[10] ,k[10],temp1, nrz_encoded[10],decoded[10],manchester_encoded[20];
    int i,val,prev,flag,temp=0,j;

    scanf("%s",byte);
    encode_nrzi(byte,nrz_encoded,10);
    decode_nrzi(nrz_encoded,decoded,10);
    printf("%s\n",decoded);

    encode_manchester(byte,manchester_encoded,10);
    decode_manchester(manchester_encoded,decoded,10);
    printf("%s\n",decoded);
    encode_diff_manchester(byte,manchester_encoded,10);
    decode_diff_manchester(manchester_encoded,decoded,10);
    printf("%s\n",decoded);

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

void encode_manchester(char *byte, char *encoded, int size){
    int i,j, temp1, temp2, prev, val,k;
    for(j = 0;j<size;j++){
        temp1=0;
        temp2 = 0;
        for(i = 0; i <= 7; i ++){
            
            val = (byte[j] >> i) & 0x01;
            if(i<4){
                if(val == 0){
                    temp1 = temp1+(1<<(i*2));
                    temp1 = temp1+(0<<(i*2+1));
                }
                if(val == 1){
                    temp1 = temp1+(0<<(i*2));
                    temp1 = temp1+(1<<(i*2+1));             
                }
            }
            else{
                k = i-4;
                if(val == 0){
                    temp2 = temp2+(1<<(k*2));
                    temp2 = temp2+(0<<(k*2+1));
                }
                if(val == 1){
                    temp2 = temp2+(0<<(k*2));
                    temp2 = temp2+(1<<(k*2+1));            
                }
            }
        }
        encoded[j*2] = temp1;
        encoded[j*2+1] = temp2;
    }
}

void decode_manchester(char *encoded, char *decoded, int size){
    int i,j,val,prev,temp,k;
    for(j = 0;j<size;j+=2){
        temp=0;
        for(i = 0; i <= 15; i+=2){
            
            if(i<8){
                val = (encoded[j] >> i) & 0x01;
                
                if(val == 0){
                    temp = temp+(1<<(i/2));
                }
                else{
                    temp = temp+(0<<(i/2));
                }
            }
            else{
                k=i-8;
                val = (encoded[j+1] >> k) & 0x01;
                
                if(val == 0){
                    temp = temp+(1<<(i/2));
                }
                else{
                    temp = temp+(0<<(i/2));
                }
            }
        }
        decoded[j/2] = temp;
    }
}

void encode_diff_manchester(char *byte, char *encoded, int size){
    int i,j, temp1, temp2, prev = 0, val,k;
    for(j = 0;j<size;j++){
        temp1=0;
        temp2 = 0;
        for(i = 0; i <= 7; i ++){
            
            val = (byte[j] >> i) & 0x01;
            if(i<4){
                if(prev == 1){
                    if(val == 0){
                        temp1 = temp1+(0<<(i*2));
                        temp1 = temp1+(1<<(i*2+1));
                        prev = 0;
                    }
                    if(val == 1){
                        temp1 = temp1+(1<<(i*2));
                        temp1 = temp1+(0<<(i*2+1));               
                    }
                }
                else{
                    if(val == 0){
                        temp1 = temp1+(1<<(i*2));
                        temp1 = temp1+(0<<(i*2+1));
                        prev = 1;
                    }
                    if(val == 1){
                        temp1 = temp1+(0<<(i*2));
                        temp1 = temp1+(1<<(i*2+1));           
                    }
                }
            }
            else{
                k = i-4;
                if(prev == 1){
                    if(val == 0){
                        temp2 = temp2+(0<<(k*2));
                        temp2 = temp2+(1<<(k*2+1));
                        prev = 0;
                    }
                    if(val == 1){
                        temp2 = temp2+(1<<(k*2));
                        temp2 = temp2+(0<<(k*2+1));           
                    }
                }
                else{
                    if(val == 0){
                        temp2 = temp2+(1<<(k*2));
                        temp2 = temp2+(0<<(k*2+1));
                        prev = 1;
                    }
                    if(val == 1){
                        temp2 = temp2+(0<<(k*2));
                        temp2 = temp2+(1<<(k*2+1));        
                    }
                }
            }
        }
        encoded[j*2] = temp1;
        encoded[j*2+1] = temp2;
    }
}

void decode_diff_manchester(char *encoded, char *decoded, int size){
    int i,j,val,prev = 0,temp,k;
    for(j = 0;j<size;j+=2){
        temp=0;
        for(i = 0; i <= 15; i+=2){
            
            if(i<8){
                val = (encoded[j] >> i) & 0x01;
                if(prev == 0){
                    if(val == 0){
                        temp = temp+(1<<(i/2));
                    }
                    else{
                        temp = temp+(0<<(i/2));
                        prev = 1;
                    }
                }
                else{
                    if(val == 0){
                        temp = temp+(0<<(i/2));
                        prev = 0;
                    }
                    else{
                        temp = temp+(1<<(i/2));
                    }
                }
            }
            else{
                k=i-8;
                val = (encoded[j+1] >> k) & 0x01;
                if(prev == 0){
                    if(val == 0){
                        temp = temp+(1<<(i/2));
                    }
                    else{
                        temp = temp+(0<<(i/2));
                        prev = 1;
                    }
                }
                else{
                    if(val == 0){
                        temp = temp+(0<<(i/2));
                        prev = 0;
                    }
                    else{
                        temp = temp+(1<<(i/2));
                    }
                }
            }
        }
        decoded[j/2] = temp;
    }
}