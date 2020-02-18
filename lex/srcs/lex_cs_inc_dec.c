/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_cs_inc_dec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 20:38:05 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/18 22:53:28 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

static t_lex_cs_type	lex_is_cs(const char *str)
{
	if (*str == '(' || *str == ')')
		return (CS_ROUND_BRK);
	else if (*str == '{' || *str == '}')
		return (CS_FIGURE_BRK);
	return (CS_NULL);
}

static int				lex_cs_stat(const char *str)
{
	if (*str == '(' || *str == '{')
		return (1);
	else if (*str == ')' || *str == '}')
		return (-1);
	else
		return (0);
}

static int				lex_cs_check_open(int check, t_lex_cs_type *cs_filter)
{
	if (!cs_filter)
		return (0);
	if (check == 1)
		return (1);
	return (0);
}

static int				lex_cs_check_close(int check, t_lex_cs_type *cs_filter,
	int cs_count, t_lex_cs_type type)
{
	if (!cs_filter)
		return (0);
	if (cs_count == -1)
		return (0);
	if (cs_filter[cs_count] != type)
		return (-1);
	if (check == -1)
		return (1);
	return (0);
}

t_lex_fr				lex_cs_inc_dec(const char *str,
	int *cs_count, size_t *offset)
{
	int						check;
	t_lex_cs_type			check_type;
	static t_lex_cs_type	*cs_filter;
	static size_t			filter_size;
	int						is_valid;

	if (!str || !cs_count)
		return (FR_ERR);
	is_valid = 0;
	lex_init_cs_filter(&cs_filter, &filter_size);
	check_type = lex_is_cs(str + *offset);
	if (check_type == CS_NULL)
		return (FR_TRUE);
	check = lex_cs_stat(str + *offset);
	if (lex_cs_check_open(check, cs_filter))
		cs_filter[++(*cs_count)] = check_type;
	else if ((is_valid = lex_cs_check_close(check,
		cs_filter, *cs_count, check_type)))
		(*cs_count)--;
	if (is_valid == -1)
		return (FR_ERR);
	if (*cs_count != -1 && (size_t)(*cs_count) >= filter_size - 1)
		if (!lex_reloc_cs_filter(&cs_filter, &filter_size))
			return (FR_ERR);
	return (FR_TRUE);
}
