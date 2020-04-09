# include <stdio.h> 
# include <string.h> 
   
int main( ) 
{ 
    FILE *fpread, *fpwrite ; 
    char dataToBeRead[55]; 
    
  
    fpread = fopen("Images/city.jpg", "rb") ;
    fpwrite = fopen("Images/trial.jpg", "wb") ; 
      
    if ( fpread == NULL ) 
    { 
        printf( "GfgTest.c file failed to open." ) ; 
    } 
    else
    { 
          
        printf("The file is now opened.\n") ; 
          
        while( fread ( dataToBeRead, sizeof(dataToBeRead),1, fpread ) != NULL ) 
        { 
            printf( "%s\n" , dataToBeRead ) ; 
            fwrite(dataToBeRead,1,sizeof(dataToBeRead),fpwrite);
         } 
          
        fclose(fpread) ; 
        fclose(fpwrite);
        printf("Data successfully read from file GfgTest.c\n"); 
        printf("The file is now closed.") ; 
    } 
    return 0;         
} 