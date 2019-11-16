/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 21:50:01 by ggrimes           #+#    #+#             */
/*   Updated: 2019/11/21 20:31:08 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

int	calc(char *str, t_variables *variables)
{	
	size_t		i;
	t_calc_tkn	*token;

	variables = calc_get_variables();
	i = 0;
	while ((token = calc_get_next_tkn(str, i, variables))->type != CALC_END)
	{
		calc_print_tkn(token, variables);
		if (token->type == CALC_ERROR)
			return (0);
		i = token->end_pos;
		calc_del_tkn(&token);
	}
	calc_print_tkn(token, variables);
	calc_del_tkn(&token);
	return (0);
}