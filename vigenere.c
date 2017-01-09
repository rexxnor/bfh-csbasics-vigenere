#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// initialization
//char decryptMessage(char[], char[], char[]); 
//char encryptMessage(char[], char[], char[]); 
////char getKey(char[], char[], char[]); 
//char encryptChar(char, char, char);
//char decryptChar(char, char, char);
//char* getKey(char, char, char);
char* getPassphrase();
char* encryptFile(char[], char[]);
//char* decryptFile(char[], char[]);
//char* hackTheEncryption(char[], char[]);


int main( int argc, char *argv[] ){
	// init vars
	int i, j;
	int decenswitch;
        char file_name[500];
	char passphrase[20];
//	char toencrypt[500];
//	char todecrypt[500];	
//	char outputText[500];
        FILE *fp;
        FILE *fp2;

        // copy arguments into local variables
        // file_name = 
        

        char getPassphrase(){
          printf("What is your passphrase?\n");
          scanf("%s",passphrase);
          printf("%s",passphrase);
          return *passphrase;
        }

        char encryptFile(char filename[], char passphrase[]){
          char ch;
          char encch;
          int i = 0;
          fp = fopen(filename,"r");

          // check for empty file pointer, exit 0 if met
          if( fp = NULL ){
            perror("Error while opening file. \n");
            exit(0);
          }

          // print out input file char by char
          while( ( ch = fgetc(fp) ) != EOF ){
            //printf("%c",ch);
            ch = ch + passphrase[i]; 
            i++;
          }
          fclose(fp);
          //
          //fp2 = fopen(file_name+encrypted,"w");
          //while (){
          //  while(key){
          //    encch = ch + key[i] 
          //    fputc(fp2), encch
          //  }
          //}
          //fclose(fp2);


          return 0;
        }

        // logic for handling command line arguments
        if( argc == 2) {
          *passphrase = getPassphrase();
          encryptFile(argv[1], passphrase);
        } else if(argv[1] == "-d"){
          *passphrase = getPassphrase();
          //decryptFile(argv[2], passphrase);
        } else if ( argc == 4 ){
          if (argv[1] == "-hack"){
            //hackTheEncryption(argv[2],argv[3]);
          }
        } 




}



//
//	// scan for user input
//	printf("Please enter a key - can be omitted\n");
//	scanf("%s",password);
//	printf("Do you want to encrypt or decrypt? 1 = decrypt, 0 = encrypt, 2 = get key \n");
//	scanf("%d",&decenswitch);
//	// switch for decision
//	if( decenswitch == 1 ) {
//		printf("please enter a string to decrypt\n");
//		scanf("%s",todecrypt);
//		while ( todecrypt[i] != 0 ){
//                        // write 1 char into var
//                        // 
//		        outputText[i] = decryptChar(todecrypt[i], password[i], outputText[i]);
//			// printf("%c",outputText[i]);
//			i++;
//		}
//		printf("%s",outputText);
//	} else if( decenswitch == 0 ) {
//		printf("please enter a text to encrypt \n");
//		scanf("%s",toencrypt);
//		*outputText = encryptChar(toencrypt, password, outputText);
//		printf("%s",outputText);
//		//while ( outputText[i] != 0 ){
//		//	printf("%c",outputText[i]);
//		//	i++;
//		//}
//	} else if( decenswitch == 2 ){
//		printf("please enter cleartext\n");
//		scanf("%s",toencrypt);
//		printf("please enter encrypted text\n");
//		scanf("%s",todecrypt);
//		*outputText = getKey(toencrypt, todecrypt, outputText);
//		printf("%s",outputText);
//	}
//}
//
//// encryptMessage function
//char encryptMessage(char inputText[], char key[], char outputText[]){
//	int i = 0;
//	//char outputText[500];
//	// for ( i = 0 ; i < sizeof(inputText)/8; i++ ){
//	while( inputText[i] != 0 ){
//		//inputText[i] += key[i];		
//		outputText[i] = ((inputText[i] + key[i]) % 255);
//		i++;
//	}	
//
//	return outputText;
//}
//
//// decryptMessage function
//char decryptMessage(char inputText[], char key[], char outputText[]){
//	int i = 0;
//	//char outputText[500];
//	while( inputText[i] != 0 ){
//		//inputText[i] -= key[i];		
//		outputText[i] = ((inputText[i] + key[i]) % 255);
//		i++;
//	}
//	return outputText;
//}
//
//// getKey function
////char getKey(char inputClearText[], char inputEncryptedText[], char password[]){
////	int i = 0;
////	//char outputKey[20];
////	while( inputClearText[i] != 0 ){
////		password[i] = ((inputEncryptedText[i] - inputClearText[i]) % 255);
////		i++;
////	}
////	return password;
////}
//
//
//
//
//// encryptChar function
//char encryptChar(char input, char key, char outputText){
//	outputText = ((input + key) % 255);
//	return outputText;
//}
//
//// decryptChar function
//char decryptChar(char input, char key, char outputText){
//	outputText = ((input - key) % 255);
//	return outputText;
//}
//
//// getkey function
//char* getKey(char inputClear, char inputEncrypted, char key){
//        key = ((inputEncrypted - inputClear) % 255);
//	return key;
//}
