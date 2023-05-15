#pragma once

#define OPTIONS_COUNT 1
#define LETTER_LENGTH 3
#define WORD_LENGTH 30
#define VALUE_LENGTH 255

void parseOptions(int argc, char** argv);
void setOption(char option[], char value[]);
char* getOption(char option[]);

typedef struct {
    char letter[LETTER_LENGTH];
    char word[WORD_LENGTH];
    char *value;//[VALUE_LENGTH];
} Option;