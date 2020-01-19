/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 17:45:59 by ggrimes           #+#    #+#             */
/*   Updated: 2020/01/19 18:15:15 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

char	*lex_strjoin(char **s1, char **s2)
{
	char	*result_str;

	if (!(*s1) || !(*s2))
		return (NULL);
	if (!(result_str = ft_strjoin(*s1, *s2)))
		return (NULL);
	ft_strdel(s1);
	ft_strdel(s2);
	return (result_str);
}

char	*lex_add_eol(char **str)
{
	char	*newstr;

	if (!(*str))
		return (NULL);
	if (!(newstr = ft_strjoin(*str, "\n")))
		return (NULL);
	ft_strdel(str);
	return (newstr);
}
