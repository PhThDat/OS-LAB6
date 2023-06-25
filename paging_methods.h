#include "array.h"

int FIFO(int pageIndex, IntArray refs, IntArray frames, int prevPos) {
    return (prevPos + 1) % frames.length;
}

int OPT(int pageIndex, IntArray refs, IntArray frames, int prevPos) {
    int pos = find(frames, -1);
    if (pos != -1)
        return pos;
    
    int count = 0;
    IntArray willArrivePages = {
        (int*)malloc(frames.length * sizeof(int)),
        frames.length
    };
    memset(willArrivePages.items, 0, willArrivePages.length*sizeof(int));

    for (
        int i = pageIndex + 1; 
        i < refs.length && count < frames.length-1;
        i++
    ) {
        int iterPage = refs.items[i];
        int posInFrames = find(frames, iterPage);
        if(posInFrames != -1) {
            willArrivePages.items[posInFrames] = 1;
            count++;
        }
    }

    pos = find(willArrivePages, 0);
    deallocate(willArrivePages);
    return pos;
}

int LRU(int pageIndex, IntArray refs, IntArray frames, int prevPos) {
    int pos = find(frames, -1);
    if (pos != -1)
        return pos;
    
    int count = 0;
    IntArray mostRecentPages = {
        (int*)malloc(frames.length * sizeof(int)),
        frames.length
    };
    memset(mostRecentPages.items, 0, mostRecentPages.length*sizeof(int));

    for (
        int i = pageIndex - 1;
        i > -1 && count < frames.length-1;
        i--
    ) {
        int iterPage = refs.items[i];
        int posInFrames = find(frames, iterPage);
        if (posInFrames != -1) {
            mostRecentPages.items[posInFrames] = 1;
            count++;
        }
    }

    pos = find(mostRecentPages, 0);
    deallocate(mostRecentPages);
    return pos;
}