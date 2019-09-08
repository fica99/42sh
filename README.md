# 21sh

## Desctiption

School 42 project in UNIX branch\. My first real functional shell. A lot of features such as autocompletion, history, line edition that allow you to use hotkeys for example\. Full description in
[subject file](https://cdn.intra.42.fr/pdf/pdf/967/21sh.en.pdf "school project")\.

## Compilation

* `make` \- executable file compilation\.
* `make loadlibs` \- download libraries\.
* `make removelibs` \- download libraries\.
* `make all` \- same as `make`\.
* `make fclean` \- removing objects directory, full cleaning library archieve directory(removing libraries archieve and objects directory with library in every library directory) and executable file\.
* `make clean` \- removing objects directory, full cleaning library archieve directory(removing libraries archieve and objects directory with library in every library directory)\.
* `make oclean` \- removing objects directory\.
* `make lfclean` \- full cleaning library archieve directory(removing libraries archieve and objects directory with library in every library directory)\.
* `make llfclean` \- full cleaning every library directory(removing objects directory with library in every library directory)\.
* `make llclean` \- cleaning every library directory(removing objects directory in every library directory)\.
* `make llall` \- full compilation every library\.
* `make lall` \- full compilation libraries archieve\.
* `make re` \- removing all intermediate files and after that executable file compilation\.

## Usage

>make

>./21sh

## Features

* Separator `;`\.
* Redirections `[command] > {filename}`, `[command] < {filename}`, `[command] >> {filename}`, `[command] 2> {filename}`, `[command] 2>> {filename}`, `[command] &> {filename}`, `[command] >& {filename}`, `[command] &>> {filename}` and `[command] >>& {filename}`\.
* Several redirections `[command] [redirection] {filename} [redirection] {filename2} ...`\.
* Pipe `|`\.
* Several pipes `[command] [pipe] [command] [pipe] [command] ...`\.
* Inhibitors `"`, `'` and `\`\.

### Line edition hotkeys:
	<home>: Go to begin of line.
	<end>: Go to end of line.
	<ctrl+[up|down]>: Move per line.
	<ctrl+[left|right]>: Move per word.
	<ctrl+D>: If there is a line, then work as well as delete; otherwise, force exit.
	<ctrl+V>: Paste.
	<ctrl+X>: Cut.
	<ctrl+C>: If there is a highlighted text, then work as well as copy; otherwise, cancel line or stop process.
	<ctrl+\>: Quit command with core dumped error.
	<shift+[left|right]>: Highlighting text.
	<up>: Go up in the history.
	<down>: Go down in the history.
    <ctrl+R>: Histry search.
	<tab>: dinamical autocomplete

### Builtins

* `cd [path]` \- change directory\. If no arguments, path is the value of HOME environment variable\. "cd -" will move you into the previous directory\.
* `env` \- display all environment variables\.
* `echo` \- display a line of text\.
* `history` \- display a history of commands\.
* `hash` \- display a hash table with binary files from the value of PATH environment variable\.
* `setenv [ENV=value]` \- change or add an environment variable\.
* `unsetenv [ENV]` \- remove an environment variable\.
* `exit` \- exit 21sh\.

### Environment variable

* Ability to change standart prompt with PS1 and continuation prompt with PS2:
	- \u: Display the current username\.
	- \h: Display the hostname\.
	- \\$: Display # (indicates root user) if the effective UID is 0, otherwise display a $\.
	- \H: Display FQDN hostname\.
	- Colour prompt\.
	- \d : the date in “Weekday Month Date” format (e.g., “Tue May 26”)\.
	- \D{format} : the format is passed to strftime(3) and the result is inserted into the prompt string; an empty format results in a locale-specific time representation\. The braces are required\.
	- \s : the name of the shell, the basename of $0 (the portion following the final slash)\.
	- \t : the current time in 24-hour HH:MM:SS format\.
	- \T : the current time in 12-hour HH:MM:SS format\.
	- \@ : the current time in 12-hour am/pm format\.
	- \A : the current time in 24-hour HH:MM format\.
	- \w : the current working directory, with $HOME abbreviated with a tilde\.
	- \W : the basename of the current working directory, with $HOME abbreviated with a tilde\.
	- \\! : the history number of this command\.
	- \\# : the history number of this command\.
* When the cd command is given, it checks for the directory name in the current directory and throws error if not found, else traverses to the directory\. If the CDPATH is set, the "cd" command starts finding the directory in the list of directories present in the CDPATH variable and then makes the directory switch appropriately\.

Note: The $PATH environment variable contains all the paths where binarys to exec\. Delete it is not the best way of usage\.

## Created with:

* POSIX standart libraries\.
* Terminfo library for cursor movements\.
