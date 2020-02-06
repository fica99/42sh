/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_existntype.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 12:42:40 by jijerde           #+#    #+#             */
/*   Updated: 2020/02/06 16:21:01 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	is_file_socket(char **argv, struct stat lstb, struct stat stb)
{
	if (argv[1][1] == 's' || argv[1][1] == 'S')
	{
		if (S_ISSOCK(lstb.st_mode) || S_ISSOCK(stb.st_mode))
		{
			if (argv[1][1] == 's')
				return (1);
			return (0);
		}
	}
	if (argv[1][1] == 's' || argv[1][1] == 'f')
	{
		if (S_ISREG(lstb.st_mode) || S_ISREG(stb.st_mode))
			return (s_or_file(argv));
	}
	return (2);
}

static int	is_namedpipe_link(char **argv, struct stat lstb, struct stat stb)
{
	if (argv[1][1] == 's' || argv[1][1] == 'p')
	{
		if (S_ISFIFO(lstb.st_mode) || S_ISFIFO(stb.st_mode))
		{
			if (argv[1][1] == 's')
				return (1);
			return (0);
		}
	}
	if (argv[1][1] == 's' || argv[1][1] == 'L')
	{
		if ((S_ISLNK(lstb.st_mode) || S_ISLNK(stb.st_mode)))
		{
			if (argv[1][1] == 'L')
				return (0);
			if ((stb.st_size) == 0 || (stb.st_mode) == 0)
				return (1);
			return (0);
		}
	}
	return (2);
}

int			is_dir_char_block(char **argv, struct stat lstb, struct stat stb)
{
	if (argv[1][1] == 's' || argv[1][1] == 'd')
	{
		if (S_ISDIR(lstb.st_mode) || S_ISDIR(stb.st_mode))
			return (0);
	}
	if (argv[1][1] == 's' || argv[1][1] == 'c')
	{
		if (S_ISCHR(lstb.st_mode) || S_ISCHR(stb.st_mode))
		{
			if (argv[1][1] == 's')
				return (1);
			return (0);
		}
	}
	if (argv[1][1] == 's' || argv[1][1] == 'b')
	{
		if (S_ISBLK(lstb.st_mode) || S_ISBLK(stb.st_mode))
		{
			if (argv[1][1] == 's')
				return (1);
			return (0);
		}
	}
	return (2);
}

int			is_pipe_link_sock_file(char **argv, struct stat lstb,
struct stat stb)
{
	int ret;

	if (argv[1][1] == 's' || argv[1][1] == 'p' || argv[1][1] == 'L')
	{
		if ((ret = is_namedpipe_link(argv, lstb, stb)) == 0)
			return (0);
		if (ret == 1)
			return (1);
	}
	if (argv[1][1] == 's' || argv[1][1] == 'S' || argv[1][1] == 'f')
	{
		if ((ret = is_file_socket(argv, lstb, stb)) == 0)
			return (0);
		if (ret == 1)
			return (1);
	}
	return (2);
}

int			file_was_found(char **argv)
{
	struct stat		lstb;
	struct stat		stb;

	if (argv[1][1] == 'e')
		return (0);
	if (lstat(argv[2], &lstb) != -1)
	{
		if (stat(argv[2], &stb) == -1)
			err("42sh", "stat error()", NULL, NOERROR);
		if (argv[1][1] == 's' || argv[1][1] == 'd' || argv[1][1] == 'f'
		|| argv[1][1] == 'c' || argv[1][1] == 'b' || argv[1][1] == 'p'
		|| argv[1][1] == 'L' || argv[1][1] == 'S')
			return (test_types(argv, lstb, stb));
		if (argv[1][1] == 'u' || argv[1][1] == 'g' || argv[1][1] == 'w'
		|| argv[1][1] == 'x' || argv[1][1] == 'r')
			return (rights_n_set(argv, lstb, stb));
	}
	return (1);
}
