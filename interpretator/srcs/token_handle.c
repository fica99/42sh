/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:50:39 by mmarti            #+#    #+#             */
/*   Updated: 2019/11/28 07:50:40 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

t_token *find_token(t_token *list, int type)
{
	//todo
	return (NULL);
}

void	token_free(t_token *token)
{
	if (!token)
		return ;
	//todo
}

t_token *split_list(t_token *token)
{
	if (!token)
		return (NULL);
	token_free(token);
	return (token + 1);
}
