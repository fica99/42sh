/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_implementation.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijerde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 12:27:24 by jijerde           #+#    #+#             */
/*   Updated: 2019/12/17 12:29:18 by jijerde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char *exp_implement(char *s)
{
	int		i;
	int		j;
	char	*param;
	char	*value;

	i = 0;
	j = 0;
	param = ft_strnew(LINE_MAX);
	//value = ft_strnew(LINE_MAX);
	while (s[j])
	{
		j++;
		if (s[j] == '}')
			break ;
	} 
	while (s[i] != ':' && s[i] != '}')
	{
		param[i] = s[i];
		i++;
	}
	if (s[++i] == '-')
	{
		if ((value = (get_env(param, ALL_ENV))))
		{
			if (!*value)
				;
			else
				return (value);
		}
		return (ft_strsub(s, i + 1, j - (i + 1)));
	}
	else
	{
		return (get_env(param, ALL_ENV));
	}
}
