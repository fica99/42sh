/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitutions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 17:04:44 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/19 01:18:47 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

t_qt		check_quotes_type(char *str, size_t pos, t_qt qt)
{
	if (str[pos] == '"' && qt == QT_NQ && (!pos
		|| (pos > 0 && str[pos - 1] != '\\')))
		return (QT_DQ);
	else if (str[pos] == '"' && qt == QT_DQ && (!pos
		|| (pos > 0 && str[pos - 1] != '\\')))
		return (QT_NQ);
	else if (str[pos] == '\'' && qt == QT_NQ && (!pos
		|| (pos > 0 && str[pos - 1] != '\\')))
		return (QT_SQ);
	else if (str[pos] == '\'' && qt == QT_SQ && (!pos
		|| (pos > 0 && str[pos - 1] != '\\')))
		return (QT_NQ);
	else
		return (qt);
}

int			check_bs(char *str, size_t *pos)
{
	if (str[*pos] == '\\' && str[(*pos) + 1] != '\0')
	{
		(*pos) += 2;
		return (1);
	}
	return (0);
}

char		**substitutions(char **args, char is_env)
{
	if (!args)
		return (NULL);
	if (!(args = tilda_substitutions(args)))
		return (NULL);
	if (!(args = vars_substitutions(args)))
		return (NULL);
	if (!is_env)
	{
		if (!(args = pattern_substitutions(args)))
			return (NULL);
		if (!(args = arith_opers(args)))
			return (NULL);
	}
	args = cut_quotes(args);
	return (args);
}

int			process_substitutions(t_job *j)
{
	t_process	*p;

	if (!(p = j->first_process))
		return (0);
	while (p)
	{
		if (!(p->args = substitutions(p->args, 0)))
		{
			clean_all_processes(j);
			return (0);
		}
		if (p->environment
			&& !(p->environment = substitutions(p->environment, 1)))
		{
			clean_all_processes(j);
			return (0);
		}
		p = p->next;
	}
	return (1);
}
