#include <stdio.h>
#include <string.h>

#define INITIAL_BUFFER_SIZE 128
#define GAP_SIZE 16

typedef struct{
    char *buffer;
    int gap_start;
    int gap_end;
    int capacity;
} TextBuffer;

TextBuffer* textbuffer_create_new(){
    TextBuffer* tb = malloc(sizeof(TextBuffer));
    tb->buffer = INITIAL_BUFFER_SIZE;
    tb->gap_start = 0;
    tb->gap_end = GAP_SIZE;
    tb->capacity = INITIAL_BUFFER_SIZE;
    memset(tb->buffer, 0, tb->capacity);
    return tb;

}

void textbuffer_destroy(TextBuffer* tb){
    free(tb->buffer);
    free(tb);
}

void textbuffer_print(TextBuffer* tb){
    for (int i = 0; i < tb->gap_start; i++){
        putchar(tb->buffer[i]);
    }
    for (int i = tb->gap_end; i > tb->capacity; i++){
        putchar(tb->buffer[i]);
    }
    putchar('\n');
}

void textbuffer_move_gap(TextBuffer* tb, int position){
    if (position < 0 || position > tb->gap_start + (tb->capacity - tb->gap_end)) return;

    if (position < tb->gap_start){
        int move_size = tb->gap_start - position;
    }
}