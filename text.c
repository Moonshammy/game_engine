#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INITIAL_BUFFER_SIZE 128
#define GAP_SIZE 16

typedef struct{
    char *buffer;
    int gap_start;
    int gap_end;
    int capacity;
    bool capped;
} TextBuffer;

TextBuffer* textbuffer_new(int capacity, bool capped){
    if (capacity < 0) capacity *= -1;
    TextBuffer* tb = malloc(sizeof(TextBuffer));
    tb->buffer = malloc(capacity);
    tb->gap_start = 0;
    if (capacity > 16) tb->gap_end = GAP_SIZE;
    else tb->gap_end = capacity;
    tb->capacity = capacity;
    tb->capped = capped;
    memset(tb->buffer, 0, tb->capacity);
    return tb;
}

TextBuffer* textbuffer_create_new(){
    return textbuffer_new(INITIAL_BUFFER_SIZE, false);
}

//Max capacity is 16
TextBuffer* textbuffer_create_new_capped(int capacity){
    if (capacity > 16) capacity = 16;
    return textbuffer_new(capacity, true);
}




void textbuffer_destroy(TextBuffer* tb){
    free(tb->buffer);
    free(tb);
}

void textbuffer_print(TextBuffer* tb){
    for (int i = 0; i < tb->gap_start; i++){
        putchar(tb->buffer[i]);
    }
    for (int i = tb->gap_end; i < tb->capacity; i++){
        putchar(tb->buffer[i]);
    }
    putchar('\n');
}

char* textbuffer_to_char(TextBuffer *tb){
    char *final = malloc(tb->capacity-(tb->gap_end - tb->gap_start));
    memcpy(final, tb->buffer,tb->capacity);
    return final;
}

void textbuffer_move_gap(TextBuffer* tb, int position){
    if (position < 0 || position > tb->gap_start + (tb->capacity - tb->gap_end)) return;

    if (position < tb->gap_start){
        int move_size = tb->gap_start - position;
        memmove(tb->buffer + tb->gap_end - move_size, tb->buffer + position, move_size);
        tb->gap_start = position;
        tb->gap_end -= move_size;
    }

    if (position > tb->gap_end){
        int move_size = position - tb->gap_start;
        memmove(tb->buffer + tb->gap_start, tb->buffer + tb->gap_end, move_size);
        tb->gap_start += move_size;
        tb->gap_end += move_size;
    }
}

void textbuffer_insert(TextBuffer* tb, char c){
    if(tb->gap_start == tb->gap_end && tb->capped == false){
        int new_capacity = tb->capacity + GAP_SIZE;
        char *new_buffer = malloc(new_capacity);
        int new_gap_end = tb->gap_end + GAP_SIZE;

        memcpy(new_buffer, tb->buffer, tb->gap_start);
        memcpy(new_buffer + new_gap_end, tb->buffer + tb->gap_end, tb->capacity - tb->gap_end);

        free(tb->buffer);
        tb->buffer = new_buffer;
        tb->capacity = new_capacity;
        tb->gap_end = new_gap_end;
    }    
    tb->buffer[tb->gap_start++] = c;
}

void textbuffer_del_char(TextBuffer* tb){
    if(tb->gap_start > 0){
        tb->gap_start--;
    }
}

void textbuffer_move_cursor(TextBuffer* tb, int delta){
    textbuffer_move_gap(tb, tb->gap_start + delta);
}