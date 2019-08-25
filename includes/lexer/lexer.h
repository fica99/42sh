#ifndef LEXER_H
# define LEXER_H
# define LEXER_COLS 100
# define LEXER_ROWS 200

typedef struct s_lexer
{
    int rows;
    int cols;
    int **matrix;
}              t_lexer;

t_lexer *load_lexer(char *path);
t_lexer *new_lexer(void);
int     **create_lexer_matrix(int rows, int cols);
int     load_new_line(int **matrix_row, char *line, int *cols);
char    *get_start_position(char *line);
int     check_coll(char *position);

#endif