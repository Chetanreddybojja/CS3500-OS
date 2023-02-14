# CS3500 - Operating Systems
The following important improvements were made to optimize the xv6-RISCV Operating System (https://github.com/mit-pdos/xv6-riscv).
- Copy on Write (COW): The parent and child processes’ virtual addresses are made to point to a single copy in
physical memory and a new copy is generated only when there’s a write to the pages at the shared memory. This is done as most of the pages remain unaltered between them.
- Just in Time allocation: System call sys_sbrk() is modified to prevent allocating new pages. An exception handler is added to allocate pages only when there’s a memory access.
