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
	char	*param;
	char	*value;
	i = 0;
	
	param = ft_strnew(LINE_MAX);
	//value = ft_strnew(LINE_MAX);
	while (s[i] != ':')
	{
		param[i] = s[i];
		i++;
	}
	if (s[++i] == '-')
	{
		if ((value = (get_env(param, ALL_ENV))))
			return (value);
		else
		{
			return (ft_strsub(s, i + 1, ft_strlen(s) - (i + 2)));
		}
		
	}
	return (NULL);
}
