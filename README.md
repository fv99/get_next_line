# get_next_line

>Write a function that returns a line read from a file descriptor

- Repeated calls to the get_next_line() function should let you read the text file pointed to by the file descriptor, ***one line at a time***.
- The function should return the line that was read.
- If there is nothing else to read or if an error occurred, it will return NULL.
- Developed get_next_line() using only one static variable.
- Manages multiple file descriptors at the same time.

**Forbidden:**
- Global variables are forbidden.
- lseek() is forbidden.
- You are not allowed to use your libft in this project.