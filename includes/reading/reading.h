/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 10:49:40 by filip             #+#    #+#             */
/*   Updated: 2019/07/03 14:43:50 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READING_H
# define READING_H

# include <unistd.h>

void	read_prompt(t_term *term);
void	reading(t_line *line);
void	read_handler(char *c, int fd);
void	set_input_mode(struct termios *savetty);
void	reset_input_mode(struct termios *savetty);
#endif
