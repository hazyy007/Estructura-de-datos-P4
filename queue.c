#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "types.h"

struct _Queue {
    void *data[MAX_QUEUE];
    int front;
    int rear;
};

Queue *queue_new() {
    int i;
    Queue *q = (Queue *)malloc(sizeof(Queue));
    if (!q) return NULL;

    q->front = 0;
    q->rear = 0;

    for (i = 0; i < MAX_QUEUE; i++) {
        q->data[i] = NULL;
    }

    return q;
}

void queue_free(Queue *q) {
    if (q) free(q);
}

Bool queue_isEmpty(const Queue *q) {
    if (!q) return TRUE;
    /*La cola esta vacia si front y rear apuntan al mismo sitio*/
    return (q->front == q->rear) ? TRUE : FALSE;
}

Bool queue_isFull(const Queue *q) {
    if (!q) return TRUE;
    return (((q->rear + 1) % MAX_QUEUE) == q->front) ? TRUE : FALSE;
}

Status queue_push(Queue *q, void *ele) {
    if (!q || !ele || queue_isFull(q)) return ERROR;

    q->data[q->rear] = ele;
    q->rear = (q->rear + 1) % MAX_QUEUE;/*Avanza circularmente*/
    return OK;
}

void *queue_pop(Queue *q) {
    void *ele;
    if (!q || queue_isEmpty(q)) return NULL;

    ele = q->data[q->front];
    q->data[q->front] = NULL;
    q->front = (q->front + 1) % MAX_QUEUE; /*Avanza circularmente*/
    return ele;
}

void *queue_getFront(const Queue *q) {
    if (!q || queue_isEmpty(q)) return NULL;
    return q->data[q->front];
}

void *queue_getBack(const Queue *q) {
    if (!q || queue_isEmpty(q)) return NULL;
    return q->data[(q->rear - 1 + MAX_QUEUE) % MAX_QUEUE]; /*rear - 1 con ajuste circular*/
}

size_t queue_size(const Queue *q) {
    if (!q) return 0;
    
    if (q->rear >= q->front) {
        return (size_t)(q->rear - q->front);
    } else {
        /* Caso en el que ha dado la vuelta circular */
        return (size_t)(MAX_QUEUE - q->front + q->rear);
    }
}

int queue_print(FILE *fp, const Queue *q, p_queue_ele_print f) {
    int count = 0, i;
    if (!fp || !q || !f) return -1;

    for (i = q->front; i < q->rear; i++) {
        int res = f(fp, q->data[i]);
        if (res < 0) return -1;
        count += res;
        fprintf(fp, "\n");
    }
    return count;
}




