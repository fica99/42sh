/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 17:55:11 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/09 17:59:15 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

void	lex_print_tkns(t_lex_tkn **tokens)
{
	size_t	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i])
		lex_print_tkn(tokens[i++]);
	lex_del_tkns(tokens);
}

void	lex_print_tkn(t_lex_tkn *token)
{
	if (!token)
		return ;
	ft_putstr("*****************************************\n");
	if (token->value)
	{
		ft_putstr("token->value = |");
		ft_putstr(token->value);
		ft_putstr("|\n");
	}
	else
		ft_putstr("token->value = NULL\n");
	ft_putstr("token->type = ");
	lex_print_type(token->type);
	ft_putstr("token->class = ");
	lex_print_class(token->class);
	ft_putstr("token->start_pos = ");
	ft_putnbr((int)token->start_pos);
	ft_putstr("\n");
	ft_putstr("token->end_pos = ");
	ft_putnbr((int)token->end_pos);
	ft_putstr("\n");
	ft_putstr("*****************************************\n");
}

void	lex_print_type(t_lex_tkn_type type)
{
	if (type == T_WORD)
		ft_putstr("WORD\n");
	else if (type == T_END)
		ft_putstr("END\n");
	else if (type == T_PIPE)
		ft_putstr("PIPE\n");
	else if (type == T_GREATER)
		ft_putstr("GREATER\n");
	else if (type == T_GREATER_GREATER)
		ft_putstr("GREATER_GREATER\n");
	else if (type == T_GREATER_AND)
		ft_putstr("GREATER_AND\n");
	else if (type == T_LESS)
		ft_putstr("LESS\n");
	else if (type == T_LESS_LESS)
		ft_putstr("LESS_LESS\n");
	else if (type == T_LESS_AND)
		ft_putstr("LESS_AND\n");
	else if (type == T_SEP)
		ft_putstr("SEP\n");
	else if (type == T_IO_NUMBER)
		ft_putstr("IO_NUMBER\n");
	else if (type == T_ASSIGNMENT_WORD)
		ft_putstr("ASSIGNMENT_WORD\n");
	else if (type == T_ROUND_SUB)
		ft_putstr("ROUND_SUB\n");
	else if (type == T_FIGURE_SUB)
		ft_putstr("FIGURE_SUB\n");
	else if (type == T_ARITH_SUB)
		ft_putstr("ARITH_SUB\n");
	else if (type == T_AND_AND)
		ft_putstr("AND_AND\n");
	else if (type == T_OR_OR)
		ft_putstr("OR_OR\n");
	else if (type == T_AND)
		ft_putstr("AND\n");
	else
		ft_putstr("UNDEFINED\n");
}

void	lex_print_class(t_lex_tkn_class class)
{
	if (class == C_WORD)
		ft_putstr("WORD\n");
	else if (class == C_END)
		ft_putstr("END\n");
	else if (class == C_PIPE)
		ft_putstr("PIPE\n");
	else if (class == C_REDIR)
		ft_putstr("REDIR\n");
	else if (class == C_LOG_OPERS)
		ft_putstr("LOG_OPERS\n");
	else if (class == C_SEP)
		ft_putstr("SEP\n");
	else if (class == C_SUB)
		ft_putstr("SUB\n");
	else if (class == C_PREFIX_SUB)
		ft_putstr("PREFIX_SUB\n");
	else if (class == C_AND)
		ft_putstr("AND\n");
	else
		ft_putstr("UNDEFINED\n");
}
