*This project has been created as part of the 42 curriculum by joaorosa.*

# Get Next Line

## Description

Get Next Line (GNL) is a function that reads a text file (or any file
descriptor) one line at a time. Each call to `get_next_line()` returns the
next line from the given file descriptor, including the terminating `\n`
character — except for the last line when the file does not end with a newline.

The goal of the project is to learn how to work with file descriptors, the
`read()` system call, dynamic memory allocation, and — most importantly — the
concept of **static variables**, which let the function remember its reading
state between successive calls.

```c
char *get_next_line(int fd);
```

- **Returns:** the line that was read, or `NULL` when there is nothing left to
  read or when an error occurs.
- **Works with:** regular files and standard input.

## Instructions

### Compilation

The buffer size used by `read()` is set at compile time through the
`BUFFER_SIZE` macro. The project compiles **with or without** the `-D` flag
(a default of `42` is provided in the header).

```sh
# With a custom buffer size (42 used as an example)
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
   get_next_line.c get_next_line_utils.c -o gnl

# Without the flag (uses the default BUFFER_SIZE in the header)
cc -Wall -Wextra -Werror \
   get_next_line.c get_next_line_utils.c -o gnl
```

### Usage example

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int   fd;
    char *line;

    fd = open("foo.txt", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

Every line returned by `get_next_line()` is heap-allocated and **must be freed
by the caller**.

## Files

| File                      | Purpose                                              |
| ------------------------- | ---------------------------------------------------- |
| `get_next_line.c`         | Core logic: reading, line extraction, stash handling |
| `get_next_line_utils.c`   | Helper functions (`ft_strlen`, `ft_strchr`, etc.)    |
| `get_next_line.h`         | Header with the prototype and `BUFFER_SIZE` default  |

## Algorithm

The function keeps the data read so far in a **static `char *stash`**. Because
the variable is `static`, its value survives between calls, so the reading
state of the file descriptor is preserved without using a global variable.

Each call follows three steps:

1. **Read into the stash** (`read_to_stash`)
   The function reads `BUFFER_SIZE` bytes at a time and appends them to the
   stash (via `ft_strjoin_free`) until either a `\n` is found in the stash or
   `read()` returns `0` (end of file). This guarantees we read *as little as
   possible*: as soon as a newline is available we stop reading and return.

2. **Extract the line** (`extract_line`)
   The stash is scanned up to and including the first `\n` (or the end of the
   string if there is none). That slice is copied into a freshly allocated
   buffer, which becomes the returned line.

3. **Update the stash** (`update_stash`)
   Everything *after* the first `\n` is copied into a new, smaller stash and
   the old one is freed. This leftover becomes the starting point for the next
   call. When nothing remains, the stash is freed and set to `NULL`, so the
   next call starts fresh.

### Why this approach

- **Static variable instead of a global:** globals are forbidden by the
  subject; a function-local `static` provides exactly the persistence we need,
  scoped to this function only.
- **Incremental reading:** we never read the whole file up front. We read just
  enough to produce the current line, which keeps memory usage proportional to
  the line length plus one buffer — not the file size.
- **Robust to any `BUFFER_SIZE`:** the loop logic is independent of the buffer
  value, so it works correctly whether `BUFFER_SIZE` is `1`, `9999`, or
  `10000000`. A larger buffer means fewer `read()` calls; a smaller one means
  more — but the result is identical.
- **Newline-terminated `read()` buffer:** each read appends a `'\0'` after the
  bytes read so the buffer can be treated as a C string for joining and
  searching.

## Resources

- [Input/Output system calls in C — GeeksforGeeks](https://www.geeksforgeeks.org/c/input-output-system-calls-c-create-open-close-read-write/)
- `man 2 read`, `man 3 malloc`, `man 3 free` — system call and allocation references
- The concept of **static variables** in C (storage duration and scope)

### Use of AI

AI was used as a *learning and review* aid, not to generate the solution:
- To help structure and format this `README.md`.
- To review and explain edge cases (empty files, files without a trailing
  newline, `read()` errors, varying `BUFFER_SIZE` values).

The implementation, the choice of algorithm, and the code logic were written
and reasoned through by the author.
