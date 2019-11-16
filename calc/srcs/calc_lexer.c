/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 16:53:08 by ggrimes           #+#    #+#             */
/*   Updated: 2019/11/21 20:40:30 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

t_calc_tkn	*calc_get_next_tkn(char *str, size_t pos, t_variables *variables)
{
	size_t  i;

	if (!str)
		return (NULL);
	str = str + pos;
	i = 0;
	while (str[i] == ' ')
        i++;
    return (calc_define_tkn(str + i, pos + i, variables));
}

t_calc_tkn  *calc_define_tkn(char *str, size_t pos, t_variables *variables)
{
    if (!str)
        return (NULL);
    else if (!*str)
        return (calc_newtkn(NULL, CALC_END));
    else if (!strncmp(str, "&&", 2) || !strncmp(str, "||", 2))
        return (calc_get_log_tkn(str, pos));
    else if (!strncmp(str, "==", 2) || !strncmp(str, "!=", 2))
        return (calc_get_eq_tkn(str, pos));
    else if (*str == '<' || *str == '>')
        return (calc_get_com_tkn(str, pos));
    else if (!ft_strncmp(str, "++", 2) || !ft_strncmp(str, "--", 2))
        return (calc_get_inc_tkn(str, pos));
    else if (*str == '+' || *str == '-')
        return (calc_get_add_tkn(str, pos));
    else if (*str == '*' || *str == '/' || *str == '%')
        return (calc_get_mul_tkn(str, pos));
    else
        return (calc_define_tkn_next(str, pos, variables));  
}

t_calc_tkn  *calc_define_tkn_next(char *str, size_t pos, t_variables *variables)
{
    int var_id;

    if (ft_isdigit(*str))
        return (calc_get_number_tkn(str, pos));
    else if (variables && (var_id = calc_check_variables(str, variables)) != -1)
         return (calc_get_var_tkn(str, pos, var_id, variables));
    else
        return (calc_newtkn((void *)ft_strdup("Lexer syntax error!"), CALC_ERROR));
}

t_calc_tkn	*calc_newtkn(void *value, t_calc_tkntype type)
{
	t_calc_tkn	*token;

	if (!(token = (t_calc_tkn *)malloc(sizeof(t_calc_tkn))))
		return (NULL);
	token->value = value;
	token->type = type;
    token->start_pos = 0;
    token->end_pos = 0;
	token->left = NULL;
	token->right = NULL;
	return (token);
}

t_calc_tkn  *calc_get_number_tkn(char *str, size_t pos)
{
    size_t      i;
    char        *value;
    t_calc_tkn  *token;

    if (!str)
        return (NULL);
    i = 0;
    while (ft_isdigit(str[i]))
        i++;
    if (!(value = ft_strsub(str, 0, i)))
        return (NULL);
    if (!(token = calc_newtkn((void *)value, CALC_NUMBER)))
    {
        ft_memdel((void **)&value);
        return (NULL);
    }
    token->start_pos = pos;
    token->end_pos = pos + i;
    return (token);
}

void        calc_del_tkn(t_calc_tkn **token)
{
    if (!token || !*token)
        return ;
    if ((*token)->value)
        free((*token)->value);
    (*token)->type = 0;
    (*token)->left = NULL;
    (*token)->right = NULL;
    free(*token);
    *token = NULL;    
}