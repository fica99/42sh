#ifndef SUB_H
#define SUB_H

typedef struct 	s_group
{
	int num;
	int dot;
	int err;
}				t_group;

/*
**	subshell.c
*/
int 	subshell_expr(char *line);
void	launch_subshell(char *sub_line);

/*
**	subgroups.c
*/
char 	*subgroups_expr(char *args);
char *char_space_join(char *src, char c);

/*
**	subgroups_comma.c
*/
char *subgroups_num_comma(char *args);
char *subgroups_comma(char *args);
char *cut_num(const char *str);

/*
**	subgroups_dot.c
*/
char *subgroups_num_dot(char *args);
char *subgroups_alph_dot(char *args);

#endif
