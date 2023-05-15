#pragma once

#define OPTIONS_COUNT 1

void parseOptions(int argc, char** argv);
void readOption(char option[], char value[]);
char* getOption(char option[]);

typedef struct {
    char letter[3];
    char word[30];
    char value[255];
} Option;