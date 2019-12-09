#include "ft_shell.h"

char *join_space(char *str)
{
	char *tmp;
	char *res;

	tmp = ft_strdup(str);
	ft_strdel(&str);
	res = ft_strjoin(tmp, " ");
	return (res);
}

char *num_seq(char *begin, char *end)
{
	int start;
	int finish;
	char *str;
	char *tmp;
	char *num;

	str = NULL;
	tmp = NULL;
	start = ft_atoi(begin);
	finish = ft_atoi(end);
	while (start <= finish)
	{
		if (str)
		{
			tmp = ft_strdup(str);
			ft_strdel(&str);
		}
		num = ft_itoa(start);
		str = ft_strjoin(tmp, num);
		str = join_space(str);
		ft_strdel(&num);
		ft_strdel(&tmp);
		start++;
	}
	while (start >= finish)
	{
		if (str)
		{
			tmp = ft_strdup(str);
			ft_strdel(&str);
		}
		num = ft_itoa(start);
		str = ft_strjoin(tmp, num);
		str = join_space(str);
		ft_strdel(&num);
		ft_strdel(&tmp);
		start--;
	}
	return (str);
}

char *subgroups_num_dot(char *args)
{
	char *begin;
	char *end;
	char *str;

	begin = cut_num(args + 1);
	end = cut_num(args + ft_strlen(begin) + 2);
	str = num_seq(begin, end);
	return (str);
}

char *subgroups_alph_dot(char *args)
{
	char begin;
	char end;
	char *tmp;
	char *str;

	str = NULL;
	tmp = NULL;
	begin = args[1];
	end = args[ft_strlen(args) - 2];
	if (begin > end)
	{
		begin = args[ft_strlen(args) - 2];
		end = args[1];
	}
	while (begin <= end)
	{
		if (str)
		{
			tmp = ft_strdup(str);
			ft_strdel(&str);
		}
		str = char_space_join(tmp, begin);
		begin++;
	}
	return (str);
}