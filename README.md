# pipex
This program pipes from one txt file (file1) to another txt file (file2). It performs two commands.

**Arguments**: ./pipex file1 command1 command2 file2 

Specific Example: ./pipex file1.txt cat "wc -l"  file2.txt  
-> this'll display (cat) the contents of a file (file1.txt) and then count those lines (wc -l) and write that number into a 2nd file (file2.txt).  

**So what's the point of this project**:  
This program can use system commands (like ls, cat, wc etc) making it useful for using SYSTEM programs. This is achieved by creating Child processes.
