/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 17:28:23 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/14 12:58:37 by aashara-         ###   ########.fr       */
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
//colors
# define STANDART ft_putstr("\033[0m")
# define RED ft_putstr("\033[0;31m")
# define GREEN ft_putstr("\033[0;32m")
# define YELLOW ft_putstr("\033[0;33m")
# define BLUE ft_putstr("\033[0;34m")
# define PURPLE ft_putstr("\033[0;35m")
# define CYAN ft_putstr("\033[0;36m")
//errno
#define	ENOENT		2		/* No such file or directory */
#define	ENOMEM		12		/* Cannot allocate memory */
#define	EACCES		13		/* Permission denied */

typedef struct	s_cord
{
	short	prompt;
	short	x_cur;
	short	ws_col;
}				t_cord;

# define RIGHT "\033[C"
# define LEFT "\033[D"

char			**env_cp;
struct termios	savetty;
struct s_cord	cord;
unsigned short	g_flags;
int 			errno_f;

//ft_errno.c
void 			ft_perror(char *str);
void 			pr_gen_perror(void);
//signal.c
void			signalling(void);
void			signal_handler(int sign);
//reading.c
char			*read_prompt();
char			*reading(char *buf);
void			read_hander(char *c);
char			*make_buf_print(char *buf, char *c, uint8_t *n);
//get.c
short			get_count_var(char *arr);
char			*ft_getenv(char *arr);
//print.c
void			print_environ(void);
void	        shell_prompt(void);
void	        print_error_withoutexit(char *name, char *str, char *command, int p);
void	        print_error(char *name, char *str, char *command, int p);
//make.c
char			**copy_double_arr(char **arr);
void			free_double_arr(char **arr);
char			*join_env(char *name, char *new_value);
pid_t			make_process(void);
char			*strnew_realloc_buf(char *str, uint8_t *n);
//make2.c
void			get_cord(void);
void			reset_input_mode(void);
void			set_input_mode(void);
char			*ft_stradd(char *buf, char *s, size_t i);
//check.c
unsigned short	double_arr_len(char **arr);
char	        *check_new_line(char *arr);
char			*check_path(void);
void			check_key(char *c, char *buf);
//shell.c
void	        shell_start(void);
void	        find_command(char **args);
char			*exec_command(char **args);
char			*check_command(char **args);
//parse.c
void			parse_string(char *buf);
char			**spec_symbols(char **args);
void			make_command(char *buf);
//flags.c
uint8_t			add_flag(uint8_t flags, char flag, uint8_t i);
uint8_t			is_flags(uint8_t flags, char flag);
uint8_t			find_flags(char **argv, unsigned short *i, uint8_t (fun)(char s));
//cd.c
void			cd(int argc, char **argv);
char			check_ch_dir(int argc , char **argv);
char			check_request(int argc, char  **argv);
//echo.c
void			echo(int argc, char **argv);
uint8_t			flag_n(char s);
//env.c
void 			env(int argc, char **argv);
char			check_set(char **argv);
//setenv.c
void 			ft_setenv(int argc, char **argv);
void	        set_env(char *name, char *new_value);
//unsetenv.c
void			ft_unsetenv(int argc, char **argv);
char			**copy_new_arr(short i);
#endif
