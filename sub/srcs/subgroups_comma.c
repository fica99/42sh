#include "ft_shell.h"

char *cut_num(const char *str)
{
	int i;
	char *res;

	i = 0;
	res = ft_strnew(64);
	while (str[i] && str[i] != '.' &&
			str[i] != ',' && str[i] != '{' && str[i] != '}')
	{
		res[i] = str[i];
		i++;
	}
	res[i] = ' ';
	return (res);
}

char *subgroups_comma(char *args)
{
	char *tmp;
	char *num;
	char *str;
	int i;

	i = 0;
	str = NULL;
	tmp = NULL;
	while (args[i])
	{
		if (args[i] != ',' && args[i] != '{' && args[i] != '}')
		{
			if (str)
			{
				tmp = ft_strdup(str);
				ft_strdel(&str);
			}
			if (args[i + 1] != ',' && args[i + 1] != '{' && args[i + 1] != '}')
			{
				num = cut_num(args + i);
				str = ft_strjoin(tmp, num);
				ft_strdel(&num);
			}
			else
				str = char_space_join(tmp, args[i]);
			while (args[i] && args[i] != ',' && args[i] != '{' && args[i] != '}')
				i++;
			ft_strdel(&tmp);
		}
		i++;
	}
	return (str);
}