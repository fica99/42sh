/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_hist_expansions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 14:00:45 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/06 15:28:59 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static int		update_hist_expansion(char **buffer, int start_i, int end_i)
{
	char	*to_find;
	char	*exp;
	char	*right;
	char	*left;

	if (!(to_find = ft_strsub(*buffer, start_i, end_i - start_i)))
		rl_err("42sh", "malloc() error", ENOMEM);
	exp = get_hist_expansions(to_find);
	ft_strdel(&to_find);
	if (!(right = ft_strdup(*buffer + end_i)))
		rl_err("42sh", "malloc() error", ENOMEM);
	if (!(left = ft_strsub(*buffer, 0, start_i - 1)))
		rl_err("42sh", "malloc() error", ENOMEM);
	ft_strdel(buffer);
	if (!(*buffer = ft_strnew(ft_strlen(left) + ft_strlen(exp) +
													ft_strlen(right))))
		rl_err("42sh", "malloc() error", ENOMEM);
	*buffer = ft_strcat(ft_strcat(ft_strcpy(*buffer, left), exp), right);
	ft_strdel(&exp);
	ft_strdel(&left);
	ft_strdel(&right);
	return (start_i);
}

static int		get_end_index_hist_expansion(char *buffer, int start_i)
{
	while (ft_isalnum(buffer[++start_i]))
		;
	return (start_i);
}

char			check_hist_expansions(char **buffer)
{
	int		i;
	char	flag;

	i = -1;
	flag = FALSE;
	while ((*buffer)[++i])
	{
		if ((!i || !ft_isalnum((*buffer)[i - 1])) && (*buffer)[i] == '!')
		{
			if (ft_isalnum((*buffer)[i + 1]) || (*buffer)[i + 1] == '!'
			|| (*buffer)[i + 1] == '-')
			{
				flag = TRUE;
				i = update_hist_expansion(buffer, i + 1,
				get_end_index_hist_expansion(*buffer, i + 1));
			}
		}
	}
	return (flag);
}
