#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "heap.h"

typedef struct nodo{
   void* data;
   int priority;
}heapElem;

typedef struct Heap{
  heapElem* heapArray;
  int size;
  int capac;
} Heap;


void* heap_top(Heap* pq){
    if(pq->size==0) return NULL;
    return pq->heapArray[0].data;
}

void heap_push(Heap* pq, void* data, int priority) {
    if (pq->size == pq->capac) {
        pq->capac = pq->capac * 2 + 1;
        pq->heapArray = realloc(pq->heapArray, pq->capac * sizeof(heapElem));
    }

    int curr = pq->size;
    pq->heapArray[curr].data = data;
    pq->heapArray[curr].priority = priority;

    while (curr > 0 && pq->heapArray[curr].priority < pq->heapArray[(curr - 1) / 2].priority) {
        heapElem tmp = pq->heapArray[curr];
        pq->heapArray[curr] = pq->heapArray[(curr - 1) / 2];
        pq->heapArray[(curr - 1) / 2] = tmp;
        curr = (curr - 1) / 2;
    }

    pq->size++;
}


void heap_pop(Heap* pq) {
    if (pq->size == 0) {
        return;
    }

    pq->size--;
    pq->heapArray[0] = pq->heapArray[pq->size];

    int curr = 0;
    while (curr * 2 + 1 < pq->size) {
        int child = curr * 2 + 1;
        if (child + 1 < pq->size && pq->heapArray[child + 1].priority < pq->heapArray[child].priority) {
            child++;
        }
        if (pq->heapArray[curr].priority > pq->heapArray[child].priority) {
            heapElem tmp = pq->heapArray[curr];
            pq->heapArray[curr] = pq->heapArray[child];
            pq->heapArray[child] = tmp;
            curr = child;
        } else {
            break;
        }
    }

    if (pq->size <= pq->capac / 2) {
        pq->capac = pq->capac / 2;
        pq->heapArray = realloc(pq->heapArray, pq->capac * sizeof(heapElem));
    }
}

Heap* createHeap(){
   Heap *pq=(Heap*) malloc(sizeof(Heap));
   pq->heapArray=(heapElem*) malloc(3*sizeof(heapElem));
   pq->size=0;
   pq->capac=3; //capacidad inicial
   return pq;
}
