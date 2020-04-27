#include<stdio.h>
#include<string.h>

void strip(char *s)
{
	int  i,j;
 
	for(i=0;s[i]==' '||s[i]=='\t';i++);
		
	for(j=0;s[i];i++)
	{
		s[j++]=s[i];
	}
	s[j]='\0';
	for(i=0;s[i]!='\0';i++)
	{
		if(s[i]!=' '&& s[i]!='\t')
				j=i;
	}
	s[j+1]='\0';
}

int main(){
char from[20];
scanf ("%[^\n]%*c", from);
strip(from);
printf("%s",from);

}