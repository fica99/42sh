/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 20:38:47 by ggrimes           #+#    #+#             */
/*   Updated: 2019/10/18 19:45:36 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_shell.h"

void		clear_lexer(t_lexer **lexer)
{
	clear_matrix(&((*lexer)->m_type));
	clear_matrix(&((*lexer)->m_class));
	clear_matrix(&((*lexer)->m_union));
	clear_matrix(&((*lexer)->m_priority));
	clear_matrix(&((*lexer)->m_generalization));
	free(*lexer);
	lexer = NULL;
}

void		clear_matrix(t_matrix **matrix)
{
	int	i;
	int	j;

	i = -1;
	while (++i < LEXER_ROWS)
	{
		j = -1;
		while (++j < LEXER_COLS)
			(*matrix)->data[i][j] = 0;
		free((*matrix)->data[i]);
	}
	free((*matrix)->data);
	free(*matrix);
	matrix = NULL;
}
