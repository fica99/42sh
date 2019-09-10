/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 14:29:32 by ggrimes           #+#    #+#             */
/*   Updated: 2019/09/14 19:36:36 by ggrimes          ###   ########.fr       */
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
		if (!(tokens.next = get_token(str, lexer)))
			return (NULL);
		state = check_tokens(&tokens, lexer, str);
		if (state == -2)
			return (token_error());
		if (state == 0)
			break ;
	}
	return (get_union_token(lexer));
}

int			init_tokens(t_tokens *tokens, t_string *str, t_lexer *lexer)
{
	tokens->previous = NULL;
	if (!(tokens->current = get_token(str, lexer)))
		return (0);
	tokens->next = NULL;
	return (1);
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
	int		class;
	t_token	*token;
	t_token	*next_token;

	token = (t_token *)ft_fifo(1, "get", NULL);
	while ((next_token = (t_token *)ft_fifo(1, "get", NULL)))
	{
		if (!(token->lexeme = join_lexeme(token->lexeme, next_token->lexeme)))
			return (NULL);
		clear_token(&next_token);
	}
	if ((class = define_class(token->type, lexer->m_class)) == -2)
		return class_error(&token);
	token->class = class;
	return (token);
}

char		*join_lexeme(char *dest, char *src)
{
	char *tmp;

	if (!dest || !src)
		return ((dest) ? dest : src);
	if (!(tmp = ft_strjoin(dest, src)))
		return (NULL);
	free(dest);
	return (tmp);
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

/* int			check_stack(t_token **token, t_token **next_token)
{
	*next_token = NULL;
	*token = NULL;
	if ((*token = (t_token *)ft_stack(1, "get", NULL)))
		return (1);
	return (0);
} */

/* int			union_tokens(t_token **token, t_token **next_token, int t_union)
{
	if (t_union > 0)
	{
		(*token)->type = t_union;
		ft_fifo(1, "add", (void *)(*token));
		*token = *next_token;
		*next_token = NULL;
		return (0);
	}
	else if (t_union == -3)
	{
		clear_token(token);
		*token = *next_token;
		return (0);
	}
	else
	{
		ft_fifo(1, "add", (void *)(*token));
		if (*next_token)
			clear_token(next_token);
		*token = get_union_token();
		return (1);
	}
} */

/* int			go_ahead(char *str, int cur_index, int cur_type, t_lexer *lexer)
{
	int	index;
	int	state;
	int	type;

	index = cur_index;
	state = 0;
	type = 0;
	if (!str || !lexer->m_type)
		return (-2);
	while(1)
	{
		type = (state == -3) ? type : state;
		state = next_state(str[index], type, lexer);
		if (state == -4)
			state = go_ahead(str, index, type, lexer);
		if (state == -1)
		{
			type = generalize_type(type, lexer->m_generalization);
			return ((type == cur_type) ? cur_type : -1);
		}
		if (str[index])
			index++;
	}
} */

/* int			generalize_type(int type, t_matrix *m_generalization)
{
	if (type < 0 && type >= m_generalization->cols)
		return (-2);
	return (m_generalization->data[0][type]);
} */