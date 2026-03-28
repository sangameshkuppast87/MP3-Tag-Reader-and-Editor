#ifndef MP3_H
#define MP3_H
#include<stdio.h>

int validate(int argc, char* argv[], char str[][10], int* index);
void mp3_view(char* argv[]);
void mp3_edit(char* argv[], int index);
int convert(int size);
void help_menu();

#endif