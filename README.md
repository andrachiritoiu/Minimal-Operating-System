Storage Management Component for a Minimal Operating System
Project Description
This project is part of the development of a minimal operating system that manages and coordinates the activities of a computing system. The operating system acts as an intermediary, granting application programs access to machine resources.

Our task is to implement a storage management component for a storage device (hard disk or SSD). Since the project is in its early stages, certain assumptions have been made to simplify development.

Requirements
The system operates in two possible modes:

Unidimensional memory (linear memory allocation)
Bidimensional memory (grid-based memory allocation)
1. Unidimensional Memory Implementation
In this case, the storage device functions as follows:

The storage capacity is fixed at 8MB.
The storage is divided into 8kB blocks.
Each block can hold data from only one file.
A file requires at least two blocks for storage.
Files are stored contiguously in memory.
If a file cannot be stored contiguously, the write operation fails.
The system does not use directories or file structures, only a simple storage mechanism.
Each file is identified by a unique descriptor (ID), a natural number between 1 and 255.
The system can store a maximum of 255 files.
Required Operations for Unidimensional Memory
Retrieve file location: Given a file descriptor (ID), return the interval of blocks (start, end) where the file is stored.
Store a file: Given a file descriptor and its size (in kB), return the interval of blocks where it can be stored. The first available contiguous interval (from left to right) is used. If storage is not possible, return (0, 0).
Delete a file: Given a file descriptor, remove the file from storage by marking its blocks as free (assigned descriptor value 0).
Defragmentation: Rearrange/recalculate the blocks so that files are stored compactly, starting from block 0 and filling all consecutive blocks without gaps.
2. Bidimensional Memory Implementation
To expand the storage capacity, the memory model is extended to two dimensions, forming an 8MB × 8MB grid. A contiguous storage section is defined along rows.

Required Operations for Bidimensional Memory
Retrieve file location: Given a file descriptor, return the interval of blocks ((startX, startY), (endX, endY)) where the file is stored.
Store a file: Given a file descriptor and its size (in kB), return the first available contiguous interval in the matrix where the file can be stored. If storage is not possible, return ((0,0), (0,0)).
Delete a file: Given a file descriptor, remove the file from storage by marking its blocks as free (0).
Defragmentation: Rearrange the blocks in the matrix so that files are stored compactly, moving gaps toward the bottom-right of the grid.
This project simulates a basic storage management system and provides an efficient way to store, retrieve, and manage files in both unidimensional and bidimensional memory models.
