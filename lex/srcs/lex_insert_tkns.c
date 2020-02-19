/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_insert_tkns.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 20:08:21 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/19 20:24:33 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

size_t				lex_tkns_size(t_lex_tkn **tkns)
{
	size_t			i;

	if (!tkns || !*tkns)
		return (0);
	i = 0;
	while (tkns[i]->type != T_END)
		i++;
	return (i);
}

static t_lex_tkn	**lex_insert_new_tkns(size_t src_size,
	size_t ins_size, size_t ins_index)
{
	t_lex_tkn		**new_tkns;

	if (ins_index > src_size)
		return (NULL);
	if (!(new_tkns = (t_lex_tkn **)malloc(sizeof(t_lex_tkn *)
		* (src_size + ins_size + 2))))
		return (NULL);
	return (new_tkns);
}

static void			lex_insert_free_tkns(t_lex_tkn **src, t_lex_tkn **ins)
{
	free(src);
	free(ins);
}

static void			lex_check_end_tkn(t_lex_tkn **tkns, size_t i)
{
	t_lex_tkn		*end;

	if (i > 1 && tkns[i - 1]->type != T_END)
	{
		if (!(end = lex_new_tkn()))
			err_exit("42sh", "malloc() error", NULL, ENOMEM);
		end->type = T_END;
		end->class = C_END;
		tkns[i] = end;
		tkns[i + 1] = NULL;
		return ;
	}
	tkns[i] = NULL;
}

t_lex_tkn			**lex_insert_tkns(t_lex_tkn **src,
	t_lex_tkn **ins, size_t ins_index)
{
	t_lex_tkn		**new_tkns;
	size_t			src_size;
	size_t			ins_size;
	size_t			i;
	size_t			j;

	src_size = lex_tkns_size(src);
	ins_size = lex_tkns_size(ins);
	if (!(new_tkns = lex_insert_new_tkns(src_size, ins_size, ins_index)))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	i = 0;
	j = 0;
	while (i < ins_index)
		new_tkns[j++] = src[i++];
	lex_del_tkn(src[i++]);
	ft_memcpy(new_tkns + j, ins, ins_size * sizeof(t_lex_tkn *));
	j += ins_size;
	lex_del_tkn(ins[ins_size]);
	while (i <= src_size)
		new_tkns[j++] = src[i++];
	lex_check_end_tkn(new_tkns, j);
	lex_insert_free_tkns(src, ins);
	return (new_tkns);
}
