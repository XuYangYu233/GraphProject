#include "queue.h"

void InitQueue(SqQueue** q)
{
    *q = (SqQueue*)calloc(1, sizeof(SqQueue));
    if (*q == NULL) {
        printf("队列申请失败\n");
    }
    (*q)->front = (*q)->rear = 0;
}

bool QueueEmpty(SqQueue* q)
{
    return (q->front == q->rear);
}
bool enQueue(SqQueue* q, ElemType e)
{
    if ((q->rear + 1) % MAXSIZE == q->front) {
        return false;
    }
    q->rear = (q->rear + 1) % MAXSIZE;
    q->data[q->rear] = e;
    return true;
}

bool deQueue(SqQueue* q, ElemType* e)
{
    if (q->front == q->rear) {
        return false;
    }
    q->front = (q->front + 1) % MAXSIZE;
    *e = q->data[q->front];
    return true;
}

bool enPQueue(SqQueue* q, ElemType e)  // 优先队列进队
{ 
    if (q->rear == MAXSIZE - 1) {
        printf("优先队列顶不住了\n");
        return false;
    }
    long long i;
    i = ++q->rear;

    for (; e.wei < q->data[i / 2].wei; i /= 2) {
        q->data[i] = q->data[i / 2];
    }
    q->data[i] = e;

    return true;
}

bool dePQueue(SqQueue* q, ElemType* e) // 优先队列出队
{
    long long parent;
    long long child;
    ElemType min, last;

    if (q->rear == 0) {
        return false;
    }

    min = q->data[1];
    last = q->data[q->rear--];

    for (parent = 1; parent * 2 <= q->rear; parent = child) {
        child = parent * 2;
        if (child != q->rear && q->data[child + 1].wei < q->data[child].wei) {
            child++;
        }
        if (last.wei > q->data[child].wei) {
            q->data[parent] = q->data[child];
        } else {
            break;
        }
    }
    q->data[parent] = last;
    *e = min;
    return true;
}