/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_tkn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 19:56:59 by ggrimes           #+#    #+#             */
/*   Updated: 2019/12/01 14:49:36 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

t_calc_tkn	*calc_newtkn(void *value, t_calc_tkntype type)
{
	t_calc_tkn	*token;

	if (!(token = (t_calc_tkn *)malloc(sizeof(t_calc_tkn))))
		return (NULL);
	token->value = value;
	token->type = type;
    token->start_pos = 0;
    token->end_pos = 0;
	token->next = NULL;
	return (token);
}

void        calc_del_tkn(t_calc_tkn **token)
{
    if (!token || !*token)
        return ;
    if ((*token)->value)    
        ft_memdel((void **)&(*token)->value);
    (*token)->type = 0;
    (*token)->next = NULL;
    free(*token);
    *token = NULL;   
}