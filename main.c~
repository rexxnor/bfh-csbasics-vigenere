#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "encryption.h"


void encrypt(FILE *fp_r, FILE *fp_w);

void get_passphrase(char *pass) {
    printf("What is your passphrase?\n");
    scanf("%s", pass);
    printf("Done.\n");
}


void get_filepointers(const char *read_f, const char *write_f) {
    FILE *fp_r = NULL, *fp_w = NULL;

    fp_r = fopen(read_f, "r");
    fp_w = fopen(write_f, "w");

    encrypt(fp_r, fp_w);

    if (fp_r != NULL) {
        fclose(fp_r);
    }
    if (fp_w != NULL) {
        fclose(fp_w);
    }
}


void encrypt(FILE *fp_r, FILE *fp_w) {
    assert(fp_r != NULL);
    assert(fp_w != NULL);
    char c;
    int size;

    while (size = sizeof(char) == fread(&c, sizeof(char), 1, fp_r) != 0) {
        fwrite(&c, sizeof(char), 1, fp_w);
    }
}

int main(int argc, char *argv) {
    char *passphrase;

    passphrase = malloc(20 * sizeof(char));
    get_passphrase(passphrase);
    printf("Your passphrase is %s\n", passphrase);
    get_filepointers("f.src", "f.dst");
}
