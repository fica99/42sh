# 21sh
- 21sh project in school 21(school 42)
- Description in the file 21sh.en.pdf


## Subject:

[Subject](https://cdn.intra.42.fr/pdf/pdf/967/21sh.en.pdf)

- [x] Prompt with edition.
- [x] Builtins `cd`, `echo`, `exit`, `env`, `setenv`, `unsetenv`, `hash`, `history` with there options.
- [x] Executing simple commands with there parameters using `PATH`.
<!-- - [x] Support for redirection `>`, `>>`, `<`and `|`.
- [x] Logical operand `&&`and `||`. -->
- [x] Separator `;`.


 - [x] Inhibitors `"`, `'`.
 <!-- and `\`. -->
<!-- - [x] Advanced redirections: aggregation of file output and heredoc `<<`.
- [x] Globbing: `*`, `?`, `[]`, `{}`, etc. -->
- [x] Backquotes `\`.
<!--- [x] Subshell with operand `()`.
- [x] Local variable and builtin `unset` and `export`. -->
- [x] History with builtin `history`.

- [x] File descriptors and builtin `read` with options.
- [x] Dynamical autocompletion.


<!-- - [x] Job Control and builtins `job`, `fg`, `bg` and operand `&`.
- [X] Shell Scripting: bang (!), variable assignements, brace group, if, while, until, for and functions -->

<!-- - [X] Advanced dollar expansion `$(..)`, `$((..))`, `$[..]` -->
<!-- - [X] Tilde expansion `~`, `~<username>`, `~-`, `~+` -->
<!-- - [X] Range expansion `{<START>..<END>}` and `{<START>..<END>..<INCREMENT>}`
- [X] Advanced redirections operator `&>`, `&>>`, `<>`, `<<<` and `|&` -->
<!-- - [X] Aliases, builtin alias `alias [-p] [name[=value] …]` and expansion
- [X] Builtin env advanced options `-u name` and `[name=value]` -->
<!-- - [X] Inline variables `[name=value] binary [arguments...]` -->
- [X] Binary hashtable
- [X] Rights in the PATH

## Usage
```
Usage: ./21sh
minishell keymap:
	<home>: Go to begin of line.
	<end>: Go to end of line.
	<ctrl+V>: Paste.
	<ctrl+D>: Exit.
    <ctrl+X>: Cut.
	<ctrl+C>: Cancel line edition/Copy.
	<ctrl+[left|right]>: Move per word.
    <shift+[left|right]>: Highlighting text.
	<ctrl+[up|down]>: Move per line.
	<up>: Go up in the history.
	<down>: Go down in the history.
    <ctrl+R>: Histroy search.
