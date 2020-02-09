/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_sub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 12:50:46 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/09 13:20:07 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_lex_tkn	**alias_sub(t_lex_tkn **token)
{
	char *val;

	if ((val = ft_getvar((*token)->value, g_aliases.vars)))
	{
		free((*token)->value);
		if (!((*token)->value = ft_strdup(val)))
			err_exit("42sh", "malloc() error", NULL, ENOMEM);
	}
	return (token);
}
