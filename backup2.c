#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// initialization
char getPassphrase();
char encryptFile(char[], char[]);

int main( int argc, char *argv[] ){
	// init vars
        char file_name[500];
        char *file_name_enc[500];
	char passphrase[20];
        FILE *fp;
        FILE *fp2;
        
        char getPassphrase(){
          printf("What is your passphrase?\n");
          scanf("%s",passphrase);
        }
        
        char *readFile(char *fileName)
        {
          FILE *file = fopen(fileName, "r");
          char *code;
          size_t n = 0;
          int c;
          long size = ftell(file);

          if (file == NULL){
            return NULL; //could not open file
          }

          // determine filesize
          if (fseek(file, 0, SEEK_END) == 0)
          {
              size = ftell(file);
              if (size != -1)              {
                  code = malloc(size);
              }
              // Go back to start of file
              fseek(file, 0, SEEK_SET);
          }     
          while ((c = fgetc(file)) != EOF)
          {
            code[n++] = (char) c;
          }

          // don't forget to terminate with the null character
          code[n] = '\0';        
          return code;
        }

        char encryptFile(char filename[], char passphrase[]){
          char ch;
          char pencch;
          int i = 0;
          char *fuck;
          char *encrypted;
          fuck = readFile(filename);


          //fp = fopen(filename,"r");
              
          
          // concatenate the filename
          *file_name_enc = strcat(filename,".encrypted");
          fp2 = fopen(*file_name_enc,"w");
          if ( fp2 == NULL ){
            perror("Error while opening destination file. \n");
          }

          return 0;
          while ((pencch = fuck++) != EOF){
            encrypted[i++] = (char) pencch;
          }

          fprintf(fp2,encrypted);
          //do {
          //  ch = fgetc(fp);
          //  pencch = ((long) ch + (long) passphrase[i]) % 256;
          //  //printf("%c ",(char) pencch);
          //  printf("%d\n",fp);
          //  printf("%d",fp2);
          //  i++;
          //} while (ch != EOF);
          //fclose(fp);

          return 0;
        }

        // logic for handling command line arguments
        if( argc == 2) {
          getPassphrase();
          printf("%s",passphrase);
          encryptFile(argv[1],passphrase);
        }
        else if(argv[0] == "-d"){
          *passphrase = getPassphrase();
          //decryptFile(argv[2], passphrase);
        } else if ( argc == 4 ){
          if (argv[0] == "-hack"){
            //hackTheEncryption(argv[2],argv[3]);
          }
        } 
}


