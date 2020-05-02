# include <stdio.h> 
# include <string.h> 
   
int main( ) 
{ 
    FILE *fpread, *fpwrite ; 
    char dataToBeRead[55]; 
    
  
    fpread = fopen("Images/city.jpg", "r") ;
    fpwrite = fopen("Images/trial.jpg", "w") ; 
      
    if ( fpread == NULL ) 
    { 
        printf( "GfgTest.c file failed to open." ) ; 
    } 
    else
    { 
        //fprintf(fpwrite,"%s","Rane");
        fwrite("Rane",1,sizeof("Rane"),fpwrite);
        printf("The file is now opened.\n") ; 
          
        while( fread ( dataToBeRead, sizeof(dataToBeRead),1, fpread ) != NULL ) 
        { 
            printf( "%s\n" , dataToBeRead ) ; 
            dataToBeRead[0]+=1;
            dataToBeRead[0]-=1;
            fwrite(dataToBeRead,1,sizeof(dataToBeRead),fpwrite);
        }
        char str[] = "Rane";
        fwrite(str,1,sizeof(dataToBeRead),fpwrite);
        
        fclose(fpread) ; 
        fclose(fpwrite);
        printf("Data successfully read from file GfgTest.c\n"); 
        printf("The file is now closed.") ; 
    } 
    return 0;         
} 