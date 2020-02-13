/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 17:31:25 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/13 17:47:54 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

char	*vars_substitution(char *line)
{

}

static char	is_glob(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '*' || str[i] == '?' || str[i] == '[' || str[i] == ']')
			return (TRUE);
	}
	return (FALSE);
}

char		**pattern_matching(char *line)
{
	char	**res;
	glob_t	globbuf;

	res = NULL;
	if (is_glob(line))
	{
		if (glob(line, GLOB_TILDE, NULL, &globbuf))
		{
			if (!(res = ft_dardup(globbuf.gl_pathv)))
				err_exit("42sh", "malloc() error", NULL, ENOMEM);
		}
		globfree(&globbuf);
	}
	return (res);
}
