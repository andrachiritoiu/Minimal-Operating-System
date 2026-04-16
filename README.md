# Storage Management System 

A minimal storage management component written in **x86 Assembly**, simulating how an operating system manages a storage device (HDD/SSD). This project is part of the development of a minimal operating system that manages and coordinates the activities of a computing system, acting as an intermediary between application programs and machine resources.

---

## Overview

This project implements a simplified file storage manager that operates in two modes:

| Mode | Description |
|------|-------------|
| **1D Memory** | Linear array of 8kB blocks across 8MB of storage |
| **2D Memory** | Grid-based matrix of blocks (8MB × 8MB) |

Each file is identified by a unique **descriptor (ID)** between `1` and `255`. The system can store a maximum of **255 files**. Files are stored contiguously in blocks — if there's no contiguous space available, the write fails.

---

## 1D Memory Implementation

The storage capacity is **fixed at 8MB**, divided into **8kB blocks**.

- Each block can hold data from only **one file**
- A file requires **at least 2 blocks** for storage
- Files are always stored **contiguously** — if no contiguous interval exists, the operation fails
- The system has no directory structure, only a flat storage mechanism

### Required Operations

| Operation | Description |
|-----------|-------------|
| **ADD** | Given a descriptor and size (kB), store the file in the first available contiguous interval (left to right). Returns the block interval used, or `(0, 0)` if not possible. |
| **GET** | Given a descriptor, return the interval `(start, end)` where the file is stored, or `(0, 0)` if it doesn't exist. |
| **DELETE** | Given a descriptor, free all blocks used by the file (set to `0`). |
| **DEFRAGMENTATION** | Rearrange all files compactly starting from block `0`, preserving order and eliminating all gaps. |

---

## 2D Memory Implementation

An extension to two dimensions: an **8MB × 8MB grid of blocks**. A contiguous storage section is defined **along rows**.

### Required Operations

| Operation | Description |
|-----------|-------------|
| **ADD** | Given a descriptor and size, return the first available contiguous interval `((x1,y1),(x2,y2))` in the matrix, or `((0,0),(0,0))` if not possible. |
| **GET** | Return the interval `((startX, startY), (endX, endY))` where the file is stored. |
| **DELETE** | Free all blocks used by the file (set to `0`). |
| **DEFRAGMENTATION** | Compact all files in the matrix, moving gaps toward the **bottom-right** corner, preserving file order. |
| **CONCRETE** | Read actual files from an absolute directory path. For each file, compute its descriptor (`fd % 255 + 1`) and size in kB, then add it to memory using ADD. |

---

## Memory Model

> For demonstration purposes, 8kB blocks are reduced to 8 bytes, and 8MB storage is proportionally scaled.

**1D Example:**
```
Initial:
0, 0, 0, 0, 0, 0, ...

After ADD descriptor=5 (20kB → 3 blocks):
5, 5, 5, 0, 0, 0, ...

After ADD descriptor=143 (14kB → 2 blocks):
5, 5, 5, 143, 143, 0, ...

After DELETE descriptor=5:
0, 0, 0, 143, 143, 0, ...

After DEFRAGMENTATION:
143, 143, 0, 0, 0, 0, ...
```

**2D Example:**
```
After several ADDs and DELETEs, before DEFRAG:
5, 5, 5, 5, 5, 5, 5, 0
2, 2, 2, 2, 2, 2, 2, 0
0, 0, 3, 3, 3, 3, 7, 7
0, 0, 0, 6, 6, 6, 6, 6

After DEFRAGMENTATION (gaps pushed to bottom-right):
5, 5, 5, 5, 5, 5, 5, 0
2, 2, 2, 2, 2, 2, 2, 0
3, 3, 3, 3, 7, 7, 0, 0
6, 6, 6, 6, 6, 0, 0, 0
```

---

## Project Structure

```
.
├── unidimesional.s     # Cerinta 0x00 — 1D memory (Assembly)
├── bidimensional.s     # Cerinta 0x01 — 2D memory (Assembly)
├── vector.cpp          # Reference implementation for 1D (C++)
├── matrix.cpp          # Reference implementation for 2D (C++)
├── inputvector.txt     # Sample input for 1D
├── inputmatrix.txt     # Sample input for 2D
└── README.md
```

---

## Input Format

First line is the number of operations `O`, followed by operation codes:

| Code | Operation |
|------|-----------|
| `1` | ADD |
| `2` | GET |
| `3` | DELETE |
| `4` | DEFRAGMENTATION |
| `5` | CONCRETE *(2D only)* |

For **ADD**, the next line gives the number of files `N`, followed by `2N` lines alternating between descriptor and size in kB.

---

## Output Format

| Operation | 1D Format | 2D Format |
|-----------|-----------|-----------|
| ADD / GET | `fd: (start, end)` | `fd: ((x1, y1), (x2, y2))` |
| Not found / fail | `fd: (0, 0)` | `fd: ((0, 0), (0, 0))` |

---

## Notes

- `1 MB = 1024 kB`, `1 kB = 1024 B`
- A file requires **at least 2 blocks** for storage
- Blocks default to `0` (free); any non-zero value represents a file descriptor
- The system has **no directory structure** — only flat file storage by descriptor
- All strings in `.data` must end with `\n`
