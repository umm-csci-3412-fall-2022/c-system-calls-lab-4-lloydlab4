#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUF_SIZE 1024

bool is_vowel(char c) {
    /*
     * Returns true if c is a vowel (upper or lower case), and
     * false otherwise.
     */
    char* vowels = (char*) "aeiouAEIOU";
    for(int j=0; j<10; j++) {
      if(c == vowels[j]) {
        return true;
      }
    }
    return false;
}

int copy_non_vowels(int num_chars, char* in_buf, char* out_buf) {
    /*
     * Copy all the non-vowels from in_buf to out_buf.
     * num_chars indicates how many characters are in in_buf,
     * and this function should return the number of non-vowels that
     * that were copied over.
     */
    int vowelcount = 0;
    for(int i=0; i<num_chars; i++) {
        if(is_vowel(in_buf[i])) {
            vowelcount++;
        }
    }
    out_buf = (char*) realloc(out_buf, (num_chars - vowelcount)*sizeof(char));
    int pos_in_out_buf = 0;
    for(int i=0; i<num_chars; i++) {
        if(!is_vowel(in_buf[i])) {
            out_buf[pos_in_out_buf] = in_buf[i];
            pos_in_out_buf++;
        }
    }
    return num_chars - vowelcount;
}

void disemvowel(FILE* inputFile, FILE* outputFile) {
    /*
     * Copy all the non-vowels from inputFile to outputFile.
     * Create input and output buffers, and use fread() to repeatedly read
     * in a buffer of data, copy the non-vowels to the output buffer, and
     * use fwrite to write that out.
     */
    char* in_buf = (char*) calloc(BUF_SIZE/sizeof(char), sizeof(char));
    char* out_buf = (char*) calloc(BUF_SIZE/sizeof(char), sizeof(char));
    while(feof(inputFile) == 0) {
        fread(in_buf, sizeof(char), BUF_SIZE/sizeof(char), inputFile);
        int len = copy_non_vowels(BUF_SIZE/sizeof(char), in_buf, out_buf);
        fwrite(out_buf, sizeof(char), len, outputFile);
    }
    free(in_buf);
    free(out_buf);
}

int main(int argc, char *argv[]) {
    // This sets these to `stdin` and `stdout` by default.
    // You then need to set them to user specified files when the user
    // provides files names as command line arguments.
    FILE *inputFile = stdin;
    FILE *outputFile = stdout;

    // Code that processes the command line arguments
    // and sets up inputFile and outputFile.

    disemvowel(inputFile, outputFile);

    return 0;
}
