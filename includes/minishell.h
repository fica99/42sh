/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 17:28:23 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/25 21:59:58 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h> //errors

char			**env_cp;

# define RUNNING 1
#define PROMPT_LEN 100

short			get_count_var(char *arr, char **environ);
char			*get_var(char *arr, char **environ);
void			print_environ(char **environ);

char			**copy_double_arr(char **arr);
unsigned short	double_arr_len(char **arr);
void			free_double_arr(char **arr);

void	        print_message(void);
void	        shell_start(void);
void	read_prompt(void);
void	parse_string(char *buf);
char	*check_new_line(char *arr);
void	find_command(char *args);

uint8_t			add_flag(uint8_t flags, char flag, uint8_t i);
uint8_t			is_flags(uint8_t flags, char flag);
uint8_t			find_flags(char **argv, unsigned short *i, uint8_t (fun)(char s));
#endif
