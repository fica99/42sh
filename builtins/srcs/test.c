/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijerde <jijerde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 22:01:45 by jijerde           #+#    #+#             */
/*   Updated: 2020/02/03 22:03:31 by jijerde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int		is_exist(char **argv)
{
	int ret;

	if ((!(ft_strcmp(argv[1], "-z"))) || (!(ft_strcmp(argv[1], "!"))))
		if (!*argv[2])
			return (0);
	if ((ret = (works_with_dir(argv))) == 0)
		return (0);
	return (1);
}

static int		dash_flags(char **argv)
{
	int ret;

	if ((!(ft_strcmp(argv[1], "-e"))) || (!(ft_strcmp(argv[1], "-s")))
	|| (!(ft_strcmp(argv[1], "-z"))) || (!(ft_strcmp(argv[1], "-d")))
	|| (!(ft_strcmp(argv[1], "-f"))) || (!(ft_strcmp(argv[1], "-c")))
	|| (!(ft_strcmp(argv[1], "-b"))) || (!(ft_strcmp(argv[1], "-p")))
	|| (!(ft_strcmp(argv[1], "-L"))) || (!(ft_strcmp(argv[1], "-S")))
	|| (!(ft_strcmp(argv[1], "-u"))) || (!(ft_strcmp(argv[1], "-g")))
	|| (!(ft_strcmp(argv[1], "-w"))) || (!(ft_strcmp(argv[1], "-x")))
	|| (!(ft_strcmp(argv[1], "-r"))) || (!(ft_strcmp(argv[1], "!"))))
	{
		if ((ret = is_exist(argv)) == 0)
			return (0);
		return (1);
	}
	if (argv[3])
		err("42sh", "test", "binary operator expected", argv[1]);
	else
		err("42sh", "test", "unary operator expected", argv[1]);
	return (2);
}

static int		is_dash(char **argv)
{
	int ret;

	if ((ret = iscomparison(argv)) == 0)
		return (0);
	if (ret == 1)
		return (1);
	if (ret == 2)
		return (2);
	if ((ret = dash_flags(argv)) == 0)
		return (0);
	if (ret == 1)
		return (1);
	if (ret == 2)
		return (2);
	return (3);
}

static int		what_is(char **argv)
{
	int ret;

	if (argv[1] && !(argv[2]))
		return (0);
	if (argv[1][0] == '-' || (!(ft_strcmp(argv[1], "!"))))
		return (is_dash(argv));
	else
	{
		if ((ret = iscomparison(argv)) == 0)
			return (0);
		if (ret == 1)
			return (1);
		if (ret == 2)
			return (2);
		if (ret == 3)
		{
			if (argv[3])
				err("42sh", "test", "binary operator expected", argv[1]);
			else
				err("42sh", "test", "unary operator expected", argv[1]);
			return (2);
		}
	}
	return (1);
}

int				ft_test(int argc, char **argv)
{
	int ret;

	if (argc < 2)
		return (1);
	if (argc > 4)
	{
		err("42sh", "test", "too many arguments", NULL);
		return (2);
	}
	if ((ret = what_is(argv)) == 0)
		return (0);
	if (ret == 1)
		return (1);
	if (ret == 2)
		return (2);
	return (1);
}
