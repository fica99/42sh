/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 14:29:32 by ggrimes           #+#    #+#             */
/*   Updated: 2019/09/02 21:58:41 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_shell.h"

t_token		*get_next_token(t_string *str, t_lexer *lexer)
{
	t_lexer_params	prm;

	if (!str || !lexer)
		return (NULL);
	initial_lexer_params(&prm, str->index);
	while (1)
	{
		prm.type = prm.state;
		prm.state = next_state(str->str[prm.index], prm.state, lexer->m_type);
		if (prm.state == -1)
			return (ready_token(str, prm, lexer->m_class));
		if (prm.state == -2)
			return token_error();
		if (str->str[prm.index])
			prm.index++;
	}
}

void		initial_lexer_params(t_lexer_params *prm, int start_index)
{
	prm->start_index = start_index;
	prm->index = start_index;
	prm->state = 0;
	prm->type = 0;
}

int			next_state(char symbol, int state, t_matrix *m_type)
{
	if (symbol < 0 && symbol >= m_type->rows)
		return (-2);
	if (state < 0 && state >= m_type->cols)
		return (-2);
	return (m_type->data[(int)symbol][state]);
}

t_token		*new_token(void)
{
	t_token	*token;

	if (!(token = (t_token *)malloc(sizeof(t_token))))
		return (NULL);
	token->lexeme = NULL;
	token->type = 0;
	token->class = 0;
	return (token);
}

t_token		*ready_token(t_string *str, t_lexer_params prm, t_matrix *m_class)
{
	t_token *token;
	int		len;
	int		class;

	if (!(token = new_token()))
		return (NULL);
	len = prm.index - prm.start_index;
	token->lexeme = ft_strsub(str->str, prm.start_index, len);
	token->type = prm.type;
	if ((class = define_class(prm.type, m_class)) == -2)
		return class_error(&token);
	token->class = class;
	str->index = prm.index;
	return (token);
}

int			define_class(int type, t_matrix *m_class)
{
	if (type < 0 && type >= m_class->cols)
		return (-2);
	return (m_class->data[0][type]);
}

t_token		*class_error(t_token **token)
{
	if (token)
	{
		ft_memdel((void **)&(*token)->lexeme);
		free(*token);
		token = NULL;
	}
	return token_error();
}

t_token		*token_error(void)
{
	t_token	*token;

	if (!(token = new_token()))
		return (NULL);
	token->type = FT_ERROR;
	token->class = C_FT_ERROR;
	return (token);
}

t_token		*eof_token(void)
{
	t_token	*token;

	if (!(token = new_token()))
		return (NULL);
	token->type = EOL;
	token->class = C_SEP;
	return (token);
}

// debug

void		print_token(t_string *str)
{
	t_token	*token;

	if (!(token = get_next_token(str, g_lexer)))
		return ;
	ft_putchar('\n');
	ft_putstr(token->lexeme);
	ft_putchar('\n');
	while (token)
	{
		if (!(token = get_next_token(str, g_lexer)))
			return ;
		if (token->type == FT_ERROR)
		{
			ft_putstr("Error");
			ft_putchar('\n');
			return ;
		}
		if (token->type == EOL)
		{
			ft_putstr("EOF");
			ft_putchar('\n');
			return ;
		}
		ft_putstr(token->lexeme);
		ft_putchar('\n');
	}
	return ;
}
