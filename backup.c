#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// initialization
char getPassphrase();
char encryptFile(char[], char[]);
//char *readFile(char *fileName);
//char* decryptFile(char[], char[]);
//char* hackTheEncryption(char[], char[]);


int main( int argc, char *argv[] ){
	// init vars
	int i, j;
	int decenswitch;
        char file_name[500];
        char *file_name_enc[500];
	char passphrase[20];
        FILE *fp;
        FILE *fp2;

        //char *readFile(char *fileName)
        //{
        //  FILE *file = fopen(fileName, "r");
        //  char *code;
        //  size_t n = 0;
        //  int c;

        //  if (file == NULL){
        //    return NULL; //could not open file
        //  }

        //  // determine filesize
        //  if (fseek(fp, 0, SEEK_END) == 0)
        //  {
        //      long size = ftell(fp);
        //      if (size != -1)
        //      {
        //          printf("%d",size);
        //          code = malloc(size);
        //      }
        //      // Go back to start of file
        //      fseek(fp, 0, SEEK_SET);
        //  }     


        //  while ((c = fgetc(file)) != EOF)
        //  {
        //      
        //    code[n++] = (char) c;
        //  }

        //  // don't forget to terminate with the null character
        //  code[n] = '\0';        

        //  return code;
        //}

        char getPassphrase(){
          printf("What is your passphrase?\n");
          scanf("%s",passphrase);
          printf("Blau");
        }

        char encryptFile(char filename[], char passphrase[]){
          char ch;
          char pencch;
          int i = 0;
          //int *fcontents;
          //fcontents = readFile(argv[1]);
          //fp2 = fopen(*file_name_enc,"w");
               
          //if (fseek(fp, 0, SEEK_END) == 0)
          //{
          //    long size = ftell(fp)
          //    if (size != -1)
          //    {
          //        // succesfully got size
          //        malloc(size);
          //        char temp1[];
          //    }
          //    // Go back to start of file
          //    fseek(fp, 0, SEEK_SET);
          //}     

          //if (fseek(fp2, 0, SEEK_END) == 0)
          //{
          //    long size = ftell(fp2)
          //    if (size != -1)
          //    {
          //        // succesfully got size
          //        malloc(size);
          //    }
          //    // Go back to start of file
          //    fseek(fp2, 0, SEEK_SET);
          //}

 

          if( fp == NULL ){
            perror("Error while opening file. \n");
          }
          // concatenate the filename
          *file_name_enc = strcat(filename,".encrypted");
          if ( fp2 == NULL){
            perror("Error while opening destination file. \n");
          }

          
          do {
            ch = fgetc(fp+i);
            pencch = ((long) ch + (long) passphrase[i]) % 256;
            // write this char at start of file until end
            //&(fp2+i) = pencch;
            //fprintf(fp2,"%c",pencch);
            printf("%c ",(char) pencch);
            printf("%d\n",fp);
            printf("%d",fp2);
            i++;
          } while (ch != EOF);
          fclose(fp);

          return 0;
        }

        // logic for handling command line arguments
        if( argc == 2) {
          *passphrase = getPassphrase();
          printf("%s",*passphrase);
          //encryptFile(argv[1], passphrase);
        }
        /*else if(argv[0] == "-d"){
          *passphrase = getPassphrase();
          //decryptFile(argv[2], passphrase);
        } else if ( argc == 4 ){
          if (argv[0] == "-hack"){
            //hackTheEncryption(argv[2],argv[3]);
          }
        } */
}


