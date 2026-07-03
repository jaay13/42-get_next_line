*This project has been created as part of the 42 curriculum by jakoch.*

# get_next_line

## Description

`get_next_line` is a C project that reads one line at a time from a file descriptor.
The function returns the next available line, keeps unread text for the next call,
and stops when there is nothing left to read or when an error occurs.

The goal is to understand static variables, file descriptors, memory ownership,
and efficient line-by-line reading with `read()`.

This repository contains my final passed 42 project, reorganized after evaluation
for readability and portfolio presentation.

## What I learned

- How to break a low-level file problem into smaller, testable steps.
- How to preserve data between calls in a controlled way.
- How to handle edge cases like empty files, missing newlines, and different buffer sizes.
- How to write code that is easier to debug by separating responsibilities.
- How to think more carefully about memory ownership and cleanup.

## Project structure

```text
.
├── include/          Public project headers for mandatory & bonus
├── src/mandatory/    Mandatory get_next_line implementation
├── src/bonus/        Bonus implementation for multiple file descriptors
├── tests/main/       Small local test mains
├── tests/input/      Input files used for manual testing
└── live_coding/ my live-coding part version from the evaluation
```

## Build

```bash
make
```

Builds the mandatory implementation into `libgnl.a`.

```bash
make bonus
```

Builds the bonus implementation into `libgnl.a`.

```bash
make BUFFER_SIZE=42
```

Builds with a custom `BUFFER_SIZE`.

```bash
make clean
make fclean
make re
```

Remove object files, remove all generated files, or rebuild from scratch.

## Manual Compilation

Mandatory:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 -Iinclude \
	src/mandatory/get_next_line.c \
	src/mandatory/get_next_line_utils.c \
	tests/main/main.c \
	-o test
```

Bonus:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 -Iinclude \
	src/bonus/get_next_line_bonus.c \
	src/bonus/get_next_line_utils_bonus.c \
	tests/main/main.c \
	-o test
```

Run with:

```bash
./test tests/input/varying_lengths_nl.txt | cat -e
```

`cat -e` makes line endings visible, which helps verify that `\n` is returned
correctly.

## Algorithm

The implementation keeps a static stash that survives between calls. `read()`
loads up to `BUFFER_SIZE` bytes at a time, so the function reads progressively
instead of loading the whole file at once.

On each call, the function first checks whether the stash already contains a
newline. If it does, it extracts everything from the start of the stash up to and
including `\n`, then keeps the remaining text for the next call.

If there is no newline yet, it keeps reading from the file descriptor, appends the
new bytes to the stash, and repeats until it finds a newline or reaches EOF. When
`read()` returns `0`, the file ended, so the function returns whatever remains in
the stash, or `NULL` if nothing is left.

## Subject Rules

- Return one line per call.
- Include `\n` when the line has one.
- Return the last line even if it does not end with `\n`.
- Work with files and standard input.
- Allowed external functions: `read`, `malloc`, and `free`.
- Do not use `libft`, `lseek`, or global variables.
- Compile with and without `-D BUFFER_SIZE=n`.

## Files

### Mandatory

- `src/mandatory/get_next_line.c`
- `src/mandatory/get_next_line_utils.c`
- `include/get_next_line.h`

### Bonus

- `src/bonus/get_next_line_bonus.c`
- `src/bonus/get_next_line_utils_bonus.c`
- `include/get_next_line_bonus.h`

## Testing

I used:

- Tripouille gnlTester
- Sfabi28 gnl_tester
- gnl-station-tester
- Manual tests in `tests/main/` with fixtures in `tests/input/`

Useful cases:

- Empty file
- One-line file
- File without trailing newline
- Long line
- Multiple newlines back to back
- Different `BUFFER_SIZE` values

## Resources

- The 42 subject
- Official C documentation for `read`, `open`, `malloc`, and `free`
- 42 Get Next Line Guide
- Understanding get_next_line

## AI Use

- I used AI to help draft and structure this README.
- I used the subject and my notes to verify compile rules, execution format, and project constraints.
