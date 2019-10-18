/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 20:32:19 by ggrimes           #+#    #+#             */
/*   Updated: 2019/10/18 19:45:36 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_shell.h"

t_matrix	*new_matrix(void)
{
	t_matrix	*matrix;

	if (!(matrix = (t_matrix *)malloc(sizeof(t_matrix))))
		return (NULL);
	if (!(matrix->data = create_lexer_matrix(LEXER_ROWS, LEXER_COLS)))
		return (NULL);
	matrix->cols = 0;
	matrix->rows = 0;
	return (matrix);
}

int			**create_lexer_matrix(int rows, int cols)
{
	int	i;
	int	j;
	int	**new_lexer_matrix;
	int	*new_matrix_row;

	if (!(new_lexer_matrix = (int **)malloc(sizeof(int *) * rows)))
		return (NULL);
	i = -1;
	while (++i < rows)
	{
		if (!(new_matrix_row = (int *)malloc(sizeof(int) * cols)))
			return (NULL);
		j = -1;
		while (++j < cols)
			new_matrix_row[j] = 0;
		new_lexer_matrix[i] = new_matrix_row;
	}
	return (new_lexer_matrix);
}

t_matrix	*load_matrix_from_file(int fd)
{
	int			res;
	char		*line;
	t_matrix	*matrix;

	line = NULL;
	res = get_next_line(fd, &line);
	if (res == 0 || res == -1)
		return (NULL);
	free(line);
	if (!(matrix = new_matrix()))
		return (NULL);
	while ((res = get_next_line(fd, &line)))
	{
		if (res == -1 || matrix->rows >= LEXER_ROWS)
			return (NULL);
		if (!load_new_line(matrix, line))
			return (NULL);
		free(line);
		matrix->rows++;
	}
	return (matrix);
}

int			load_new_line(t_matrix *matrix, char *line)
{
	int			i;
	char		*position;

	if (!(position = get_start_position(line)))
		return (0);
	i = -1;
	while (position && *position)
	{
		if (!check_coll(position) || i >= LEXER_COLS)
			return (0);
		matrix->data[matrix->rows][++i] = ft_atoi(position);
		position = ft_strchr(position, '|');
		if (position && *position)
			position++;
	}
	if (matrix->cols == 0)
		matrix->cols = i + 1;
	return ((matrix->cols == i + 1) ? 1 : 0);
}

char		*get_start_position(char *line)
{
	int i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '|' && line[i + 1] != '\0')
			if (line[i + 1] == '|')
				return (line + i + 2);
	}
	return (NULL);
}
