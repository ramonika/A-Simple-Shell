Shell Utility
Using system calls to handle all file operations, write a program in C/C++/Java that copies a file from one location to another, and deletes the original version. The program should take two file names as its arguments, the first one being the file to copy, and the second being the new location. The new location should not be over-written if it already exists. The program should check for bad inputs and should work for files of arbitrary size. In addition, the program should gracefully handle error conditions while copying the file. Make sure to use system calls (e.g., open) and not the C library for manipulating files (e.g., fopen).
Write a program in C/C++/Java to create files of 1, 10 and 100MB in size, and them time how long it takes to copy these files. Are the results what you imagine them to be?
The Simple shell: the behaviour of the simple shell is simply an infinite loop:
Displaying a prompt to indicate that it is ready to accept the next command from the user
Reading a line of keyboard input as a command, and
Spawning and having a new process execute as per the user's command
Write a simple shell in C/C++. The shell should read a line from the standard input, parse the line to get the command and its arguments, fork and exec the command. The shell should wait for commands to finish, and should exit when it receives the command exit. When executing a command, the shell should first look for the command in the current directory, and if not found, search the directories defined in a special variable, path. Some general-purpose commands such as ls or installed software have their executables stores in folder /usr/bin. The shell should not be able to run these commands, and report an error till /usr/bin has been added to the path.
Using the system() command is not allowed, as it simply invokes the system's /bin/sh shell to do the work.
You may assume that the command line arguments are separated by whitespaces. Do not do anything special for backslashes, quotes, ampersands or other characters that are ``special'' in other shells. Note that this means that commands in your shell will not be able to operate on filenames with spaces in them!
You may set a reasonable maximum on the number of command line arguments, but the shell should handle input lines of any length.
The executable file for your shell should be named sh. When executing it, make sure you are executing your own sh and not /bin/sh.
A few shell commands are not separate programs, but are handled directly by the shell program. You have already implemented exit, which is an example of such a command. Now, implement cd, the change directory commands. You will need to invoke the chdir system call to do this. Note that if the call to chdir fails, you probably don't want to exit the shell, but instead, should handle the error appropriately.
Some convenient built-ins present in many shells are pushd, popd and dirs. Implement these in your shell. Do not assume any limit on the number of times these may be given by a user, in a session.
pushd works like cd, but pushes the directory you switched from onto a stack
popd pops the top directory off the stack, and cds to it. In other words, a pushd followed by a popd should bring you back to the directory you were in, before the pushd.
dirs prints the contents of the stack.
The path variable holds a list of possible paths in which to search for executables. The list of paths is empty by default, but may grow to any arbitrary size. You should implement a built-in command to control this variable: path [+|- /some/dir]
path (without arguments) displays all entries in the list separated by colons e.g., /bin:/usr/bin.
path + /some/dir appends the given pathname to the path list.
path - /some/dir removes the given pathname from the path list.

