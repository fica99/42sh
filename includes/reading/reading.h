/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 10:49:40 by filip             #+#    #+#             */
/*   Updated: 2019/06/08 14:39:25 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READING_H
# define READING_H

# include <unistd.h>

void	read_prompt(t_term *term);
void	reading(t_buff *buffer, t_cord *cord, t_history *history);
void	read_handler(char *c, int fd);
char	*check_quotes(char	*str, t_cord *cord);
char	*quotes_dquotes_brackets(short quotes, short dquotes, short brackets,
t_cord *cord);
#endif
