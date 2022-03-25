#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void main(int argc ,char **argv)
{

	FILE *fp;
	FILE *fd;  
	char ch,filename[20],s[50];
	int i=0,j=0;

	if(2!=argc)
	{
		printf("Uasge :cc filename \n");
		return;
	}

	fp=fopen(argv[1],"r");
	fd=fopen("./a.out.i","w");//preprocessor file generation(creation)

	if(fp==0)
	{
		printf("Usage: file not present \n");
		return;
	}


	while((ch=fgetc(fp))!=EOF)//for checking and including header file
	{
again: fseek(fd,-i,SEEK_CUR);
       if(ch=='m')
       {

	       i=1;
	       while(1)
	       {		
		       ch=fgetc(fp);
		       if(ch=='a')
		       {i++;
			       ch=fgetc(fp);
			       if(ch=='i')
			       {i++;
				       ch=fgetc(fp);
				       if(ch=='n')
				       {
					       i++;
					fprintf(fd,"%s","main");
					       goto naxt;
				       }
				       else
					       goto again;
			       }
			       else
				       goto again;		
		       }
		       else
			       goto again;		
	       }
       }
       if(ch=='<')
       {

	       while((ch=fgetc(fp))!='>')
	       {
		       filename[i++]=ch;
	       }
	       filename[i]='\0';

	       printf("include filename is %s\n",filename);

	       fprintf(fd,"#include<%s>",filename);
	       fprintf(fd,"\n");
       }
       i=0;

	}
naxt:


	while((ch=fgetc(fp))!=EOF)//for check and remove the comments
	{
		if(ch=='/')
		{
			if((ch=fgetc(fp))=='/')//checking single line comment and remove
			{

				while((ch=fgetc(fp))!='\n')
				{
					ch=' ';
					fputc(ch,fd);
				}

			}

		
			fseek(fp,-1,SEEK_CUR);
			if((ch=fgetc(fp))=='*')//checking multiline comment and remove
			{

back:		while((ch=fgetc(fp))!='*')
		{
			ch=' ';
			fputc(ch,fd);
		}
		if(ch=fgetc(fp)!='/')

			goto back;

			}

			fprintf(fd,"\n");
		}
		else
			fputc(ch,fd);
	}
}