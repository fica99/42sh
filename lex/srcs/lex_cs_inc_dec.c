/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_cs_inc_dec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 20:38:05 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/09 15:04:11 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

static t_lex_cs_type	lex_is_cs(const char *str)
{
	if (!ft_strncmp(str, "((", 2) || !ft_strncmp(str, "))", 2))
		return (CS_D_ROUND_BRK);
	else if (*str == '(' || *str == ')')
		return (CS_ROUND_BRK);
	else if (*str == '{' || *str == '}')
		return (CS_FIGURE_BRK);
	else if (*str == '"')
		return (CS_DOUBLE_QUOTES);
	else if (*str == '\'')
		return (CS_SINGLE_QUOTES);
	else if (*str == '`')
		return (CS_BACK_QUOTES);
	else
		return (CS_NULL);
}

static int				lex_cs_stat(const char *str)
{
	if (!ft_strncmp(str, "((", 2) || *str == '(' || *str == '{')
		return (1);
	else if (!ft_strncmp(str, "))", 2) || *str == ')' || *str == '}')
		return (-1);
	else if (*str == '"' || *str == '\'' || *str == '`')
		return (2);
	else
		return (0);
}

static int				lex_not_inc_dec(t_lex_cs_type *os_filter,
	int os_count, t_lex_cs_type check_type, size_t *offset)
{
	if (check_type == CS_NULL || (os_count > -1 && lex_cs_is_brk(check_type)
		&& lex_cs_is_quotes(os_filter[os_count])))
	{
		(*offset) += (check_type == CS_D_ROUND_BRK) ? 2 : 1;
		return (1);
	}
	return (0);
}

static t_lex_fr			lex_cs_valid(t_lex_cs_type filter_type,
	t_lex_cs_type check_type, int check, size_t *offset)
{
	if (!offset)
		return (FR_ERR);
	else if (check == -1 && filter_type == CS_D_ROUND_BRK
		&& check_type == CS_ROUND_BRK)
		return (FR_DRBRK_OPEN);
	else if (check == -1 && filter_type != check_type)
		return (FR_ERR);
	else
	{
		(*offset) += (check_type == CS_D_ROUND_BRK) ? 2 : 1;
		return (FR_OK);
	}
}

t_lex_fr				lex_cs_inc_dec(const char *str,
	int *cs_count, size_t *offset)
{
	int						check;
	t_lex_cs_type			check_type;
	static t_lex_cs_type	*cs_filter;
	static size_t			filter_size;

	if (!str || !cs_count)
		return (FR_ERR);
	lex_init_cs_filter(&cs_filter, &filter_size);
	check_type = lex_is_cs(str + *offset);
	if (lex_not_inc_dec(cs_filter, *cs_count, check_type, offset))
		return (FR_OK);
	check = lex_cs_stat(str + *offset);
	if (lex_cs_check_open(check, cs_filter, *cs_count, check_type))
		cs_filter[++(*cs_count)] = check_type;
	else if (lex_cs_check_close(check, cs_filter, *cs_count, check_type))
		(*cs_count)--;
	if (*cs_count != -1 && (size_t)(*cs_count) >= filter_size - 1)
		if (!lex_reloc_cs_filter(&cs_filter, &filter_size))
			return (FR_ERR);
	if (*cs_count > -1)
		return (lex_cs_valid(cs_filter[*cs_count], check_type, check, offset));
	(*offset) += (check_type == CS_D_ROUND_BRK) ? 2 : 1;
	return (FR_OK);
}
