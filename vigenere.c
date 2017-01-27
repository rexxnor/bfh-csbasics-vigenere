#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// define function in advance
void crypt(FILE *fp_r, FILE *fp_w, unsigned char *passphrase, int encswitch);

// scan passphrase from user
void get_passphrase(unsigned char *pass) {
    printf("What is your passphrase?\n");
    scanf("%s", pass);
    printf("Done.\n");
}

// function to open filepointers for read and write
void get_filepointers(char *read_f, char *write_f, unsigned char *passphrase, int encswitch) {
    // define file pointers
    FILE *fp_r = NULL, *fp_w = NULL;

    // open file pointers
    fp_r = fopen(read_f, "r");
    fp_w = fopen(write_f, "w");

    // call crypt function
    crypt(fp_r, fp_w, passphrase, encswitch);

    // close file pointers
    if (fp_r != NULL) {
        fclose(fp_r);
    }
    if (fp_w != NULL) {
        fclose(fp_w);
    }
}

// function to open filepointers for read
void get_filepointers_read(char *read_f, char *write_r2, unsigned char *passphrase, int encswitch) {
    // define file pointers
    FILE *fp_r = NULL, *fp_w = NULL;

    // open file pointers
    fp_r = fopen(read_f, "r");
    fp_w = fopen(write_r2, "r");

    // call crypt function
    crypt(fp_r, fp_w, passphrase, encswitch);

    // close file pointers
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
    // variable definition
    unsigned char c;
    unsigned char d;
    int size;
    int i = 0;
    int u = 0;
    int charbuffer = sizeof(passphrase);
    
    // decide whether to encrypt, decrypt or hack
    if (encswitch == 0){
        // sets size to read bytes and checks if size of last read char is not 0
        while (size = sizeof(char) == fread(&c, sizeof(char), 1, fp_r) != 0) {
            // reset counter if passphrase has two sequential null characters
            if(passphrase[i] == 0 && passphrase[i + 1] == 0){
                i = 0;
            }
            // add passphrase char and modulo so it does not get too big
            c = (c + passphrase[i]) % 256;
            // write char to filepointer
            fwrite(&c, sizeof(char), 1, fp_w);
            // increment i 
            i++;
        }
        printf("Successfully encrypted!\n");
    } else if (encswitch == 1){
        // sets size to read bytes and checks if size of last read char is not 0
        while (size = sizeof(char) == fread(&c, sizeof(char), 1, fp_r) != 0) {
            // reset counter if passphrase has two sequential null characters
            if(passphrase[i] == 0 || passphrase[i] == '\0'){
                i = 0;
            }
            // subtract passphrase char and modulo so it does not get too big
            //
            c = (c - passphrase[i]) % 256;
            // write char to filepointer
            fwrite(&c, sizeof(char), 1, fp_w);
            // increment i 
            i++;
        }
        printf("Successfully decrypted!\n");
    } else if (encswitch == 2){
        // read two files in memory and subtract char by char
        // define unsigned char variable and allocate memory for it
        unsigned char * content_r = malloc(30 * sizeof(char));
        // set i = 0 for new loop
        i = 0;
        // read from filepointer until null is read
        while (size = sizeof(char) == fread(&c, sizeof(char), 1, fp_r) != 0) {
            // limit loops to 30 for max passphrase length
            if ( i > 30){
                break;
            }
            // set arraycontents to current char and increment i
            content_r[i] = c;
            i++;
        }

        // define unsigned char variable and allocate memory for it
        unsigned char * content_w = malloc(30 * sizeof(char));
        // set i = 0 for new loop
        i = 0;
        // read from filepointer until null is read
        while (size = sizeof(char) == fread(&d, sizeof(char), 1, fp_w) != 0) {
            // limit loops to 30 for max passphrase length
            if ( i > 30 ){
                break;
            }
            // set arraycontents to current char and increment i
            content_w[i] = d;
            i++;
        }

        // define unsigned char variable and allocate memory for it
        unsigned char * solution = malloc(30 * sizeof(char));
        // loop through the first 30 chars
        for( u = 0 ; u < 30 ; u++ ){
            // assign char for char the casted value of passphrase character
            solution[u] = (unsigned char)((256 + content_w[u] - content_r[u]) % 256);
        }

        // lots of print for nice asthetics
        printf("Your passphrase was:\n");

        // loop to determine repetition in the passphrase
        // set i to zero for the loop
        i = 0; 
        for( u = 1 ; u < 30 ; u++ ){
            // if first and character at u match
            if( solution[i] == solution[u] ){
                // if second and character at u + 1 match
                if (solution[i + 1] == solution[u + 1]){
                   // set the u equals zero character
                   solution[u] = '\0';
                   // set adjacent character also to zero
                   solution[u + 1] = '\0'; 
                } 
            }
        }

        // loop through the solution array to display hacked passphrase
        for( u = 0 ; u < 30 ; u++ ){
            // if there are not two nulls in a row, print current char
            if( solution[u] != '\0' && solution[u + 1] != '\0'){
                printf( "%c", solution[u]);
            } else {
                // will print the last character that is valid
                printf( "%c", solution[u]);
                // if there are two nulls in a row, break the printing
                break; 
            }
        }

        // spacer for nice looks
        printf("\n"); 

    }
}

// taken from http://stackoverflow.com/questions/2736753/how-to-remove-extension-from-file-name
// removes file ending from a char array
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

// main method
int main(int argc, char *argv[]) {
    // define vars
    unsigned char *passphrase;
    char *filename;
    char *encrypted_filename;
    int encswitch = 0;
    int i = 0;
    // allocate memory for passphrase
    passphrase = malloc(30 * sizeof(char));

    // writes zero characters to passphrase memory
    for( i = 0 ; i < 30 ; i++ ){
        passphrase[i] = '\0';
    }
    // allocate memory for filenames
    filename = malloc(50 * sizeof(char));
    encrypted_filename = malloc(60 * sizeof(char));
    // if construct depending on argument count
    if(argc == 2){
        // gets passphrase from user
        get_passphrase(passphrase);
        // prints out passphrase again for remembering
        printf("Your passphrase is %s\n", passphrase);
        // sets filename to first argument of execution
        filename = argv[1];
        // puts filename in encrypted_filename
        strcat(encrypted_filename,filename);
        // adds .encrypted to the encrypted filename
        strcat(encrypted_filename,".encrypted");

        // calls method to get_filepointers set the rest in motion
        get_filepointers(filename,encrypted_filename,passphrase,encswitch);
        
        // return a normal value for successfull execution
        return 0;

    } else if(argc == 3){
        // gets passphrase from user
        get_passphrase(passphrase);
        // prints out passphrase again for remembering
        printf("Your passphrase is %s\n", passphrase);
        // set encrypted filename to argument
        encrypted_filename = argv[2]; 
        // generates filename withoud .encrypted and saves it in var
        filename = remove_file_ending(encrypted_filename);
        // sets the switch to 1 for decryption
        encswitch = 1;

        // calls method to get_filepointers set the rest in motion
        get_filepointers(encrypted_filename,filename,passphrase,encswitch);
        
        // return a normal value for successfull execution
        return 0;

    } else if (argc == 4){
        // set filenames to arguments
        filename = argv[2]; 
        encrypted_filename = argv[3];
        
        // sets the switch to 2 for hacking the encryption
        encswitch = 2;

        // calls different method from above to get two read filepointers
        get_filepointers_read(filename,encrypted_filename,passphrase,encswitch);
        
        // return a normal value for successfull execution
        return 0;

    } else{
        // if there are not enough arguments these messages will be displayed
        printf("Invalid command line arguments supplied\n");
        printf("Valid: filename (to encrypt)\n");
        printf("Valid: -d filename (to decrypt)\n");
        printf("Valid: -hack filename enc-filename (to hack passphrase)\n");
        // return a error code
        return 1;
    }
}

