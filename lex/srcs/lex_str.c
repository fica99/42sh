/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 17:45:59 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/17 23:02:56 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

char	*lex_strjoin(char *s1, char *s2)
{
	char	*result_str;

	if (!s1 || !s2)
		return (NULL);
	if (!(result_str = ft_strjoin(s1, s2)))
		return (NULL);
	free(s1);
	free(s2);
	return (result_str);
}

char	*lex_add_eol(char *str)
{
	char	*result_str;

	if (!str)
		return (NULL);
	if (!(result_str = ft_strjoin(str, "\n")))
		return (NULL);
	free(str);
	return (result_str);
}

void	lex_clear_strs(char **s1, char **s2)
{
	if (s1)
	{
		if (*s1)
		{
			free(*s1);
			*s1 = NULL;
		}
	}
	if (s2)
	{
		if (*s2)
		{
			free(*s2);
			*s2 = NULL;
		}
	}
}
