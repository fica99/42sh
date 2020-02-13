/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_brackets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijerde <jijerde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 15:14:08 by jijerde           #+#    #+#             */
/*   Updated: 2020/02/13 21:15:26 by jijerde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

int		last_bracket(char *s)
{
	int i;
	int	numb_of_br;
	int	last_bracket;

	i = 0;
	numb_of_br = 0;
	last_bracket = 0;
	while (s[i])
	{
		if (s[i] == '{')
			numb_of_br++;
		if (s[i] == '}')
		{
			numb_of_br--;
			if (numb_of_br == 0)
			{
				last_bracket = i;
				return (last_bracket);
			}
		}
		i++;
	}
	return (last_bracket);
}

int		check_bracket(char *s)
{
	int i;

	g_fo = 0;
	g_curr_doll = 0;
	i = 0;
	if (s[i] == '}' || ((s[i] == '_' && s[i + 1] == '}')))
		return (0);
	while (s[i])
	{
		if (s[i] == '}')
		{
			if (i == 1)
				return (1);
			return (i - 1);
		}
		i++;
	}
	return (0);
}
