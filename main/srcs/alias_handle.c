/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_alias.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 05:50:22 by mmarti            #+#    #+#             */
/*   Updated: 2020/02/11 05:59:28 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char			*ft_getalias(char *name, char **varlist)
{
	char	*tmp;
	long	varlen;

	if (!name || !*name)
		return (NULL);
	while (*varlist)
	{
		tmp = ft_strchr(*varlist, '=');
		varlen = tmp - *varlist;
		if ((long)ft_strlen(name) == varlen &&
				!ft_strncmp(name, *varlist, varlen))
			return (*varlist);
		++varlist;
	}
	return (NULL);
}

int				check_cycle(char *alias, t_cycle_list *l)
{
	while (l)
	{
		if (!strcmp(alias, l->name))
			return (1);
		l = l->next;
	}
	return (0);
}

t_lex_tkn		**get_alias_tkn(t_lex_tkn **tkn, char *val, t_cycle_list **l)
{
	t_lex_tkn	**ret;
	char		*alias;
	t_lex_tkn	**new_tkn;

	if (!(alias = ft_getalias(val, g_aliases.vars)))
		return (tkn);
	if (check_cycle(alias, *l))
		return (NULL);
	add_to_cycle_list(alias, l);
	alias = ft_strchr(alias, '=') + 1;
	if (!tkn)
		new_tkn = lex_get_tkns(&alias);
	else
		new_tkn = lex_insert_tkns(tkn, lex_get_tkns(&alias), 0);
	ret = get_alias_tkn(new_tkn, (*new_tkn)->value, l);
	return (ret);
}

void			skip_delim(t_lex_tkn **list, int *i)
{
	while (list[*i]->class != C_END)
	{
		if (list[*i]->class == C_SEP || list[*i]->class == C_PIPE
				|| list[*i]->class == C_AND || list[*i]->class == C_LOG_OPERS)
			break ;
		(*i)++;
	}
}

t_lex_tkn		**alias_handle(t_lex_tkn **list)
{
	t_lex_tkn			**new;
	int					i;
	static t_cycle_list	*l;

	i = 0;
	while (list[i]->class != C_END)
	{
		if (list[i]->type == T_WORD)
		{
			if ((new = get_alias_tkn(NULL, list[i]->value, &l)))
				list = lex_insert_tkns(list, new, i);
			skip_delim(list, &i);
			if (list[i]->class == C_END)
				break ;
		}
		i++;
	}
	free_cycle_list(l);
	l = NULL;
	return (list);
}
