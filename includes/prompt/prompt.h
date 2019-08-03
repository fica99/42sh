/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 13:44:16 by aashara-          #+#    #+#             */
/*   Updated: 2019/08/04 00:16:55 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include <time.h>
# include <unistd.h>

# define TIME_BRACKETS 2

void		term_prompt(short history_len, char *name);
void		standart_prompt(void);
short		prompt_user_host(char *str, short i);
void		write_prompt(char *str, short history_len, char *name);
short		prompt_time(char *str, short i);
short		check_time_flags(char *str, short i, struct tm *info);
short		prompt_colour_name(char *str, short i, char *name);
short		prompt_dir_history(char *str, short i, short history_len);
short		time_format_flag(char *str, short i, struct tm *info);
#endif
