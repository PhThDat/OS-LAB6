#ifndef PAGING_DEP_H
#define PAGING_DEP_H

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "array.h"

IntArray initRefs(__int8_t random) {
    srand(time(0));
    IntArray refSeq;
    switch (random)
    {
    case 0:
        printf("Please input number of pages: ");
        scanf("%d", &refSeq.length);

        refSeq.items = (int*)malloc(refSeq.length * sizeof(int));
        for (int i = 0; i < refSeq.length; i++) {
            refSeq.items[i] = rand() % 10;
        }
        break;
    
    default:
        refSeq.length = 11;
        int defaultRef[] = {2, 1, 5, 2, 1 ,2, 6, 0, 0, 0, 7};
        refSeq.items = (int*)malloc(refSeq.length * sizeof(int));
        for (int i = 0; i < refSeq.length; i++) {
            refSeq.items[i] = defaultRef[i];
        }
        break;
    }

    return refSeq;
}

IntArray initFrames() {
    IntArray frames = { NULL, 0 };
    do {
        printf("How many page frames do you want? ");
        scanf("%d", &frames.length);
    } while (frames.length < 1);
    frames.items = (int*)malloc(frames.length * sizeof(int));
    for (int i = 0; i < frames.length; i++) {
        frames.items[i] = -1;
    }

    return frames;
}

__int8_t occurPageFault(IntArray frames, int newPage) {
    return find(frames, newPage) == -1;
}

IntArray paging(
    IntArray refs,
    IntArray frames,
    int method(int pageIndex, IntArray refs, IntArray frames, int prevPos),
    int (*out)[refs.length]
) {
    IntArray faults = {
        (int*)malloc(refs.length * sizeof(int)),
        refs.length
    };
    memset(faults.items, 0, sizeof(int)*faults.length);

    int pos = -1;
    for (int i = 0; i < refs.length; i++) {
        int currentPage = refs.items[i];
        faults.items[i] = occurPageFault(frames, currentPage);

        if (faults.items[i]) {
            pos = method(i, refs, frames, pos);
            frames.items[pos] = currentPage;
        }

        for (int j = 0; j < frames.length; j++) {
            out[j][i] = frames.items[j];
        }
    }

    return faults;
}

#endif