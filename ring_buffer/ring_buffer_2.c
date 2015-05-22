#include <stdio.h>
#include <stdlib.h>  // calloc


typedef struct {
    int size;
    int start;
    int end;
    int* elems;
} RingBuffer;


void rbInit(RingBuffer* rb, int size) {
    rb->size = size;
    rb->start = 0;
    rb->end = 0;
    rb->elems = (int*) calloc(size, sizeof(RingBuffer));
}


int rbIsFull(RingBuffer* rb) {
    // return abs(rb->end - rb->start) == rb->size;
    return rb->end - rb->start == rb->size;
}


int rbIsEmpty(RingBuffer* rb) {
    return rb->start == rb->end;
}



void rbPrint(RingBuffer* rb) {
    for (int i = 0; i < rb->size; i++) {
        printf("%d ", rb->elems[i]);
    }
    printf("\nsize: %d, start: %d, end: %d, empty: %d, full: %d\n", 
        rb->size, rb->start, rb->end, rbIsEmpty(rb), rbIsFull(rb));
}


int rbNext(RingBuffer* rb, int p) {
     /* start and end pointers incrementation is done modulo 2*size */
    // return (p + 1) % (2 * rb->size);
    return p + 1;
}


void rbWrite(RingBuffer* rb, int elem) {
    rb->elems[rb->end % rb->size] = elem;
    if (rbIsFull(rb)) {
        /* full, start pos has been overwrited, move start pos forward */
        rb->start = rbNext(rb, rb->start);
    }
    rb->end = rbNext(rb, rb->end);
}


int rbRead(RingBuffer* rb) {
    if (rbIsEmpty(rb)) return -1;
    int elem = rb->elems[rb->start % rb->size];
    rb->start = rbNext(rb, rb->start);
    return elem;
}



int main() {
    RingBuffer ringBuf;
    rbInit(&ringBuf, 5);
    rbPrint(&ringBuf);
    for (int i = 1; i < 13; i++) {
        rbWrite(&ringBuf, i);
        rbPrint(&ringBuf);
    }
    printf("\n\n");
    for (int i = 1; i < 7; i++) {
        rbPrint(&ringBuf);
        printf("get: %d\n", rbRead(&ringBuf));
    }

    return 0; 
}
