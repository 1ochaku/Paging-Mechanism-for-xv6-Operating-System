#include "types.h"
#include "stat.h"
#include "user.h"

#define BLOCK_SIZE 4096  // 4KB block size
#define NUM_PROCESSES 20 // Number of child processes
#define NUM_ITERATIONS 10 // Number of iterations per child
#define NUM_ELEMENTS (BLOCK_SIZE / sizeof(int)) // Number of int elements (1024 for 4KB)

// A simple function to fill memory with values (returns index % 256)
unsigned char simple_function(int index) {
    return (unsigned char)(index % 256);
}

int
main(void) {
    int pids[NUM_PROCESSES];

    // Fork 20 child processes
    for (int i = 0; i < NUM_PROCESSES; i++) {
        pids[i] = fork();

        if (pids[i] < 0) {
            printf(1, "Fork failed\n");
            exit();
        }

        if (pids[i] == 0) {  // Child process
            printf(1, "Child %d\n", i + 1);
            printf(1, "Iteration Matched Different\n");
            printf(1, "--------- ------- ---------\n\n");

            for (int j = 0; j < NUM_ITERATIONS; j++) {
                // Allocate 4KB of memory using sbrk
                unsigned char *mem_block = (unsigned char *)sbrk(BLOCK_SIZE);
                if (mem_block == (unsigned char *)-1) {
                    printf(1, "Memory allocation failed in child process %d\n", getpid());
                    exit();
                }

                // Fill the memory with values from simple_function
                for (int k = 0; k < BLOCK_SIZE; k++) {
                    mem_block[k] = simple_function(k);
                }

                // Validate the memory content
                int matched = 0;
                for (int k = 0; k < BLOCK_SIZE; k++) {
                    if (mem_block[k] == simple_function(k)) {
                        matched++;
                    }
                }

                // Print the result for this iteration
                int matched_bytes = matched;
                int different_bytes = BLOCK_SIZE - matched_bytes; // it checks if there is memory error

                if (j < 9) {
                    printf(1, "    %d      %dB      %dB\n", j + 1, matched_bytes, different_bytes);
                } else {
                    printf(1, "   %d      %dB      %dB\n", j + 1, matched_bytes, different_bytes);
                }
            }

            printf(1, "\n");
            exit();
        }
    }

    // Parent process waits for all child processes to finish
    while (wait() != -1)
        ;

    exit();
}

