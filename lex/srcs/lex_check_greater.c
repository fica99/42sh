/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_check_greater.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 19:07:33 by ggrimes           #+#    #+#             */
/*   Updated: 2019/12/08 20:28:36 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

t_lex_tkn_type	lex_check_greater(char **str, short is_word, size_t *pos)
{
	if (is_word)
		return (T_NULL);
	else if (lex_check_fd_redir(*str, is_word, pos))
		return (T_GREATER_AND);
	else if (!ft_strncmp(*str + *pos, ">>", 2))
	{
		(*pos) += 2;
		return (T_GREATER_GREATER);
	}
	else
	{
		(*pos)++;
		return (T_GREATER);
	}
}

int				lex_check_fd_redir(char *str, short is_word, size_t *pos)
{
	size_t	i;

	if (!str)
		return (0);
	i = *pos;
	while (ft_isdigit(str[i]))
		i++;
	if (!ft_strncmp(str + i, ">&", 2))
		i += 2;
	else
		return (0);
	if (ft_isdigit(str[i]))
	{
		while (ft_isdigit(str[i]))
			i++;
	}
	else
		return (0);
	if (!is_word)
		(*pos) = i;
	return (1);
}
