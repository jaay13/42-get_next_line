*This project has been created as part of the 42 curriculum by jakoch.*

# get_next_line

## What I learned
- How to break a low-level file problem into smaller, testable steps.
- How to preserve data between calls in a controlled way.
- How to handle edge cases like empty files, missing newlines, and different buffer sizes.
- How to write code that is easier to debug by separating responsibilities.
- How to think more carefully about memory ownership and cleanup.

# Description
`get_next_line` is a C project where you write a function that reads one line at a time from a file descriptor.  
The function returns the next available line, keeps unread text for the next call, and stops when there is nothing left to read or an error occurs. 

The goal is to understand static variables, file descriptors and efficient line-by-line reading with `read()`. 

# Instructions

### Compilation
Compile my small main with:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 -o test get_next_line.c get_next_line_utils.c main.c
```

Your project must also compile without `-D BUFFER_SIZE`, using the default value defined in your header. 

### Execution
Run it like this:

```bash
./test FILE_NAME | cat -e
```

Example:

```bash
./test files/varying_lengths_nl.txt | cat -e
```

`cat -e` makes line endings visible, which helps verify that `\n` is returned correctly.  
The `main.c` is only for local testing: it opens a file, calls `get_next_line(fd)` in a loop, prints each line, frees it, and closes the file descriptor. 

## Algorithm
My implementation keeps a **static stash** that survives between calls. `read()` loads up to `BUFFER_SIZE` bytes at a time, so the function reads the file progressively, unless `BUFFER_SIZE` is large enough to cover the remaining content in one call.

On each call, I first check whether the stash already contains a newline. If it does, I extract everything from the start of the stash up to and including `\n`, then keep the remaining part in the stash for the next call. 

If there is no newline yet, I keep reading from the file descriptor, append the new bytes to the stash, and repeat until I find a newline or reach EOF. When `read()` returns `0`, the file ended, so I return whatever remains in the stash as the last line, or `NULL` if nothing is left. 

This approach matches the subject because it reads as little as possible, works with repeated calls, preserves leftover text, and avoids global variables. 

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
- `get_next_line.c`
- `get_next_line_utils.c`
- `get_next_line.h`

### Bonus
- `get_next_line_bonus.c`
- `get_next_line_utils_bonus.c`
- `get_next_line_bonus.h`

## Testing
I used:
- [Tripouille gnlTester](https://github.com/Tripouille/gnlTester)
- [Sfabi28 gnl_tester](https://github.com/Sfabi28/gnl_tester)
- [gnl-station-tester](https://github.com/kodpe/gnl-station-tester)
- My own tests like like `main.c`

### Useful tests
- Empty file.
- One-line file.
- File without trailing newline.
- long line
- multiple new lines back to back
- Different `BUFFER_SIZE` values.

# Resources
- The 42 Subject
- Official C documentation of functions, such as `read` or `open`
- [42 Get Next Line Guide](https://medium.com/@lannur-s/gnl-c3cff1ee552b)
- [understanding get_next_line](https://www.youtube.com/watch?v=-Mt2FdJjVno)

## AI Use
- I used AI to help draft and structure this README.
- I used the subject and my notes to verify the compile rules, execution format, and project constraints. 