/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijerde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 06:05:14 by jijerde           #+#    #+#             */
/*   Updated: 2019/12/11 15:02:49 by jijerde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int		check_bracket(char *s)
{
	int i;

	i = 0;
	if (s[i++] == '}')
		return (0);
	while (s[i])
	{
		if (s[i] == '}')
			return (1);
		i++;
	}
	return (0);
}

void	*expansions(char *s)
{
	//if we see $ character, and the next is {, we go here with pointer
	//after {. And we sure for } at the end.
	int		i;
	char	var[100];

	ft_bzero(var, 100);
	i = 0;
	if (s[i] == '#')
		return ((int *)ft_strlen(sh_getenv(s + i)));
	while (s[i] != '}' && s[i] != ':' && s[i] != '%' && s[i] != '#')
	{
		var[i] = s[i];
		i++;
	}
	return (0);
}
