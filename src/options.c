#include <string.h>
#include "options.h"


extern Option options[OPTIONS_COUNT];


void parseOptions(int argc, char** argv) {
    char option[30];

    for(int i = 1; i < argc; ++i) {
        if(strlen(argv[i]) > 1) {
            if(argv[i][0] == '-') {
                strcpy(option, argv[i]);
            } else {
                readOption(option, argv[i]);
            }
            
        }
    }
}

void readOption(char option[], char value[]) {
    for(int i = 0; i < OPTIONS_COUNT; ++i) {
        if(strcmp(options[i].letter, option) == 0 || strcmp(options[i].word, option) == 0) {
            strcpy(options[i].value, value);
        }
    }
}

char* getOption(char option[]) {
    for(int i = 0; i < OPTIONS_COUNT; ++i) {
        if(strcmp(options[i].letter, option) == 0 || strcmp(options[i].word, option) == 0) {
            return options[i].value;
        }
    }

    return NULL;
}