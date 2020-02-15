/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitutions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 17:04:44 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/15 18:28:06 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

t_qt		check_quotes_type(char *str, size_t pos, t_qt qt)
{
	if (str[pos] == '"' && qt == QT_NQ)
		return (QT_DQ);
	else if (str[pos] == '"' && qt == QT_DQ)
		return (QT_NQ);
	else if (str[pos] == '\'' && qt == QT_NQ)
		return (QT_SQ);
	else if (str[pos] == '\'' && qt == QT_SQ)
		return (QT_NQ);
	else
		return (QT_NQ);
}

char		**substitutions(char **args)
{
	args = tilda_substitutions(args);
	args = vars_substitutions(args);
	args = pattern_substitutions(args);
	args = cut_quotes(args);
	return (args);
}
