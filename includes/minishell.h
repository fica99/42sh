/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 17:28:23 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/20 14:03:00 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <signal.h>
# include <stdint.h> //lib for uint8_t
# include <fcntl.h>
# include <termios.h>

# define RUNNING 1
# define SHELL_SIGINT (1 << 1)
# define SHELL_SIGQUIT (1 << 2)
# define NORMAL_LINE 100
# define HOST_NAME_MAX 255
# define LINE_MAX 2048
# define SOMETHING "1"
# define READING 1
# define INIT_FLAGS 0
//colors
# define STANDART(fd) ft_putstr_fd("\033[0m", fd)
# define RED(fd) ft_putstr_fd("\033[0;31m", fd)
# define GREEN(fd) ft_putstr_fd("\033[0;32m", fd)
# define YELLOW(fd) ft_putstr_fd("\033[0;33m", fd)
# define BLUE(fd) ft_putstr_fd("\033[0;34m", fd)
# define PURPLE(fd) ft_putstr_fd("\033[0;35m", fd)
# define CYAN(fd) ft_putstr_fd("\033[0;36m", fd)
//errno
#define	ENOENT		2		/* No such file or directory */
#define	ENOMEM		12		/* Cannot allocate memory */
#define	EACCES		13		/* Permission denied */

typedef struct	s_cord
{
	short	prompt;
	short	x_cur;
	short	y_cur;
	short	ws_col;
	short	ws_row;
}				t_cord;

# define RIGHT "\033[C"
# define LEFT "\033[D"
# define PREV_LINE "\033[F"
# define NEXT_LINE "\033[E"
# define SAVE_CUR "\0337"
# define RESTORE_CUR "\0338"
# define CLEAN_SCREEN(fd) ft_putstr_fd("\033[0J", fd)
# define BCSP 127
# define CTRL_H 8
# define CTRL_D 4
# define DEL "\033[3~"
# define FT_ABS(value) (value) < (0)?((value == -2147483648)?0:-value):(value)

char			**env_cp;
struct termios	savetty;
struct s_cord	cord;
unsigned short	g_flags;
int 			errno_f;

//make.c
char			**copy_double_arr(char **arr);
void			get_cord(void);
char			*ft_getenv(char *arr);
short			get_count_var(char *arr);
void			set_input_mode(void);
//check.c
unsigned short	double_arr_len(char **arr);
char			*check_path(void);
//print.c
void			print_error(char *name, char *str, char *command, int p);
void			shell_prompt(void);
void  			ft_putstr_cord(char *str);
void			print_environ(void);
void			print_error_withoutexit(char *name, char *str, char *command, int p);
//ft_errno.c
void 			ft_perror(char *str);
void 			pr_gen_perror(void);
//shell.c
void	        shell_start(void);
//signal.c
void			signalling(void);
void			signal_handler(int sign);
//reading.c
char			*read_prompt();
char			*reading(char *buf);
void			read_handler(char *c);
char			*make_buf_print(char *buf, char *c, uint8_t *n);
void			check_key(char *c, char *buf, short len);
//make2.c
char			*strnew_realloc_buf(char *str, uint8_t *n);
void			reset_input_mode (void);
void			go_left(short i);
void			go_to(short i);
void			go_right(void);
//make3.c
void			del_symb(char *buf, short len);
void			print_symb(char *c, char *buf, short len);
char			*ft_strdel_el(char	*buf, size_t i);
char			*ft_stradd(char	*buf, char *s, size_t i);
pid_t			make_process(void);
//parse.c
void			parse_string(char *buf);
void			make_command(char *buf);
char			**spec_symbols(char **args);
void			find_command(char **args);
char			*check_command(char **args);
char			*exec_command(char **args);
//make4.c
void			ft_setenv(char *name, char *new_value);
char			*join_env(char *name, char *new_value);
void			free_double_arr(char **arr);
//cd.c
void			cd(int argc, char **argv);
char			check_ch_dir(int argc , char **argv);
char			check_request(int argc, char  **argv);
//echo.c
void			echo(int argc, char **argv);
//env.c
void 			env(int argc, char **argv);
char			check_set(char **argv);
//setenv.c
void 			set_env(int argc, char **argv);
//unsetenv.c
void			ft_unsetenv(int argc, char **argv);
char			**copy_new_arr(short i);
#endif
