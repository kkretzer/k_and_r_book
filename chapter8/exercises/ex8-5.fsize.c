not doing this exercise

relies on section 8.6 code, which will not work on modern system it seems
k&r assume we can read a directory listing file
but the 'read' function does not do that
the system readdir function is the only way to get at that data
and readdir is what the 8.6 code is implementing
