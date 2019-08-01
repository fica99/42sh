/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 13:44:16 by aashara-          #+#    #+#             */
/*   Updated: 2019/08/01 15:36:29 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include <time.h>
# include <unistd.h>

# define START_TIME 11
# define END_TIME 16

void		term_prompt(void);
void		standart_prompt(void);
short		prompt_user_host_dir(char *str, short i);
void		write_prompt(char *str);
short		prompt_time_root(char *str, short i);
short		prompt_colour(char *str, short i);
#endif
