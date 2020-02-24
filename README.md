# 42sh

As a coder in training, there are moments, which marks your life. Forever. 42sh is one of those moments. Achieving this project is a milestone at 42(school 42).

You already know a lot of shells and each has its own features, from the humble sh available on every UNIX distribution in the world to the complete and complex zsh, which many of you use without really knowing why. There are many other shells, such as bash, csh, tcsh, ksh, ash, etc. 42sh is your first real shell.

42sh is a complete command shell written according to the POSIX standard for Unix systems.

    - Type any command
    - See result
    - Magic

### Tech

42sh uses:
* functions of the terminfo(ncurses) library
* the whole man 2 section
* malloc, free
* access
* open, close, read, write
* opendir, readdir, closedir
* getcwd, chdir
* stat, lstat
* fork, execve*
* waitpid
* signal, kill
* exit
* pipe
* dup, dup2
* isatty
* ioctl
* tcsetattr, tcgetattr

### Installation

```
$ git clone https://github.com/fica99/42sh.git
$ cd 42sh
$ make
```

### Usage

```
$ ./42sh
```
