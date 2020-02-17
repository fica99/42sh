/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic_operation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: work <work@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 09:30:29 by work              #+#    #+#             */
/*   Updated: 2020/02/17 10:43:42 by work             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"
#include "calc.h"

static size_t	check_ao(char *str, size_t pos)
{
	short		is_ao;

	if (ft_strncmp(str + pos, "$((", 3))
		return (0);
	pos += 3;
	is_ao = 0;
	while (str[pos])
	{
		if (!ft_strncmp(str + pos, "))", 2))
		{
			is_ao = 1;
			pos += 2;
		}
	}
	if (is_ao)
		return (pos);
	return (0);
}

static char 	*calc_str_result(char *str, size_t end)
{
	char				*str_res;
	char				c;
	long long			res;
	static t_calc_err	*err;

	c = str[end];
	str[end] = '\0';
	res = calc(str, &err);
	if (err->status == 1)
	{
		str[end] = c;
		return (NULL);
	}
	if (!(str_res = calc_ltoa(res)))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	str[end] = c;
	return (str_res);
}

static char		*add_ao(char **args, size_t i, size_t start, size_t end)
{

	char				*new_str;
	char				*calc_res;
	size_t				calc_len;
	size_t				str_len;

	if (!(calc_res = calc_str_result(args[i], end)))
	{
		ft_free_dar(args);
		return (NULL);
	}
	calc_len = ft_strlen(calc_res);
	str_len = ft_strlen(args[i]);
	if (!(new_str = ft_strnew(str_len - (end - start) + calc_len)))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	ft_memcpy(args[i], new_str, start);
	ft_memcpy(calc_res, new_str + start + 1, calc_len);
	ft_memcpy(args[i] + end, new_str + start + calc_len, str_len - end);
	free(args[i]);
	return (new_str);
}

char			**arith_opers(char **args)
{
	size_t		i;
	size_t		j;
	size_t		end;
	t_qt		qt;

	i = 0;
	while (args[i])
	{
		j = 0;
		qt = QT_NQ;
		while (args[i][j])
		{
			if (check_bs(args[i], &j))
				continue ;
			qt = check_quotes_type(args[i], j, qt);
			if (qt != QT_SQ)
				if ((end = check_ao(args[i], j)))
					if (!(args[i] = add_ao(args, i, j, end)))
						return (NULL);
			j++;
		}
		i++;
	}
	return (args);
}
