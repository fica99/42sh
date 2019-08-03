/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 13:44:16 by aashara-          #+#    #+#             */
/*   Updated: 2019/08/02 19:15:04 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include <time.h>
# include <unistd.h>

void		term_prompt(short history_len);
void		standart_prompt(void);
short		prompt_user_host(char *str, short i);
void		write_prompt(char *str, short history_len);
short		prompt_time(char *str, short i);
short		prompt_colour(char *str, short i);
short		prompt_dir_history(char *str, short i, short history_len);
#endif
