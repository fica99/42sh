/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 17:28:23 by aashara-          #+#    #+#             */
/*   Updated: 2019/05/20 13:25:30 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHELL_H
# define FT_SHELL_H

# include "libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <stdint.h>
# include <fcntl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <sys/ioctl.h>
# include "macro/colour.h"
# include "macro/command.h"
# include "macro/error.h"
# include "builtins/cd.h"
# include "builtins/env.h"
# include "builtins/echo.h"
# include "builtins/setenv.h"
# include "builtins/unsetenv.h"
# include "hash_table.h"

# define RUNNING 1
# define TERM_SIGINT (1 << 1)
# define TERM_EXIT (1 << 2)
# define NORMAL_LINE 100
# define FT_HOST_NAME_MAX 255
# define LINE_MAX 2048
# define SOMETHING "1"
# define READING 1
# define INIT_FLAGS 0

typedef struct	s_term
{
	short			x_start;
	short			y_start;
	short			x_cur;
	short			y_cur;
	short			ws_col;
	short			ws_row;
	char			*buffer;
	char			**env_cp;
	struct termios	savetty;
	short			malloc_len;
	unsigned short	hash_table_size;
	t_hash			**hash_table;
}				t_term;

struct s_term	g_term;
unsigned short	g_flags;
int				g_errno_f;

char			**copy_double_arr(char **arr);
void			init_term();
void			get_win_size(void);
void			term_start(void);
void			signalling(void);
void			signal_handler(int sign);
void			term_prompt(void);
void			get_cur_cord(void);
void			set_input_mode(void);
void			reset_input_mode (void);
void			term_prompt(void);
void			get_cur_cord(void);
void			ft_putstr_cord(char *str);
void			read_prompt(void);
void			reading(void);
void			read_handler(char *c, int fd);
char			*strnew_realloc_buf(char *str, short len);
void			print_read(char *c);
void			print_read_other(char *c);
void			go_left(short i);
void			go_right(short i);
void			prev_word(char *buf, short len);
void			next_word(char *buf);
void			del_symb(char *buf, short len);
void			print_symb(char *c, char *buf, short len);
char			*ft_strdel_el(char	*buf, size_t i);
char			*ft_stradd(char	*buf, char *s, size_t i);
char			*ft_getenv(char *arr);
short			get_count_var(char *arr);
char			*check_path(void);
void			print_error(char *name, char *str, char *command, int p);
void			print_environ(void);
void			print_error_withoutexit(char *name, char *str, char *command,
				int p);
void			ft_perror(char *str);
void			pr_gen_perror(void);
pid_t			make_process(void);
void			ft_setenv(char *name, char *new_value);
void			parse_string(void);
void			make_command(char *buf);
char			*spec_symbols(char *args);
void			find_command(char **args);
char			*check_command(char **args);
char			*exec_command(char **args);
char			*join_env(char *name, char *new_value);
char			**get_arr_matches(char **start, int prog);
char			**match_selection(char *arg, char **arr_mat);
char			**get_dirs_arr(char *path, int flag);
char			*get_autocom_part(char **com_arr, char *arg);
char			**get_prog_arr(char *arg);
char			**ft_strarr_add(char **dest, char **src, char **exc);
int				ft_strarr_len(char **str_arr);
int				ft_cheak_exc(char *str, char **exc);
char			get_type(mode_t mode);
int				autocom(char **buf, short len);
char			*get_start_com(char *buf, int *prog);
int				ft_strcmp_mod(const char *str1, const char *str2, int flag);
void			print_arr(char **arr);
void			reset_term(void);

#endif
