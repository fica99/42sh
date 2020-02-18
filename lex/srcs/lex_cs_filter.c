/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_cs_filter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 21:40:02 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/16 15:46:12 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

t_lex_cs_type	*lex_new_cs_filter(size_t size)
{
	t_lex_cs_type	*new_filler;

	if (!size)
		return (NULL);
	if (!(new_filler = (t_lex_cs_type *)
		malloc(sizeof(t_lex_cs_type) * size)))
		return (NULL);
	return (new_filler);
}

int				lex_reloc_cs_filter(t_lex_cs_type **cs_filter, size_t *size)
{
	t_lex_cs_type	*new_cs_filter;
	size_t			new_size;

	if (!cs_filter || !*cs_filter || !size || !*size)
		return (0);
	new_size = (*size) * 2;
	if (!(new_cs_filter = lex_new_cs_filter(new_size)))
		return (0);
	ft_memcpy(new_cs_filter, *cs_filter,
		sizeof(t_lex_cs_type) * (*size));
	free(*cs_filter);
	(*size) = new_size;
	*cs_filter = new_cs_filter;
	return (1);
}

void			lex_init_cs_filter(t_lex_cs_type **cs_filter,
	size_t *filter_size)
{
	if (!(*filter_size))
		(*filter_size) = SIZE_CS_FILTER;
	if (!(*cs_filter))
		(*cs_filter) = lex_new_cs_filter(*filter_size);
}
