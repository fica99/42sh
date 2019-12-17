#include "ft_shell.h"

char *char_space_join(char *src, char c)
{
	char *line;
	char *str;

	str = ft_strnew(2);
	str[0] = c;
	str[1] = ' ';
	if (src)
		line = ft_strjoin(src, str);
	else
		line = ft_strdup(str);
	ft_strdel(&str);
	return (line);
}

static int is_numeric(t_group **value, const char *args)
{
	int err;
	int num;
	int i;

	i = 0;
	err = 0;
	num = 0;
	if (ft_strchr(args, ','))
		return (num);
	while (args[i])
	{
		if (args[i] >= 48 && args[i] <= 57)
			num++;
		else if (args[i] != '.' && args[i] != '{' && args[i] != '}')
			err++;
		i++;
	}
	if (num > 0 && err > 0)
		(*value)->err += 1;
	return (num);
}

static int check_valid_numeric(const char *args)
{
	int i;
	int err;

	i = 0;
	err = 0;
	while (args[i])
	{
		if (err == 0 && args[i] == '.' && args[i + 1] != '.')
			return (1);
		else if (args[i] == '.')
			err--;
		else if (err < -2)
			return (1);
		i++;
	}
	return (0);
}

static int check_valid_alph(const char *args)
{
	int i;
	int err;

	i = 0;
	err = 0;
	while (args[i])
	{
		if (err == 0 && args[i] == '.' && i != 2)
			return (1);
		else if (err == 0 && args[i] == '.' && args[i + 1] != '.')
			return (1);
		else if (args[i] == '.')
			err--;
		else if (err < -2)
			return (1);
		i++;
	}
	return (0);
}

static t_group *check_valid_subgroup_expr(const char *args)
{
	t_group *res;

	res = (t_group *)malloc(sizeof(t_group));
	res->err = 0;
	res->dot = 0;
	res->num = 0;
	if (ft_strchr(args, ' ') || ft_strchr(args, '\t') || ft_strchr(args, '\n') ||
			ft_strlen(args) < 3 || args[ft_strlen(args) - 1] != '}')
		res->err += 1;
	res->num = is_numeric(&res, args);
	if (res->num > 0)
		res->err += check_valid_numeric(args);
	else
		res->err += check_valid_alph(args);
	return (res);
}

char 	*subgroups_expr(char *args)
{
	t_group *value;
	char *op_expr;

	value = check_valid_subgroup_expr(args);
	if (value->err > 0)
		return args;
	value->dot = ft_strchr(args, ',') ? 0 : 1;
	if (value->dot == 0)
		op_expr = value->num ? NULL : subgroups_comma(args);
	else
		op_expr = value->num ? subgroups_num_dot(args) : subgroups_alph_dot(args);
	ft_putstr(op_expr);
	ft_putstr("\n");
	free(value);
	exit(0);
	return (op_expr);
}