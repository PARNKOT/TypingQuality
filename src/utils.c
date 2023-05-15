#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"


int countWords(const char* str) {
    int words_counter = 0;
    int is_previous_symbol = 1;

    if (*str == ' ' || *str == ',') {
        is_previous_symbol = 0;
    }

    while (*str != '\0') {
        if (*str == ' ' || *str == ',') {
            if (is_previous_symbol) {
                ++words_counter;
                is_previous_symbol = 0;
            }
        } else {
            if (!is_previous_symbol) {
                is_previous_symbol = 1;
            }
        }

        ++str;
    }

    if (is_previous_symbol) {
        ++words_counter;
    }

    return words_counter;
}

char** splitString(const char* str, int Nwords) {
    // if (Nwords == -1) {
    //     Nwords = countWords(str);
    // }    
}

char* strtok_my(char* str, char delim, int* start_pos) {
    int end_pos;
    char* token;

    while(str[*start_pos] == delim) {
        ++(*start_pos);
    }

    if (str[*start_pos] == '\0') {
        return NULL;
    }

    end_pos = *start_pos + 1;

    while(str[end_pos] != delim && str[end_pos] != '\0') {
        ++end_pos;
    }

    token = (char*)malloc(sizeof(char)*(end_pos-(*start_pos) + 1));
    strncpy(token, str+(*start_pos), end_pos - (*start_pos));
    *(token + (end_pos-(*start_pos))) = '\0';

    *start_pos = end_pos;

    return token;
}

#ifdef MAIN
int main(int argc, char** argv) {
    printf("Must be words: 12\n");
    printf("Count words: %i\n", countWords(", Hello my friend, i am glad to see you , go with me ,"));
    int start = 0;
    char* str = "I love Sonya!";
    
    printf("Word1: %s\n", strtok_my(str, ' ', &start));
    printf("New start pos: %i\n", start);

    printf("Word1: %s\n", strtok_my(str, ' ', &start));
    printf("New start pos: %i\n", start);

    printf("Word1: %s\n", strtok_my(str, ' ', &start));
    printf("New start pos: %i\n", start);

    printf("Word1: %s\n", strtok_my(str, ' ', &start));
    printf("New start pos: %i\n", start);
}
#endif

