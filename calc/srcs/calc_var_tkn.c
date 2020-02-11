/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_var_tkn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 18:28:30 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/11 17:07:47 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

static void	calc_fill_var(t_calc_var *var, char *value, size_t size)
{
	if (!var)
		return ;
	var->size = size;
	var->value = value;
}

int			calc_var_is_valid(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && ft_isalnum(str[i]))
		i++;
	return (i);
}

int			calc_check_var(char *str, t_calc_var *var)
{
	size_t	i;
	char	temp;
	char	*value;

	if (!str || !var)
		return (0);
	if (!(i = calc_var_is_valid(str)))
		return (0);
	temp = str[i];
	str[i] = '\0';
	value = get_var(str, ALL_VARS);
	calc_fill_var(var, value, i);
	str[i] = temp;
	return (1);
}

t_calc_tkn	*calc_get_var_tkn(char *str, size_t pos, t_calc_var *var)
{
	t_calc_tkn		*token;
	t_calc_var		*new_var;

	if (!str || !var)
		return (NULL);
	if (!(token = calc_newtkn(NULL, CALC_VAR)))
		return (NULL);
	if (!(new_var = (t_calc_var *)malloc(sizeof(t_calc_var))))
	{
		calc_del_tkn(&token);
		return (NULL);
	}
	new_var = ft_memcpy((void *)new_var, (void *)var, sizeof(t_calc_var));
	token->value = (void *)new_var;
	token->start_pos = pos;
	token->end_pos = pos + var->size;
	return (token);
}
