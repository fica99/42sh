/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 21:18:50 by ggrimes           #+#    #+#             */
/*   Updated: 2019/10/18 19:45:36 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_shell.h"

t_lexer		*load_lexer(void)
{
	t_lexer	*lexer;

	lexer = new_lexer();
	if (!(lexer->m_type = get_matrix("srcs/lexer/matrixs/types_matrix")))
		return (NULL);
	if (!(lexer->m_class = get_matrix("srcs/lexer/matrixs/classes_matrix")))
		return (NULL);
	if (!(lexer->m_union = get_matrix("srcs/lexer/matrixs/union_matrix")))
		return (NULL);
	if (!(lexer->m_priority = get_matrix("srcs/lexer/matrixs/priority_matrix")))
		return (NULL);
	if (!(lexer->m_generalization =
		get_matrix("srcs/lexer/matrixs/generalization_matrix")))
		return (NULL);
	return (lexer);
}

t_lexer		*new_lexer(void)
{
	t_lexer	*lexer;

	if (!(lexer = (t_lexer *)malloc(sizeof(t_lexer))))
		return (NULL);
	lexer->m_class = NULL;
	lexer->m_type = NULL;
	return (lexer);
}

t_matrix	*get_matrix(char *path)
{
	int			fd;
	t_matrix	*matrix;

	if ((fd = open(path, O_RDONLY)) == -1)
		return (NULL);
	if (!(matrix = load_matrix_from_file(fd)))
		return (NULL);
	close(fd);
	return (matrix);
}

int			check_coll(char *position)
{
	int sign;

	sign = 0;
	while (*position != '|' && *position != '\0')
	{
		if (*position == ' ' || *position == '\t')
			position++;
		else if ((*position == '+' || *position == '-') && !sign)
		{
			sign = !sign;
			position++;
		}
		else if (ft_isdigit(*position))
			position++;
		else
			return (0);
	}
	return (1);
}
