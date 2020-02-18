/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_preprocessing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 13:45:09 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/17 23:32:51 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

static void					rewind_spases(const char *str, size_t *pos)
{
	if (!str || !pos)
		return ;
	while (ft_isspace(str[*pos]))
		(*pos)++;
}

void						lex_preprocessing(const char *str, size_t *pos)
{
	rewind_spases(str, pos);
}
