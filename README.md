<img src="https://i.imgur.com/I6m9zIU.png" width=100%>
<h2 align=center> 🐚 SIMPLE SHELL PROJECT🐚 </h2>
This is a colaboration project for the end of the first tremeter at Holberton School between [Diego](https://github.com/DiegoSusviela) and [Toshi](https://github.com/toshi-uy).
It was a 15 day project where we had to replicate a simple command line prompt inspired as much as we could on the basic "sh" shell or the "bash" shell. Our basic shell can run programs and built-in commands.

### Instalation
If you wish to install this you will need to have Linux OS or a virtual machine, and can run Gcc >= 4.8.4.
#### Steps to compile and execute.

-   `git clone https://github.com/DiegoSusviela/simple_shell.git`
-   `cd simple_shell`
-   `gcc -Wall -Werror -Wextra -pedantic *.c -o hsh`
-   `./hsh`
### EXAMPLES

#### Modes

##### Non-interactive
```
$ echo "/bin/ls" | ./hsh
example.c   example.c  example.c        file     man _1_simple_shell  example.c  README.md
AUTHORS  example.c      example.c  example.c  example.c      readline.c         shell.h
$
```
----------
##### Interactive

```
$ ./hsh
```
Then the prompt appears, so you can type in the command line, and press return
```
hsh$ ls
example.c   example.c  example.c        file     man_1_simple_shell  example.c  README.md
AUTHORS  example.c      example.c  example.c  example.c      readline.c         shell.h
hsh$ 
hsh$ pwd
/root/simple_shell
hsh$ 
```
## File Contents

This repository contains the following files:
File | Description 
------------ | ------------- 
 **AUTHORS** | Describes the colaborating authors 
 **man_1_simple_shell** | manual file
  **_strlen** | counts the length of a string
  **aux_func_1** | aditional functions
  **builtins.c** | handles the builtin functions of shell
  **env_hanlder.c** | handles the enviroment
  **free_1.c** | memory freeing functions
  **free_2.c** | more memory freeing functions
  **header.h** | header file
  **input_arranger.c** | handles the input from the keyboard
  **paths_1.c** | handles the paths
  **string_handlers.c** | handles all strings modifiers
  **shell.c** | main function for our shell

### TASK REQUIREMENTS
-   Allowed editors:  _vi_,  _vim_,  _emacs_
-   All your files will be compiled on Ubuntu 14.04 LTS.
-   Your programs and functions will be compiled with  _gcc 4.8.4_  using the flags  _-Wall -Werror -Wextra_  and  _-pedantic_
-   All your files should end with a new line
-   A  _README.md_  file, at the root of the folder of the project is mandatory
-   Your code should use the  _Betty_  style. It will be checked using  _betty-style.pl_  and  _betty-doc.pl_
-   No more than 5 functions per file.
-   Your shell should not have any memory leaks.
-   All your header files should be include guarded.
-   Use system calls only when you need to.
## Builtins Commands

**Command** | **Description**
------------ | ------------- 
cd | Changes the current directory of the process 
env | Run a program in a modified enviroment.
exit | Cause normal process termination (can handle arguments)
## Extras
### Builtin command  `cd`:
-   Changes the current directory of the process.
-   Command syntax:  `cd [DIRECTORY]`
-   If no argument is given to  `cd`  the command must be interpreted like  `cd $HOME`
-   It can handle the command  `cd -`
-   The environment variable  `PWD`  is updated when you change directory
### -   Handle the commands separator  `;`
The command separator allows you to run various commands in one line. For example:
```
alex@~$ ls /var ; ls /var
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
alex@~$ ls /hbtn ; ls /var
ls: cannot access /hbtn: No such file or directory
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
alex@~$ ls /var ; ls /hbtn
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
ls: cannot access /hbtn: No such file or directory
```
*Known Bug: when two commas are entered it crashes.
### -   Handle comments (`#`)
If commented the following arguments are not run. For example:
```
julien@ubuntu:~/shell$ sh
$ echo $$ # ls -la
5114
$ exit
julien@ubuntu:~/shell$ 
```
### -   Own implementation of `strtok`
We made our own implementation of the standard libary funciton `strtok`.
### -   Own implementation of `getline`
We made our own implementation of the standard libary funciton `getline`.

## Authors
- [**Diego**](https://github.com/DiegoSusviela) <2792@holbertonschool.com>
- [**Toshi**](https://github.com/toshi-uy) <2785@holbertonschool.com>
