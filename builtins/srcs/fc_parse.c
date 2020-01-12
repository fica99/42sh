/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 22:41:15 by aashara-          #+#    #+#             */
/*   Updated: 2020/01/12 22:54:32 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static char	fc_parse_editor(t_fc *fc, int argc, char **argv, int *i)
{
	if (argc < 3)
		return (FALSE);
	fc->editor = argv[++(*i)];
	return (TRUE);
}

static char	fc_parse_flags(t_fc *fc, char *arg)
{
	short	i;

	i = 0;
	while (arg[++i])
	{
		if (arg[i] == 'l')
			fc->flag_l = TRUE;
		else if (arg[i] == 'r')
			fc->flag_r = TRUE;
		else if (arg[i] == 'n')
			fc->flag_n = TRUE;
		else
			return (FALSE);
	}
	return (TRUE);
}

static void	fc_parse_first_last(t_fc *fc, char *arg)
{
	if (!fc->first)
		fc->first = arg;
	else if (!fc->last)
		fc->last = arg;
}

char		fc_parse_args(t_fc *fc, int argc, char **argv)
{
	int		i;
	char	flags;

	i = 0;
	flags = TRUE;
	while (++i < argc)
	{
		if (i == 1 && !ft_strcmp(argv[i], "-e"))
		{
			if (!fc_parse_editor(fc, argc, argv, &i))
				return (FALSE);
		}
		else if (*argv[i] == '-')
		{
			if (flags == FALSE || !fc_parse_flags(fc, argv[i]))
				return (FALSE);
		}
		else
		{
			flags = FALSE;
			fc_parse_first_last(fc, argv[i]);
		}
	}
	return (TRUE);
}
