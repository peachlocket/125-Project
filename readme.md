# VaronaShell
A simulation of a Windows Command Line Written in C.

Final project for CMSC 125.
<br><br>

## Files
### VaronaShell.c
Source code of a windows command prompt, written in C. Contains  implementations of selected Windows command line commands.

### VaronaShell.exe
The executable file, emulating selected processes and behaviors of a Windows command prompt.

<br>

## How to Compile

Type in the following text in the Windows Command Prompt.
```
gcc VaronaShell.c -o VaronaShell
```
<br>

## Available Commands

### CD
Changes the current directory

###### Syntax
```
CD [..]
```
```
CD [drive:][path]
```
###### Example
```
cd C:\Users\charlenemcv\Documents\125-project
```

### CHDIR
Changes the current directory

###### Syntax
```
CHDIR [..]
```
```
CHDIR [drive:][path]
```
###### Example
```
chdir C:\Users\charlenemcv\Documents\125-project
```

### CLS
Clears the screen

###### Syntax
```
cls
```

### CMD
Starts a new instance of the command interpreter

###### Syntax
```
cmd
```

### COPY
Copies one or more files to another location

###### Syntax
```
copy [source][destination]
```

###### Example
```
copy a.txt b.txt
```
```
copy a.txt destination
```

### DATE
Displays or sets the date. Unfortunately, for this simulation, the user cannot set the date due to administrator rights.

###### Syntax
```
date [MM/DD/YYY]
```
###### Example
```
date 12/04/2017
```

### DEL
Deletes one or more files

###### Syntax
```
del [file][...]
```
###### Example
```
del sample.txt
```

### DIR
Displays a list of files and subdirectories in a directory

###### Syntax
```
dir
```
###### Example
```
dir
```

### MKDIR
Creates a directory

###### Syntax
```
mkdir [dirname]
```
###### Example
```
mkdir new_folder
```

### MOVE
Moves one or more files from one directory to another directory

```
move [source][destination]
```

###### Example
```
move a.txt b.txt
```

### RENAME
Renames a file

###### Syntax
```
rename [oldname][newname]
```
###### Example
```
rename text1.txt newtext1.txt
```

### RMDIR
Removes a directory

###### Syntax
```
rmdir [dirname]
```
###### Example
```
rmdir folder
```

### TIME
Displays or sets the system time. The user cannot set the time due to administrator rights.

###### Syntax
```
time [HH:MM:SS.ms]
```
###### Example
```
time 11:11:11.0
```

### TYPE
Displays the contents of a text file

###### Syntax
```
type [filename]
```
###### Example
```
type a.txt
```

<br><br>

## Additional Commands

### EXIT
Closes the shell

###### Syntax
```
exit
```
