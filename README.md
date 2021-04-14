<img src="https://i.imgur.com/I6m9zIU.png" width=100%>
<h2 align=center> 🐚 SIMPLE SHELL PROJECT🐚 </h2>
This is a colaboration project for the end of the first tremeter at Holberton School between [**Diego**](https://github.com/DiegoSusviela) and [**Toshi**](https://github.com/toshi-uy).
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

## Authors
- [**Diego**](https://github.com/DiegoSusviela) <2792@holbertonschool.com>
- [**Toshi**](https://github.com/toshi-uy) <2785@holbertonschool.com>
