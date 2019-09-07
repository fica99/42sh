/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 21:18:50 by ggrimes           #+#    #+#             */
/*   Updated: 2019/09/07 19:21:04 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

t_lexer		*load_lexer(void)
{
	t_lexer	*lexer;

	lexer = new_lexer();
	if (!(lexer->m_type = get_matrix("srcs/lexer/types_matrix")))
		return (NULL);
	if (!(lexer->m_class = get_matrix("srcs/lexer/classes_matrix")))
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

t_matrix	*load_matrix_from_file(int fd)
{
	int			res;
	char		*line;
	t_matrix	*matrix;

	line = NULL;
	res = get_next_line(fd, &line);
	if (res == 0 || res == -1)
		return (NULL);
	if (!(matrix = new_matrix()))
		return (NULL);
	while ((res = get_next_line(fd, &line)))
	{
		if (res == -1 || matrix->rows >= LEXER_ROWS)
			return (NULL);
		if (!load_new_line(matrix, line))
			return (NULL);
		matrix->rows++;
	}
	return (matrix);
}

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

void		print_matrix(t_matrix *matrix)
{
	int	i;
	int	j;

	i = -1;
	if (!matrix)
		return ;
	while (++i < matrix->rows)
	{
		j = -1;
		while (++j < matrix->cols)
		{
		ft_putnbr(matrix->data[i][j]);
			ft_putchar(' ');
		}
		ft_putchar('\n');
	}
}

void		clear_lexer(t_lexer **lexer)
{
	clear_matrix(&((*lexer)->m_type));
	clear_matrix(&((*lexer)->m_class));
	free(*lexer);
	lexer = NULL;
}

void		clear_matrix(t_matrix **matrix)
{
	int	i;
	int	j;

	i = 0;
	while (i < LEXER_ROWS)
	{
		j =0;
		while (j < LEXER_COLS)
		{
			(*matrix)->data[i][j++] = 0;
		}
		free((*matrix)->data[i++]);
	}
	free((*matrix)->data);
	free(*matrix);
	matrix = NULL;
}
