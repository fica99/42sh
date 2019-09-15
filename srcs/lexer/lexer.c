/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 14:29:32 by ggrimes           #+#    #+#             */
/*   Updated: 2019/09/15 23:59:01 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

t_token		*get_next_token(t_string *str, t_lexer *lexer)
{
	t_tokens	tokens;
	int			state;

	if (!init_tokens(&tokens, str, lexer))
		return (NULL);
	if (tokens.current->type == EOL || tokens.current->type == FT_ERROR)
			return (tokens.current);
	while (1)
	{
		if (!(init_next_token(&tokens.next, str, lexer)))
			return (NULL);
		state = check_tokens(&tokens, lexer, str);
		if (state == -2)
			return (token_error());
		if (state == 0)
			break ;
	}
	return (get_union_token(lexer));
}

int			init_next_token(t_token **token, t_string *str, t_lexer *lexer)
{
	if (!((*token) = get_token(str, lexer)))
			return (0);
	*token = check_space(*token, str, lexer);
	*token = check_next_token(*token, str, lexer);
	return (1);
}

int			init_tokens(t_tokens *tokens, t_string *str, t_lexer *lexer)
{
	tokens->previous = NULL;
	if (!(tokens->current = get_token(str, lexer)))
		return (0);
	tokens->current = check_space(tokens->current, str, lexer);
	tokens->next = NULL;
	return (1);
}

t_token		*check_space(t_token *token, t_string *str, t_lexer *lexer)
{
	while (token->type == SPACE)
	{
		clear_token(&token);
		if (!(token = get_token(str, lexer)))
		return (NULL);
	}
	return (token);
}

t_token		*check_next_token(t_token *token, t_string *str, t_lexer *lexer)
{
	int		state;
	t_token	*next_token;

	if (!(next_token = get_token(str, lexer)))
		return (NULL);
	next_token = check_space(next_token, str, lexer);
	state = check_union(token, next_token, lexer);
	if (state == 0 || state == -2)
		return (no_union(token, next_token, str));
	else
	{
		token = join_token(token, next_token, lexer, state);
		return (token);
	}
}

t_token		*no_union(t_token *token, t_token *next_token, t_string *str)
{
	clear_token(&next_token);
	str->index = token->fin_index;
	return (token);
}

int			check_tokens(t_tokens *tokens, t_lexer *lexer, t_string *str)
{
	if (tokens->previous)
		tokens->pc = check_union(tokens->previous, tokens->current, lexer);
	else
		tokens->pc = tokens->current->type;
	tokens->cn = check_union(tokens->current, tokens->next, lexer);
	if (tokens->pc != tokens->cn)
	{
		if (tokens->cn == -3)
			return miss_token(tokens);
		else if (tokens->cn == -2)
			return tokens_error(tokens, str);
		else if (tokens->cn == 0)
			return completed_token(tokens, str);
		else
			return different_tokens(tokens, str);
	}
	else
		return equal_tokens(tokens, str);
}

int			check_union(t_token *token, t_token *next_token, t_lexer *lexer)
{
	t_matrix	*m_union;
	int			t_type;
	int			nt_type;

	if (!token || !next_token || !lexer)
		return (-2);
	t_type = token->type;
	nt_type = next_token->type;
	m_union = lexer->m_union;
	if (t_type < 0 && t_type >= m_union->rows)
		return (-2);
	if (nt_type < 0 && nt_type >= m_union->cols)
		return (-2);
	return (m_union->data[t_type][nt_type]);
}

int			miss_token(t_tokens *tokens)
{
	if (tokens->next)
		clear_token(&(tokens->next));
	return (-3);
}

int			completed_token(t_tokens *tokens, t_string *str)
{
	if (tokens->previous)
	{
		tokens->previous->type = tokens->pc;
		ft_fifo(1, "add", (void *)(tokens->previous));
	}
	tokens->current->type = tokens->pc;
	ft_fifo(1, "add", (void *)(tokens->current));
	str->index = tokens->next->start_index;
	clear_token(&(tokens->next));
	return (0);
}

int			different_tokens(t_tokens *tokens, t_string *str)
{
	if (tokens->previous)
	{
		tokens->previous->type = tokens->pc;
		ft_fifo(1, "add", (void *)(tokens->previous));
		str->index = tokens->current->start_index;
		clear_token(&(tokens->current));
		clear_token(&(tokens->next));
		return (0);
	}
	tokens->previous = tokens->current;
	tokens->current = tokens->next;
	tokens->next = NULL;
	return (tokens->pc);
}

int			equal_tokens(t_tokens *tokens, t_string *str)
{
	if (tokens->previous)
	{
		tokens->previous->type = tokens->pc;
		ft_fifo(1, "add", (void *)(tokens->previous));
	}
	tokens->previous = tokens->current;
	tokens->current = tokens->next;
	tokens->next = NULL;
	str->index = tokens->current->fin_index;
	return (tokens->pc);
}

t_token		*get_union_token(t_lexer *lexer)
{
	t_token	*token;
	t_token	*next_token;

	token = (t_token *)ft_fifo(1, "get", NULL);
	while ((next_token = (t_token *)ft_fifo(1, "get", NULL)))
		if (!(token = join_token(token, next_token, lexer, token->type)))
			return (NULL);
	return (token);
}

t_token		*join_token(t_token *token, t_token *next_token, t_lexer *lexer, int state)
{
	char	*tmp;
	int		class;

	if (state == EXPRESS)
	{
		if (!(tmp = ft_strjoin(token->lexeme, " ")))
			return (NULL);
		free(token->lexeme);
		token->lexeme = tmp;
	}
	if (!(tmp = ft_strjoin(token->lexeme, next_token->lexeme)))
		return (NULL);
	free(token->lexeme);
	token->lexeme = tmp;
	clear_token(&next_token);
	token->type = state;
	if ((class = define_class(state, lexer->m_class)) == -2)
			return class_error(token, next_token);
	token->class = class;
	return (token);
}

void		clear_token(t_token **token)
{
	if (!*token)
		return ;
	if ((*token)->lexeme)
		free((*token)->lexeme);
	free(*token);
	*token = NULL;
}