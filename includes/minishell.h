/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 17:28:23 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/26 12:51:50 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdint.h> //lib for uint8_t
# include <stdio.h> //errors


char			**env_cp;

# define RUNNING 1
#define PROMPT_LEN 100


//get.c
short			get_count_var(char *arr, char **environ);
char			*get_var(char *arr, char **environ);
//print.c
void			print_environ(char **environ);
void	        print_message(void);
//make.c
char			**copy_double_arr(char **arr);
void			free_double_arr(char **arr);
//check.c
unsigned short	double_arr_len(char **arr);
char	        *check_new_line(char *arr);
//shell.c
void	        shell_start(void);
void	        find_command(char **args);
//main.c
void	        read_prompt(void);
//parse.c
void			parse_string(char *buf);
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
uint8_t			check_set(char **argv);
//setenv.c
void 			ft_setenv(int argc, char **argv);
void	        set_env(char *name, char *new_value);
//unsetenv.c
void			ft_unsetenv(int argc, char **argv);
#endif
