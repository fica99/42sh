/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 17:28:23 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/24 16:59:39 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <signal.h>
# include <stdint.h> //lib for uint8_t
# include <fcntl.h>
# include <termios.h>

# define RUNNING 1
# define TERM_SIGINT (1 << 1)
# define TERM_SIGQUIT (1 << 2)
# define TERM_SIGWINCH (1 << 3)
# define NORMAL_LINE 100
# define FT_HOST_NAME_MAX 255
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

typedef struct	s_term
{
	short			prompt_len;
	short			x_cur;
	short			y_cur;
	short			ws_col;
	char			*buffer;
	char			**env_cp;
	struct termios	savetty;
	short			malloc_len;
}				t_term;

# define RIGHT "\033[C"
# define LEFT "\033[D"
# define GO_RIGHT(i) ft_putstr_fd("\033[", STDIN_FILENO); ft_putnbr_fd(i, STDIN_FILENO); ft_putchar_fd('C',STDIN_FILENO)
# define GO_LEFT(i) ft_putstr_fd("\033[", STDIN_FILENO); ft_putnbr_fd(i, STDIN_FILENO); ft_putchar_fd('D',STDIN_FILENO)
# define PREV_LINE "\033[F"
# define NEXT_LINE "\033[E"
# define SAVE_CUR "\0337"
# define RESTORE_CUR "\0338"
# define CLEAN_SCREEN(fd) ft_putstr_fd("\033[0J", fd)
# define BCSP 127
# define CTRL_H 8
# define CTRL_D 4
# define CTRL_C 3
# define TAB 9
# define DEL "\033[3~"
# define CUR_CORD "\033[6n"
struct s_term	g_term;
unsigned short	g_flags;
int 			errno_f;

//make.c
char			**copy_double_arr(char **arr);
void			get_win_size(void);
char			*ft_getenv(char *arr);
short			get_count_var(char *arr);
void			set_input_mode(void);
//check.c
unsigned short	double_arr_len(char **arr);
char			*check_path(void);
//print.c
void			print_error(char *name, char *str, char *command, int p);
void			term_prompt(void);
void  			ft_putstr_cord(char *str);
void			print_environ(void);
void			print_error_withoutexit(char *name, char *str, char *command, int p);
//ft_errno.c
void 			ft_perror(char *str);
void 			pr_gen_perror(void);
//shell.c
void	        shell_start(void);
void			get_cur_cord(void);
//signal.c
void			signalling(void);
void			signal_handler(int sign);
//reading.c
void			read_prompt(void);
void			reading(void);
void			read_handler(char *c, int fd);
void			print_read(char *c);
void			print_read_other(char *c);
//make2.c
char			*strnew_realloc_buf(char *str, short len);
void			reset_input_mode (void);
void			go_left(short i);
void			go_right(short i);
//make3.c
void			del_symb(char *buf, short len);
void			print_symb(char *c, char *buf, short len);
char			*ft_strdel_el(char	*buf, size_t i);
char			*ft_stradd(char	*buf, char *s, size_t i);
pid_t			make_process(void);
//parse.c
void			parse_string(void);
void			make_command(char *buf);
char			**spec_symbols(char **args);
void			find_command(char **args);
char			*check_command(char **args);
char			*exec_command(char **args);
//make4.c
void			ft_setenv(char *name, char *new_value);
char			*join_env(char *name, char *new_value);
void			free_double_arr(char **arr);
//autocom.c
char			**get_arr_matches(char **start, int prog);
char			**match_selection(char *arg, char **arr_mat);
char			**get_dirs_arr(char *path, int flag);
char  			*get_autocom_part(char **com_arr, char *arg);
char			**get_prog_arr(char *arg);
char 			**ft_strarr_add(char **dest, char **src, char **exc);
int 			ft_strarr_len(char **str_arr);
int 			ft_cheak_exc(char *str, char **exc);
char			get_type(mode_t mode);
int 			autocom(char **buf, short len);
char 			*get_start_com(char *buf, int *prog);
int				ft_strcmp_mod(const char *str1, const char *str2, int flag);
void 			print_arr(char **arr);
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
