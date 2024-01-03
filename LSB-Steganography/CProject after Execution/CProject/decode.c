#include<stdio.h>
#include<string.h>
//Decryption Size
void size_decryption(FILE *pf1, int *size_txt)
{
	//Declaring variables
	int file_buff = 0, i;
	int ch, bit_msg;
	for (i = 0; i < 8; i++)
	{
		//Getting single byte from File Pointer pf1 pointed to output/modified image 
		ch = fgetc(pf1);
		//AND operation of ch and 1
		bit_msg = (ch & 1);
		//If its non-zero then enter the loop
		if (bit_msg)
		{
			file_buff = (file_buff << 1) | 1;
		}
		else
		{
			file_buff = file_buff << 1;
		}
	}
	*size_txt = file_buff;
}

//String Decryption
void string_decryption(FILE *pf1,char *string,int size)
{
	//Declaring variables
	int file_buff=0, i, j=0, k=0;
	int ch, bit_msg;
	for (i = 0; i < (size * 8); i++)
	{
		//Incrementing
		j++;
		//Getting each byte from pf1
		ch = fgetc(pf1);
		//AND Operation
		bit_msg = (ch & 1);
		//If loop
		if (bit_msg)
		{
			file_buff = (file_buff << 1) | 1;
		}
		else
		{
			file_buff = file_buff << 1;
		}
		//1 byte is one character in the secret message
		//j when reaching 8 enters the loop
		if ( j == 8)
		{
			//The byte/bits stored is converted into character and stored in string one by one
			string[k] =(char)file_buff; 
			//Initialization of j back to zero and continuing the loop
			j=0;
			//Incrementing k variable to store the next character
			k++;
			//Initialization of file_buff back to zero
			file_buff = 0;
		}
	}
	//Adding a null character after a string
	string[k] = '\0';
}


//Decryption of  the secret message
void secret_decryption(int size_txt, FILE *pf1, FILE *pf2)
{
	//Declaring variables
	int file_buff=0, i, j = 0, k = 0;
	int ch,bit_msg;
	//Declaring output charcacter array storing the output i.e the decoded message
	char output[250] = {0};
	for (i = 0; i < (size_txt * 8); i++)
	{
		//Incrementing the j variable
		j++;
		//Getting single byte at a time
		ch = fgetc(pf1);
		//AND Operation of the fetched character and 1
		bit_msg = (ch & 1);
		//If non-zero enter the loop
		if (bit_msg)
		{
			file_buff = (file_buff << 1) | 1;
		}
		else
		{
			file_buff = file_buff << 1;
		}
		//1 byte is one character in the secret message
		//j when reaching 8 enters the loop
		if ( j == 8)
		{
			//Character stored in the file_buff being copied  in the file stream pointed by  FILE Pointer pf2
			putc(file_buff, pf2);
			//Output i.e the secret message is being stored in the output character array
			output[k++] = file_buff;
			//Initialization of j back to zero and continuing the loop
			j=0;
			//Initialization of file_buff back to zero
			file_buff = 0;
		}
	}
	printf(" Secret Text is %s \n", output);
}

//Defining the Decode Function
int Decode(char *argv_2, char *argv_4)
{
	//Declaring the file pointers
	FILE *pf1, *pf2;
	//Declaring variables
	int size, size1, size_txt;
	
	//Opening the modified/encoded image file in read mode
	if((pf1 = fopen(argv_2, "r")) == NULL) 
	{
		printf("%s cannot be opened\n", argv_2);
		return 1;
	}
	//File pointer fp1 pointing to the 54 th position i.e the just the bit after the image header
	fseek(pf1,54 ,SEEK_SET);
	
	//Opening/Creation of the output.txt file fpr storing the secret message
	if((pf2 = fopen(argv_4, "w+")) == NULL) 
	{
		printf("%s cannot be opened \n", argv_4);
		return 1;
	}

	//Declaring the magic string
	char magic_string[20];
	char magic_string1[20] = "#*";

	
	//Calling functions to decrypt the magic string 
	//Calling the size_decryption function with file pointer pf1 and address of the size as the arguments
	size_decryption(pf1,&size);
	//Calling the string_decryption function with file pointer pf1 , magic_string and the size as the arguments
	string_decryption(pf1,magic_string,size);

	//Declaring temp variable
	int temp;
	//strcmp to compare the magic string whether they match or not
	temp = strcmp(magic_string1, magic_string);
	
	//If its 1 then enter the loop
	if(temp)
	{
		//Magic Strings entered do not match 
		printf("Entered Magic Strings do not match \n");
		return 0;
	}
	else
		//Magic Strings entered match
		printf("Entered Magic Strings match and are accepted \n");

	
	//Calling functions to decrypt the secret text message
	//First calling size_decryption to decrypt the size
	size_decryption(pf1, &size_txt);
	//Second calling the secret_decryption  to decrypt the secret message
	secret_decryption(size_txt, pf1, pf2);
	
	
	//Printing the message
	printf("The secret text is copied to %s \n", argv_4);

	//Closing the file pointer after the operation is successful
	fclose(pf1);

}
