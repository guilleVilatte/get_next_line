*This project has been created as part of the 42 curriculum by guvilatt.*

# get_next_line

## Description

`get_next_line` is a C function that reads and returns one line at a time from a file descriptor.

The objective of this project is to gain a deeper understanding of file descriptors, static variables, dynamic memory management, and buffered input handling in C. Unlike standard file reading functions, `get_next_line` must preserve unread data between function calls and efficiently return each line, including the newline character when present.

The function can be called repeatedly to read a file, standard input, or any valid file descriptor until the end of the input is reached.

---

# Features

- Reads one line at a time from a file descriptor.
- Handles files of any size.
- Preserves unread data between calls using a static buffer.
- Supports configurable buffer sizes through the `BUFFER_SIZE` macro.
- Returns lines including the terminating newline character when present.
- Correctly handles end-of-file conditions.
- Works with standard input, files, and other valid file descriptors.

---

# Instructions

## Compilation

Compile the project using:

```bash
make
```

Available Makefile rules:

```bash
make
make clean
make fclean
make re
```

---

## Usage

Include the header file:

```c
#include "get_next_line.h"
```

Example:

```c
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		return (1);

	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
```

Compile:

```bash
cc main.c get_next_line.c get_next_line_utils.c
```

For a custom buffer size:

```bash
cc -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c
```

---

# How It Works

The function reads data from a file descriptor in chunks of size `BUFFER_SIZE`.

Each read operation appends new data to a persistent static buffer. The buffer is then searched for a newline character (`'\n'`).

When a complete line is found:

1. The line is extracted and returned.
2. The remaining unread data is preserved.
3. The next call continues reading from where the previous one stopped.

If no newline is found, the function continues reading until:
- a newline is encountered,
- the end of the file is reached,
- or an error occurs.

---

# Algorithm Selection and Justification

## Selected Approach

The project uses a buffered reading strategy combined with a static storage area.

Instead of reading the entire file at once, the function repeatedly calls `read()` using a fixed-size buffer and accumulates the content until a complete line becomes available.

This approach was selected because:

- files may be larger than available memory,
- the line length is unknown in advance,
- only the necessary data should be read,
- unread data must remain available for future calls.

---

## Why a Static Variable?

A static variable retains its value between function calls.

Without a static variable, any data remaining after a newline character would be lost when the function returns.

Example:

```text
BUFFER CONTENT:
Hello\nWorld\n
```

After returning:

```text
Hello\n
```

the remaining:

```text
World\n
```

must be preserved for the next call.

The static variable allows the function to maintain this state efficiently.

---

## Time Complexity

Let:

- `n` be the number of characters read.

The overall complexity is approximately:

```text
O(n)
```

since each character is processed a limited number of times while searching for newline characters and constructing the returned line.

---

## Space Complexity

```text
O(n)
```

where `n` corresponds to the size of the stored line and any remaining buffered content.

The memory usage grows according to the amount of unread data that must be preserved.

---

# Technical Decisions

### Dynamic Memory Allocation

Memory is allocated only when necessary to:

- store newly read content,
- build the line returned to the user,
- preserve remaining data.

This prevents arbitrary fixed-size limitations.

### Buffered Reading

Using a configurable `BUFFER_SIZE` reduces the number of system calls and improves efficiency compared to reading one character at a time.

### File Descriptor Validation

The function validates the file descriptor before processing and properly handles read errors.

---

# Project Structure

```text
.
├── get_next_line.c
├── get_next_line_utils.c
├── get_next_line.h
├── Makefile
└── README.md
```

For the bonus version:

```text
.
├── get_next_line_bonus.c
├── get_next_line_bonus.h
├── get_next_line_utils_bonus.c
```

---

# Resources

## Official Documentation

- POSIX read() Manual  
  https://man7.org/linux/man-pages/man2/read.2.html

- File Descriptor Documentation  
  https://man7.org/linux/man-pages/man2/open.2.html

- GNU C Library Documentation  
  https://www.gnu.org/software/libc/manual/

- The Open Group Base Specifications  
  https://pubs.opengroup.org

---

## Learning Resources

- Static Variables in C  
  https://www.geeksforgeeks.org/static-variables-in-c/

- Dynamic Memory Allocation in C  
  https://en.cppreference.com/w/c/memory

- Understanding File Descriptors  
  https://man7.org/linux/man-pages/man7/file_descriptor.7.html

---

# AI Usage Disclosure

Artificial intelligence tools were used during the documentation process to:

- improve technical writing,
- review grammar and readability,
- help structure the README documentation.

The design, implementation, debugging, memory management decisions, and algorithm development were completed manually as part of the learning process.

