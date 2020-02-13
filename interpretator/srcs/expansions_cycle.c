/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_cycle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijerde <jijerde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 21:57:09 by jijerde           #+#    #+#             */
/*   Updated: 2020/02/13 02:55:06 by jijerde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

void	*exp_error(char *s)
{
    err("42sh", s, "operand expected", "syntax error");
    return ("err");
}

char	*triple_strcat(char *s, char *for_replace, int sec_beg, int third_beg)
{
	char	*new_str;
	char	*final_str;
	int		i;

	i = 0;
	new_str = ft_strnew(LINE_MAX);
	final_str = new_str;
	while (s[i] && i != sec_beg)
	{
		*new_str++ = s[i++];
	}
	if (for_replace != NULL)
	{
		while(*for_replace)
		{
			*new_str++ = *for_replace++;
		}
	}
	while(s[third_beg])
	{
		*new_str++ = s[third_beg++];
	}
	//free(s);
	return (final_str);
}	

char	*expansions_cycle(char *s)
{
	int		i;
	int		curr_doll;
	char	*for_replace;
	int		third_beg;
	int		second_beg;
	char	*tmp;
	char	*tmp2;
	int		f;

	f = 0;
	while (1)
	{
		i = 0;
		while (s[i])
		{
			if (s[i] == '$')
				curr_doll = i;
			if (s[i] == ':')
				if ((s[i + 1] == '=' || s[i + 1] == '-' || s[i + 1] == '+' 
				|| s[i + 1] == '?') && s[i + 2] == '$')
					second_beg = i + 1;
			i++;
		}
		for_replace = expansions_validation(tmp = (ft_strsub(s, curr_doll, 
		((third_beg = check_bracket(s)) - curr_doll) + 2)));
		free(tmp);
		if (for_replace)
		{
			if (!(ft_strcmp(for_replace, "err")))
				return (NULL);
		}
		if (curr_doll == 0)
		{
			if (f)
				free(s);
			return (for_replace);
		}
		tmp2 = triple_strcat(s, for_replace, second_beg + 1, third_beg + 2);
		if (f)
		{
			free(s);
			f++;
		}
		s = tmp2;
		if (!(ft_strchr(s, '$')))
			break ;
	}
	return (s);
}