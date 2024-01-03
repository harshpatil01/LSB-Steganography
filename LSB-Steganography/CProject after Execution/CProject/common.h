#include<stdio.h>

//Reading size of image file
int size_of_image(FILE *fp1);

//Entering the secret etxt into the file pointed by file pointer fp2
void secret_text(FILE *fp2, FILE *fp4);


//Extracting the size of the secret message
int secret_text_size(FILE *fp2);

//Getting bit by bit 
int get_bit(char byte, int bit);

//Encryption of the entire message
void stega_encrypt(FILE *fp1, FILE *fp2, FILE *fp3);

//Encryption for strings i.e the secret text file data
void string_encrypt(char *str,FILE *fp1, FILE *fp3);

//Encryption the size of the files
void size_encrypt(int num,FILE *fp1, FILE *fp3);

/* decryption of sizes */
void size_decryption(FILE *pf1, int *size_txt);

/* decryption of strings*/
void string_decryption(FILE *pf1,char *strng,int size);

/* decryption of secret message*/
void secret_decryption(int size_txt,FILE *pf1, FILE *pf2);
