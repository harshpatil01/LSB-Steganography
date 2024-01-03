#include<stdio.h>
#include<string.h>
//Reading size of image file
int size_of_image(FILE *fp1)
{
	int width, height;
	//Seeking the Width position from the image header
	fseek(fp1, 0x12, SEEK_SET);	
	//Reading the Width position from the image header
	fread(&width, sizeof(int), 1, fp1);	
	//Reading the height position from the image header
	fread(&height, sizeof(int), 1, fp1);	
	//Printing the dimensions
	printf("Dimensions of the Image is %d x %d \n", width, height);
	//Seeking the position to the start
	fseek(fp1, 0L, SEEK_SET);	
	//Returning the size of the input image
	return ((width * height * 3) / 8);
}
//Entering the secret text into the file pointed by file pointer fp2
void secret_text(FILE *fp2, FILE *fp4)
{
	//Declaring character variable
	char ch;
	//secret text file content pointed by file pointer fp4
	fp4 = fopen("secret.txt","r+");

	//Loop will continue until it returns end of file
	//Getting each character one by one from file pointer fp4
	while ((ch = fgetc(fp4))!=EOF)
	{
		//It puts each character of secret text stored in ch at one 		     time into file pointer fp2	
	    putc(ch,fp2);
	}
}

//Extracting the size of the secret message
int secret_text_size(FILE *fp2)
{
	//Declaring variables
	int size_txt;
	//Seeking the end of the secret text from the file pointed by file pointed by fp2
	fseek(fp2, 0L, SEEK_END);
	//Giving out the position of the file pointer fp2 with respect to starting of the file
	size_txt = ftell(fp2);
	//Setting it back to begining
	fseek(fp2, 0L, SEEK_SET);
	//Returning the size of the secret text size
	return size_txt;
}
//Getting bit by bit 
int get_bit(char byte, int bit)
{
	//Returning the byte right shifted by 8 & with 1 to get binary bit of each char byte one by one
	return ((byte >> 8 - bit) & 1);
}

//Encryption of the entire message
void stega_encrypt(FILE *fp1, FILE *fp2, FILE *fp3)
{
	//Declaring variables
	char file_buff = 0, msg_buff = 0, ch;	
	int i;
	int bit_msg;
	//Continue the loop until the secret message ends or receives an EOF 
	while((msg_buff = fgetc(fp2)) != EOF)
	{
		//For loop
		for(i = 1; i <= 8; i++)
		{
			//Temporary variable file_buff storing each byte from file pointer fp1 pointing to the beautiful.bmp image file
			file_buff = fgetc(fp1);
			//Getting the lsb byte of the image byte and storing it into file_byte_lsb
			int file_byte_lsb = (file_buff & 1);
			//Getting the bit of the secret text message being stored in the temporary variable msg_buff
			bit_msg = get_bit(msg_buff, i);
			//If the lsb bit of byte of image is equal to the bit of the secret text message 
			if(file_byte_lsb == bit_msg)
			{
				//writing the secret text byte by byte to file pointed by fp3
				fputc(file_buff, fp3);
			}
			else
			{
				//If its equal to 0 then set the bit to 1
				if(file_byte_lsb == 0)
					file_buff = (file_buff | 1);
				else
					file_buff = (file_buff ^ 1);
				//writing the secret text byte by byte to file pointed by fp3
				fputc(file_buff, fp3);
			}
		}
	}

	//Copying the rest of the data
	while(!feof(fp1))
	{
		char tmp_cpy = fgetc(fp1);
		fputc(tmp_cpy,fp3);

	}
	//If msg_buff i.e secret message file reaches EOF then print the message
	if(msg_buff == EOF)
		printf(" Secret Message Encrypted Successfully \n ");
	else
		printf("Encryption not successful \n ");

}



//Encryption for strings i.e the secret text file data
void string_encrypt(char *str,FILE *fp1, FILE *fp3)
{
	//Declaring variables
	char file_buff, msg_buff;	
	int i, j = 0;
	int bit_msg;
	//Continue the loop until the secret message which is a string receives a null character
	while((msg_buff = str[j]) != '\0')
	{
		for(i = 1; i <= 8; i++)
		{
			//Temporary variable file_buff storing each byte from file pointer fp1 pointing to the beautiful.bmp image file
			file_buff = fgetc(fp1);
			//getting the lsb byte of the image byte and storing it into file_byte_lsb
			int file_byte_lsb = (file_buff & 1);
			//Getting the bit of the secret text message being stored in the temporary variable msg_buff
			bit_msg = get_bit(msg_buff, i);
			//If the lsb bit of byte of image is equal to the bit of the secret text message 
			if(file_byte_lsb == bit_msg)
			{
				//writing the secret text byte by byte to file pointed by fp3
				fputc(file_buff, fp3);
			}
			else
			{
				//If its equal to 0 then set the bit to 1
				if(file_byte_lsb == 0)
				
					file_buff = (file_buff | 1);
				else
					file_buff = (file_buff ^ 1);
				//writing the secret text byte by byte to file pointed by fp3
				fputc(file_buff, fp3);
			}
		}
		//Incrementing the j variable so that the string reaches till the null character
		j++;
	}
}
//Encryption the size of the files
void size_encrypt(int num,FILE *fp1, FILE *fp3)
{
	//Declaring variables
	char file_buff;	
	int i, j = 0;
	int bit_msg;
	//Encryption Logic for the size of the files
	for(i = 1; i <= 8; i++)
	{
		file_buff = fgetc(fp1);

		int file_byte_lsb = (file_buff & 1);

		bit_msg = get_bit(num, i);

		if(file_byte_lsb == bit_msg)
		{
			fputc(file_buff, fp3);
		}
		else
		{
			if(file_byte_lsb == 0)
				file_buff = (file_buff | 1);
			else
				file_buff = (file_buff ^ 1);

			fputc(file_buff, fp3);
		}
	}

}

//Defining the Encode Function
int Encode(char *argv_2,char *argv_3,char *argv_4)
{
	//Declaring File Pointers
	FILE *fp1, *fp2, *fp3 , *fp4;

	//Opening the image file in r+ mode 
	//If the pointer returns a NULL pointer print error message
	if((fp1 = fopen(argv_2, "r+")) == NULL) 
	{
		printf(" %s could not be opened \n", argv_2);
		return 1;
	}
	
	
	//Storing the size of image in the variable size_image by passing fp1 i.e FILE Pointer with the help of size_of_image
	int size_image = size_of_image(fp1);
	//Printing the message about the storage capacity of the beautiful.bmp image
	printf("Total %d Characters can be stored in %s \n", size_image, argv_2);

	//fp2 will store the pointer and opening of the secret file in w+ mode i.e creation of a new file 
	fp2=fopen("files.txt","w+");	
	

	//Entering the message	
	printf("Secret Text being entered \n ");
	//Calling the function
	secret_text(fp2,fp4);

	//Calculating the size of secret text size
	int size_txt = secret_text_size(fp2);

	//Printing the size of the secret message
	printf("The size of secret message is %d \n ",size_txt);

	//Comparing Image Size with secret text 
	if(size_image < size_txt)
	{
		printf(" The Size Of secret Message Exceeds the Size of ima		   ge \n");
		return 1;
	}

	//Opening the destination or the output file in w= mode
	fp3 = fopen(argv_4, "w+");
	//If the pointer returns null then print error message
	if (fp3== NULL) 
	{
		//Printing the error message
	 fprintf(stderr, "Cannot create the destination file %s\n",argv_4);	
	 return 1;
	}

	//Copying the 54 byte header file
	//Declaring variables
	int i, c = 0;
	char tmp_cpy;
	//fp1 pointer pointing to the start of the image(beautiful.bmp) header
	rewind(fp1);
	
	for(i = 0;i < 54; i++)
	{
		//Copying the 54 bytes
		tmp_cpy = fgetc(fp1);
		//Storing it in file pointed by fp3
		fputc(tmp_cpy,fp3);
		//Incrementing c variable
		c++;
	}

	//If i == c then print 54 image header bytes successfully copied
	if(i == c)
		printf(" Sucessfully copied 54 header bytes \n");
	else
	{
		printf("Image Header not successfully copied \n");
		exit(1);
	}

	//Declaring Magic String
	printf("Encryption of Magic String in Progress .... \n  ");
	char magic_str[10]= "#*";
	//Declaring variables
	int size;
	//Calculating the size of the magic_str
	size = strlen(magic_str);
	//Printing the message of the magic_str
	printf("Size Of The Magic string is ==> %d\n", size);
	//Calling the size_encrypt function and passing the size of magic_str along with FILE Pointer fp1 and fp3 to encrypt the size of magic_str
	size_encrypt(size,fp1,fp3);
	//Calling the size_encrypt function and passing the magic_str along with FILE Pointer fp1 and fp3 to encrypt the magic string 
	string_encrypt(magic_str,fp1,fp3);
	//Print the message of the magic string encrypted successfully
	printf("Magic String Encrypted successfully\n");

	

	//Calling the function to encrypt size of the message 
	size_encrypt(size_txt,fp1,fp3);
	//Calling the function stega_encrypt the entire message message
	stega_encrypt(fp1,fp2,fp3);

	//Cleaning the file streams before the program exits
	fclose(fp1);	
	fclose(fp2);
	fclose(fp3);

	return 0;

}
