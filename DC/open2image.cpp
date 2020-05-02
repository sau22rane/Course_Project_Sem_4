# include <stdio.h> 
# include <string.h> 
   
int main( ) 
{ 
    FILE *fpread; 
    char dataToBeRead[55];
    
  
    fpread = fopen("Images/city.jpg", "r") ;
      
    if ( fpread == NULL ) 
    { 
        printf( "Good to go...!!!" ) ; 
    } 
    else
    { 
        fscanf (fpread, "%s",dataToBeRead);
        printf( "%s\n" , dataToBeRead );
        /* while( fread ( dataToBeRead, sizeof(dataToBeRead),1, fpread ) != NULL ) 
        { 
            printf( "%s\n" , dataToBeRead );
        } */
          
    } 
    fclose(fpread) ; 
    return 0;         
} 