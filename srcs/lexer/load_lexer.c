#include "ft_shell.h"

t_lexer *load_lexer(char *path)
{
    int     fd;
    int     res;
    int     row;
    char    *line;
    t_lexer *lexer;

    if ((fd = open(path, O_RDONLY) == -1))
        return (NULL);
    res = get_next_line(fd, &line);
    if (res == 0 || res == -1)
        return (NULL);
    if (!(lexer = new_lexer()))
        return (NULL);
    row = 0;
    while (1)
    {
        res = get_next_line(fd, &line);
        if (res == -1)
            return (NULL);
        if (res == 0)
            break;
        if (!load_new_line(&lexer->matrix[row], line, &lexer->cols))
            return (NULL);
        row++;
    }
    lexer->rows = row;
    return (lexer);
}

t_lexer *new_lexer(void)
{
    t_lexer *new_lexer;

    if (!(new_lexer = (t_lexer *)malloc(sizeof(t_lexer))))
        return (NULL);
    if (!(new_lexer->matrix = create_lexer_matrix(LEXER_ROWS, LEXER_COLS)))
        return (NULL);
    return (new_lexer);
}

int **create_lexer_matrix(int rows, int cols)
{
    int i;
    int j;
    int **new_lexer_matrix;
    int *new_matrix_row;

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

int load_new_line(int **matrix_row, char *line, int *line_cols)
{
    static  int cols;
    int         i;
    char        *position;

    if (!(position = get_start_position(line)))
        return (0);
    i = 0;
    while (position)
    {
        if (!check_coll(position))
            return (0);
        (*matrix_row)[i++] = ft_atoi(position);
        position = ft_strchr(position, '|');
        position = (*position != '\0') ? position++ : position;
    }
    cols = (!cols) ? i + 1 : cols;
    *line_cols = cols;
    return ((cols == i + 1) ? 1 : 0);
}

char    *get_start_position(char *line)
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

int     check_coll(char *position)
{
    int sign;

    sign = 0;
    while (*position != '|' && *position != '\0')
    {
        if (*position == ' ')
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
