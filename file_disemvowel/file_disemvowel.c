#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUF_SIZE 128 

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
    int pos_in_out_buf = 0;
    for(int i=0; i<num_chars; i++) {
        if(!is_vowel(in_buf[i])) {
            out_buf[pos_in_out_buf] = in_buf[i];
            pos_in_out_buf++;
        }
    }
    out_buf[pos_in_out_buf+1] = '\0';
    return num_chars - vowelcount+1;
}

void disemvowel(FILE* inputFile, FILE* outputFile) {
    /*
     * Copy all the non-vowels from inputFile to outputFile.
     * Create input and output buffers, and use fread() to repeatedly read
     * in a buffer of data, copy the non-vowels to the output buffer, and
     * use fwrite to write that out.
     */
    char* in_buf = (char*) calloc(BUF_SIZE, sizeof(char));
    char* out_buf = (char*) calloc(BUF_SIZE, sizeof(char));
    bool run = true;
    for(int j=0; run; j++) {
        if(fgets(in_buf, BUF_SIZE-1, inputFile) == NULL) {
            run = false;
            free(in_buf);
            free(out_buf);
        } else {
            int len = copy_non_vowels(BUF_SIZE-1, in_buf, out_buf);
            for(int i=0; i<len; i++) {
                if(out_buf[i] != '\0') {
                    fputc(out_buf[i], outputFile);
                } else {
                    i=len;
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
    // This sets these to `stdin` and `stdout` by default.
    // You then need to set them to user specified files when the user
    // provides files names as command line arguments.
    FILE *inputFile;
    FILE *outputFile;

    if(argc == 3) {
        inputFile = fopen(argv[1], "r");
        outputFile = fopen(argv[2], "w+");
    } else
    if(argc == 2) {
        inputFile = fopen(argv[1], "r");
        outputFile = stdout;
    } else {
        inputFile = stdin;
        outputFile = stdout;
    }

    // Code that processes the command line arguments
    // and sets up inputFile and outputFile.

    disemvowel(inputFile, outputFile);

    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
