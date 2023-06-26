#include <stdlib.h>
#include <time.h>
#include "utils.h"
#include "paging_dependency.h"
#include "paging_methods.h"

int main(int argc, char* argv[]) {
    system("clear");
    srand(time(0));

    // Default reference sequence or choose a lenght
    int init = choice(
        "--- Page Replacement algorithm ---",
        "Default referenced sequence",
        "Choose a number of pages",
        NULL
    );

    // Create reference sequence
    IntArray refs = initRefs(init == 1);
    // Create frames slots
    IntArray frames = initFrames();
    // Choose paging method
    int pagingMethod = choice(
        "Choose an algorithm:",
        "FIFO",
        "OPT",
        "LRU",
        NULL
    );
    // Pointer to method for later execution
    void* method = NULL;
    switch (pagingMethod) {
    case 1:
        method = FIFO; break;
    case 2:
        method = OPT; break;
    case 3:
        method = LRU; break;
    }

    // Frames output memory
    int output[frames.length][refs.length];
    memset(
        output, 
        -1, 
        sizeof(int)*refs.length*frames.length
    );
    
    // Core function - Paging processor
    IntArray faults = paging(
        refs,
        frames,
        method,
        output
    );

    // Print results
    print(refs);
    printf("\n");
    printMat(frames.length, refs.length, output);
    int countFaults = 0;
    for (int i = 0; i < faults.length; i++) {
        char val = faults.items[i] ? '*' : ' ';
        printf("%s%c%s\t", "\x1b[1;33m", val, "\x1b[0m");
        countFaults += faults.items[i] != 0;
    }
    printf("\nNumber of Page Faults: %d", countFaults);

    // Free memory
    deallocate(refs);
    deallocate(frames);
    deallocate(faults);
    return 0;
}