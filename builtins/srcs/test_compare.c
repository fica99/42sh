/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_compare.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijerde <jijerde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 17:03:27 by jijerde           #+#    #+#             */
/*   Updated: 2020/02/03 21:50:02 by jijerde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int		unary_error(char **argv)
{
	ft_error("42sh", "test", "unary operator expected", argv[1]);
	return (2);
}

static int		isnumeric_comparison(char **argv)
{
	if (!(ft_strcmp(argv[2], "-lt")) || !(ft_strcmp(argv[2], "-le")))
	{
		if (argv[3] && (ft_atoi(argv[1]) < ft_atoi(argv[3])))
			return (0);
		if (!(ft_strcmp(argv[2], "-le")) && argv[3] &&
			(ft_atoi(argv[1]) == ft_atoi(argv[3])))
			return (0);
		if (!(argv[3]))
			return (unary_error(argv));
		return (1);
	}
	else if (!(ft_strcmp(argv[2], "-ge")))
	{
		if (argv[3] && (ft_atoi(argv[1]) >= ft_atoi(argv[3])))
			return (0);
		if (!(argv[3]))
			return (unary_error(argv));
		return (1);
	}
	return (3);
}

int				iscomparison(char **argv)
{
	int ret;

	if (!(ft_strcmp(argv[2], "=")) || !(ft_strcmp(argv[2], "-eq")))
	{
		if (argv[3] && (!(ft_strcmp(argv[1], argv[3]))))
			return (0);
		if (!(argv[3]))
			return (unary_error(argv));
		return (1);
	}
	else if (!(ft_strcmp(argv[2], "!=")) || !(ft_strcmp(argv[2], "-ne")))
	{
		if (argv[3] && (ft_strcmp(argv[1], argv[3])))
			return (0);
		if (!(argv[3]))
			return (unary_error(argv));
		return (1);
	}
	else if (!(ret = (isnumeric_comparison(argv))))
		return (0);
	else if (ret == 2)
		return (2);
	else if (ret == 1)
		return (1);
	return (3);
}
