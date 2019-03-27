/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 17:28:23 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/27 18:33:57 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "ft_errno.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdint.h> //lib for uint8_t
//exit(6) read error
//exit(7) command not found
//exit(9) chdir error
//exit(9) env no such file or dir

//comand not found
//too many arguments
//string not in pwd
char			**env_cp;

# define RUNNING 1
#define PROMPT_LEN 100


//get.c
short			get_count_var(char *arr);
char			*get_var(char *arr);
//print.c
void			print_environ(void);
void	        print_message(void);
void	        print_error(char *name, char *str, char *command, int p);
//make.c
char			**copy_double_arr(char **arr);
void			free_double_arr(char **arr);
char			*join_env(char *name, char *new_value);
//check.c
unsigned short	double_arr_len(char **arr);
char	        *check_new_line(char *arr);
//shell.c
void	        shell_start(void);
void	        find_command(char **args);
char	        **read_prompt(void);
void			make_new_process(ushort i, int *status);
//parse.c
char	**parse_string(char *buf);
//flags.c
uint8_t			add_flag(uint8_t flags, char flag, uint8_t i);
uint8_t			is_flags(uint8_t flags, char flag);
uint8_t			find_flags(char **argv, unsigned short *i, uint8_t (fun)(char s));
//cd.c
void			cd(int argc, char **argv);
void			check_ch_dir(int argc , char **argv);
void			check_request(int argc, char  **argv);
//echo.c
void			echo(int argc, char **argv);
uint8_t			flag_n(char s);
//env.c
void 			env(int argc, char **argv);
uint8_t         check_set(char **argv);
//setenv.c
void 			ft_setenv(int argc, char **argv);
void	        set_env(char *name, char *new_value);
//unsetenv.c
void			ft_unsetenv(int argc, char **argv);
#endif
