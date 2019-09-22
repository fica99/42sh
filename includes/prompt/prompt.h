/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 13:44:16 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/22 20:29:18 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include <time.h>
# include <unistd.h>

# define TIME_BRACKETS 2
# define FT_HOST_NAME_MAX 255
/*
**	prompt.c
*/
void		term_prompt(void);
void		standart_prompt(void);
void		write_prompt(char *str);
short		prompt_user_host(char *str, short i);
/*
**	prompt_other.c
*/
short		prompt_dir_history(char *str, short i);
short		prompt_time(char *str, short i);
short		check_time_flags(char *str, short i, struct tm *info);
short		prompt_colour_name(char *str, short i);
short		time_format_flag(char *str, short i, struct tm *info);
/*
**	path.c
*/
char		*get_path(void);
char		*get_cur_dir(void);
#endif
