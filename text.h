#ifndef TEXT_H
#define TEXT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char *buffer;
    int gap_start;
    int gap_end;
    int capacity;
} TextBuffer;

TextBuffer* textbuffer_new(int capacity, bool capped);
TextBuffer* textbuffer_create_new();
TextBuffer* textbuffer_create_new_capped(int capacity);
void textbuffer_destroy(TextBuffer* tb);
void textbuffer_print(TextBuffer* tb);
void textbuffer_move_gap(TextBuffer* tb, int position);
void textbuffer_insert(TextBuffer* tb, char c);
void textbuffer_del_char(TextBuffer* tb);
void textbuffer_move_cursor(TextBuffer* tb, int delta);

#endif