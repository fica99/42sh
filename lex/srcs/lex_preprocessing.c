/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_preprocessing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 13:45:09 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/09 14:10:23 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

static void					rewind_spases(const char *str, size_t *pos)
{
	if (!str || !pos)
		return ;
	while (str[*pos] == ' ')
		(*pos)++;
}

static t_lex_prefix_prop	lex_prefix_prop(const char *str, size_t *pos)
{
	if (!str || !pos)
		return (PP_NULL);
	if (str[*pos] != '$')
		return (PP_ALL);
	if (str[(*pos) + 1] == '(' || str[(*pos) + 1] == '{')
	{
		(*pos)++;
		return (PP_PREFIX);
	}
	return (PP_ALL);
}

void						lex_preprocessing(const char *str, size_t *pos,
	t_lex_prefix_prop *prefix_prop)
{
	rewind_spases(str, pos);
	*prefix_prop = lex_prefix_prop(str, pos);
}
