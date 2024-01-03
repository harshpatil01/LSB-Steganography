#include "common.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"encode.c"
#include"decode.c"

//Arguments being passed through cmd line
int main(int argc,char *argv[])
{
	//Declaring variables
    int i;
    char *argv_2,*argv_3,*argv_4;


    switch(argc)
    {
			//Comparing the second argument with the '-E'
	case 8 :	if(!strcmp(argv[1],"-E"))
			{
			    for (i = 2; i < 8; i++)
			    {
					//Comparing the argument with the '-i'
				if (!strcmp(argv[i],"-i"))
				//Moving that argument in the argv_2
				    argv_2 = argv[i+1];
					//Comparing the argument with the '-s'
				if (!strcmp(argv[i],"-s"))
				//Moving that argument in the argv_3
				    argv_3 = argv[i+1];
				//Comparing the argument with the '-s'
				if (!strcmp(argv[i],"-o"))
				//Moving that argument in the argv_4
				    argv_4 = argv[i+1];
			    }
				//Calling the encode function			    
			    Encode(argv_2, argv_3, argv_4);
			    break;
			}
				//Comparing the argument with the '-D'		
	case 6 :	if(!strcmp(argv[1], "-D"))
				{
			    for (i = 2; i < 6; i++)
			    {
				//Comparing the argument with the '-i'	
				if (!strcmp(argv[i],"-i"))
				    argv_2 = argv[i+1];
				//Comparing the argument with the '-o'		
				if (!strcmp(argv[i],"-o"))
				    argv_4 = argv[i+1];
			    }			    
				//Calling the Decode function		
			    Decode(argv_2, argv_4);
			    break;
			}

	default : 
		printf("Its an error \n ");
		printf("For EXECUTION =>");
		printf("ENCODING  => ./a.out -E -i <input.bmp> -s <secret.txt> -o <output.bmp> \n");
		printf("DECODING =>  ./a.out -D -i <output.bmp> -o <output_text.txt> \n");
   }	
}
