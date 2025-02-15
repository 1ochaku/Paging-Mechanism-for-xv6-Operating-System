
# Paging Mechanism for xv6 Operating System

This project addresses the problem of handling page faults in the xv6 operating system by implementing a paging mechanism with a Least Recently Used (LRU) page replacement strategy.

## Overview

Whenever a page fault occurs, the process is put to sleep and the least recently used page from its page table is removed. As a result, some frames in main memory become free, allowing other processes to utilize the available frames to continue execution.

This mechanism is managed by two key functions:
- **swapOutFunction**: Responsible for removing the least recently used page from a process's page table.
- **swapInFunction**: Brings a page back into memory when required by a process.

Both of these functions are implemented in the `proc.c` file.

## Getting Started

### Prerequisites
- QEMU emulator installed on your system.

### Installation and Running

1. Clone this repository:
   ```bash
   git clone https://github.com/1ochaku/Paging-Mechanism-for-xv6-Operating-System.git
   ```
2. Navigate into the project directory:
   ```bash
   cd Paging-Mechanism-for-xv6-Operating-System
   ```
3. Build the project and run the xv6 system on QEMU:
   ```bash
   make file
   make
   make QEMU
   ```

## Testing the Paging Mechanism

To verify the correctness of the paging mechanism, we implemented a user-level test program, `sanity_test.c`.

### Running the Test

After QEMU has launched the xv6 system, you can run the following command in the shell:

```bash
sanity_test
```

### Test Details

The `sanity_test` program spawns 20 processes. Each process runs a loop of 10 iterations, where in each iteration, 4096 bytes of memory are allocated. The allocated memory is filled with specific values, and these values are later checked for correctness. Any discrepancy in the values indicates a failure in the paging mechanism.
