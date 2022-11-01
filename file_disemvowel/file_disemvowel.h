#ifndef FILE_DISEMVOWEL_H_GUARD
#define FILE_DISEMVOWEL_H_GUARD

#include <stdio.h>
#include <stdbool.h>

bool is_vowel(char c);

int copy_non_vowels(int num_chars, char* in_buf, char* out_buf);

void disemvowel(FILE* inputFile, FILE* outputFile);

int main(int argc, char *argv[]);

#endif
