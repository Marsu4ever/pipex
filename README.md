# pipex
This program pipes from one txt file (file1) to another txt file (file2). It performs two commands.

**Arguments**: ./pipex file1 command1 command2 file2 

Specific Example: ./pipex file1.txt ls "wc -l"  file2.txt  
-> this'll list the number of lines in a directory and then count those lines and write that number into the file2.txt.  

**So what's interesting about this project**:  
This program can use system commands (like ls, cat, wc etc) making it useful for using ALREADY made programs. This is done by creating Child processes.
