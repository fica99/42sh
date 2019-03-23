/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 17:28:23 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/23 15:49:15 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

short	get_count_var(char *arr, char **environ);
char	*get_var(char *arr, char **environ);

uint8_t	add_flag(uint8_t flags, char flag, uint8_t i);
uint8_t	is_flags(uint8_t flags, char flag);
uint8_t	find_flags(char **argv, unsigned short *i, uint8_t (fun)(char s));
#endif
