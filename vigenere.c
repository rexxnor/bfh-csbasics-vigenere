#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void crypt(FILE *fp_r, FILE *fp_w, unsigned char *passphrase, int encswitch);

void get_passphrase(unsigned char *pass) {
    printf("What is your passphrase?\n");
    scanf("%s", pass);
    printf("Done.\n");
}

void get_filepointers(char *read_f, char *write_f, unsigned char *passphrase, int encswitch) {
    FILE *fp_r = NULL, *fp_w = NULL;

    fp_r = fopen(read_f, "r");
    fp_w = fopen(write_f, "w");

    crypt(fp_r, fp_w, passphrase, encswitch);

    if (fp_r != NULL) {
        fclose(fp_r);
    }
    if (fp_w != NULL) {
        fclose(fp_w);
    }
}

void get_filepointers_read(char *read_f, char *write_r2, unsigned char *passphrase, int encswitch) {
    FILE *fp_r = NULL, *fp_w = NULL;

    fp_r = fopen(read_f, "r");
    fp_w = fopen(write_r2, "r");

    crypt(fp_r, fp_w, passphrase, encswitch);

    if (fp_r != NULL) {
        fclose(fp_r);
    }
    if (fp_w != NULL) {
        fclose(fp_w);
    }
}

void crypt(FILE *fp_r, FILE *fp_w, unsigned char *passphrase, int encswitch) {
    // if expression is false, aborts execution
    assert(fp_r != NULL);
    assert(fp_w != NULL);
    unsigned char c;
    unsigned char d;
    unsigned int r=42;
    //printf("%d this is r\n",r);
    int size;
    int i = 0;
    int charbuffer = sizeof(passphrase);
    

    if (encswitch == 0){
        // sets size to read bytes and checks if size of last read char is not 0
        while (size = sizeof(char) == fread(&c, sizeof(char), 1, fp_r) != 0) {
            // writes char to file pointer
            c = (c + passphrase[i]) % 256;
            fwrite(&c, sizeof(char), 1, fp_w);
            i++;
            i % charbuffer;
        }
        printf("Successfully encrypted!");
    } else if (encswitch == 1){
        // sets size to read bytes and checks if size of last read char is not 0
        while (size = sizeof(char) == fread(&c, sizeof(char), 1, fp_r) != 0) {
            // writes char to file pointer
            c = (c - passphrase[i]) % 256;
            fwrite(&c, sizeof(char), 1, fp_w);
            i++;
            i % charbuffer;
        }
        printf("Successfully decrypted!");
    } else if (encswitch == 2){
        // sets size to read bytes and checks if size of last read char is not 0




        unsigned char * content_r = malloc(42 * sizeof(char));
        i = 0;
        while (size = sizeof(char) == fread(&c, sizeof(char), 1, fp_r) != 0) {
            if ( i >20)
                break;
            content_r[i] = c;
            i++;
        }
        printf("\n");
        //printf("length of content_r: %d\n", sizeof(content_r));
        int u=0;
        for( u=0; u<20; u++)
            printf( "%4d  ", content_r[u] );




        unsigned char * content_w = malloc(42 * sizeof(char));
        i = 0;
        while (size = sizeof(char) == fread(&d, sizeof(char), 1, fp_w) != 0) {
            if ( i >20)
                break;
            content_w[i] = d;
            i++;
        }
        printf("\n");
        //printf("length of content_w: %d\n", sizeof(content_w));
        for( u=0; u<20; u++)
            printf( "%4d  ", content_w[u] );





        unsigned char * solution = malloc(42 * sizeof(char));
        for( u=0; u<20; u++ )
            solution[u] = (unsigned char)((255 + content_w[u] - content_r[u]) % 255);

        printf("\nSolution:\n");
        printf("###############################\n");
        printf("# HACKED BY rexxnor & vimja   #\n");
        printf("###############################\n");
        for( u=0; u<20; u++ )
            printf( "%c\n", solution[u] );
        printf("\n\n\n");
        /*
        for( u=0; u <20; u++ ){
            // reads in char of second file as well
            fread(&c, sizeof(char),1,fp_r);
            fread(&d, sizeof(char),1,fp_w);
            // determines passphrase
            //r=98;
            //printf("%d this is r\n",r);
            //printf("%d\n",(d-c));
            //r = ((d - c)) % 256;

            //printf("%d this is r\n",r);
            //r=22;
            //printf("%d this is r\n",r);
            printf("c: %d\n", c);
            printf("d: %d\n", d);
            
            if(i < 18){
                passphrase[i] = (char)(c - d + 256) % 256;
            } else{
                break;
            }
            i++;
        }
        */
        //while (i < 20) {
        //    assert(fp_r != NULL);
        //    assert(fp_w != NULL);
        //    // determines passphrase
        //    printf("%c",&c + i);
        //    passphrase[i % 20] = (c + i);
        //    //printf("%c\n",passphrase[i]);
        //    i++;
        //}
        /*
        for ( i = 0; i < 20; i++){
            printf("%d\n",passphrase[i]);
        }
        */
        //printf("Your passphrase is: %s ",passphrase);
    }
}

// taken from http://stackoverflow.com/questions/2736753/how-to-remove-extension-from-file-name
char *remove_file_ending(char* mystr) {
    char *retstr;
    char *lastdot;
    if (mystr == NULL)
         return NULL;
    if ((retstr = malloc (strlen (mystr) + 1)) == NULL)
        return NULL;
    strcpy (retstr, mystr);
    lastdot = strrchr (retstr, '.');
    if (lastdot != NULL)
        *lastdot = '\0';
    return retstr;
}

int main(int argc, char *argv[]) {
    // define var for passphrase
    unsigned char *passphrase;
    char *filename;
    char *encrypted_filename;
    int encswitch = 0;
    int i = 0;
    // allocate memory for passphrase
    passphrase = malloc(20 * sizeof(char));
    for( i=0; i<20; i++ ){
        passphrase[i] = '\0';
    }
    filename = malloc(50 * sizeof(char));
    encrypted_filename = malloc(50 * sizeof(char));
    //
    // make filenames
    // input filenames for source and destination
    if(argc == 2){
        // gets passphrase from user
        get_passphrase(passphrase);
        printf("Your passphrase is %s\n", passphrase);
        // sets filename to first argument
        filename = argv[1];
        // puts filename in encrypted_filename
        strcat(encrypted_filename,filename);
        // adds .encrypted to the encrypted filename
        strcat(encrypted_filename,".encrypted");

        get_filepointers(filename,encrypted_filename,passphrase,encswitch);

    } else if(argc == 3){
        // gets passphrase from user
        get_passphrase(passphrase);
        printf("Your passphrase is %s\n", passphrase);

        encrypted_filename = argv[2]; 
        filename = remove_file_ending(encrypted_filename);
        // sets the switch to 1 for decryption
        encswitch = 1;

        get_filepointers(encrypted_filename,filename,passphrase,encswitch);

    } else if (argc == 4){
        filename = argv[2]; 
        encrypted_filename = argv[3];
        
        // sets the switch to 2 for hacking the encryption
        encswitch = 2;

        get_filepointers_read(filename,encrypted_filename,passphrase,encswitch);

    } else{
        printf("Invalid command line arguments supplied\n");
        printf("Valid: filename, -d enc-filename, -hack filename, enc-filename\n");
        return 1;
    }
}

