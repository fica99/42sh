/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_cycle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijerde <jijerde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 21:57:09 by jijerde           #+#    #+#             */
/*   Updated: 2020/02/13 21:14:34 by jijerde          ###   ########.fr       */
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
	char	*beg;
	int		i;

	i = 0;
	new_str = ft_strnew(LINE_MAX);
	final_str = new_str;
	while (s[i] && i != sec_beg)
		*new_str++ = s[i++];
	if (for_replace != NULL)
	{
		beg = for_replace;
		while (*for_replace)
		{
			*new_str++ = *for_replace++;
		}
		if (g_f == 1)
			free(beg);
	}
	while (s[third_beg])
	{
		*new_str++ = s[third_beg++];
	}
	return (final_str);
}

void	find_indexes(int second_beg, char *s)
{
	int		i;

	g_f = 0;
	i = 0;
	while (s[i] && i <= g_br)
	{
		if (s[i] == '$')
			g_curr_doll = i;
		if (s[i] == ':')
			if ((s[i + 1] == '=' || s[i + 1] == '-' || s[i + 1] == '+'
			|| s[i + 1] == '?') && s[i + 2] == '$')
				second_beg = i + 1;
		i++;
	}
}

char	*find_rep(int second_beg, char **for_replace, int third_beg,
char *s)
{
	char *tmp;

	find_indexes(second_beg, s);
	*for_replace =
	expansions_validation(tmp = (ft_strsub(s, g_curr_doll,
	((third_beg = check_bracket(s)) - g_curr_doll) + 2)));
	free(tmp);
	if (*for_replace)
	{
		if (!(ft_strcmp(*for_replace, "err")))
		{
			if (g_f == 1)
			{
				free(*for_replace);
				g_f = 0;
			}
			return (NULL);
		}
	}
	return ("ok");
}

char	*expansions_cycle(char *s)
{
	char	*for_replace;
	int		third_beg;
	int		second_beg;
	char	*tmp;

	second_beg = 0;
	third_beg = 0;
	last_bracket(s);
	while (1)
	{
		if ((ft_strcmp(find_rep(second_beg, &for_replace, third_beg, s), "ok")))
			return (NULL);
		if (g_curr_doll == 0)
		{
			if (g_fo)
				free(s);
			return (for_replace);
		}
		tmp = triple_strcat(s, for_replace, second_beg + 1, third_beg + 2);
		if (g_fo)
			free(s);
		s = tmp;
		g_fo++;
	}
	return (s);
}
