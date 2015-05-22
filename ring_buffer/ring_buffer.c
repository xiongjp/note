/* 
 * 如果缓冲区长度是2的幂，则本方法可以省略镜像指示位。
 * 如果读写指针的值相等，则缓冲区为空；
 * 如果读写指针相差n，则缓冲区为满，
 * 这可以用条件表达式（写指针 == (读指针 异或 缓冲区长度)）来判断
 */

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
    /* This inverts the most significant bit of start before comparison */
    return rb->start == (rb->end ^ rb->size);
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
    return (p + 1) & (2 * rb->size - 1);
}


void rbWrite(RingBuffer* rb, int elem) {
    rb->elems[rb->end & (rb->size - 1)] = elem;
    if (rbIsFull(rb)) {
        /* full, start pos has been overwrited, move start pos forward */
        rb->start = rbNext(rb, rb->start);
    }
    rb->end = rbNext(rb, rb->end);
}


int rbRead(RingBuffer* rb) {
    if (rbIsEmpty(rb)) return -1;
    int elem = rb->elems[rb->start & (rb->size - 1)];
    rb->start = rbNext(rb, rb->start);
    return elem;
}



int main() {
    RingBuffer ringBuf;
    rbInit(&ringBuf, 4);
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
