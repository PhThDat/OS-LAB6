#include <stdlib.h>
#include <time.h>
#include "utils.h"
#include "paging_dependency.h"
#include "paging_methods.h"

int main(int argc, char* argv[]) {
    srand(time(0));

    int init = choice(
        "--- Page Replacement algorithm ---",
        "Default referenced sequence",
        "Choose a number of pages",
        NULL
    );

    IntArray refs = initRefs(init == 1);
    IntArray frames = initFrames();
    int pagingMethod = choice(
        "Choose an algorithm:",
        "FIFO",
        "OPT",
        "LRU",
        NULL
    );

    int output[frames.length][refs.length];
    memset(
        output, 
        -1, 
        sizeof(int)*refs.length*frames.length
    );
    
    IntArray faults = paging(
        refs,
        frames,
        LRU,
        output
    );

    print(refs);
    printf("\n");
    printMat(frames.length, refs.length, output);
    print(faults);

    deallocate(refs);
    deallocate(frames);
    deallocate(faults);
    return 0;
}