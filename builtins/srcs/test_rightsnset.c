/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_rightsnset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijerde <jijerde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 21:07:33 by jijerde           #+#    #+#             */
/*   Updated: 2020/02/03 21:11:19 by jijerde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int	rights_n_set(char **argv, struct stat lstb, struct stat stb)
{
	if (argv[1][1] == 'u')
		if (S_ISUID & (lstb.st_mode) || S_ISUID & (stb.st_mode))
			return (0);
	if (argv[1][1] == 'g')
		if (S_ISGID & (lstb.st_mode) || S_ISGID & (stb.st_mode))
			return (0);
	if (argv[1][1] == 'w')
		if (S_IWUSR & (lstb.st_mode) || S_IWUSR & (stb.st_mode))
			return (0);
	if (argv[1][1] == 'x')
		if (S_IXUSR & (lstb.st_mode) || S_IXUSR & (stb.st_mode))
			return (0);
	if (argv[1][1] == 'r')
		if (S_IRUSR & (lstb.st_mode) || S_IRUSR & (stb.st_mode))
			return (0);
	return (1);
}

int	test_types(char **argv, struct stat lstb, struct stat stb)
{
	int ret;

	if (argv[1][1] == 's' || argv[1][1] == 'd' || argv[1][1] == 'c'
	|| argv[1][1] == 'b')
	{
		if ((ret = is_dir_char_block(argv, lstb, stb)) == 0)
			return (0);
		if (ret == 1)
			return (1);
	}
	if (argv[1][1] == 's' || argv[1][1] == 'p' || argv[1][1] == 'L'
	|| argv[1][1] == 'S' || argv[1][1] == 'f')
	{
		if ((ret = is_pipe_link_sock_file(argv, lstb, stb)) == 0)
			return (0);
		if (ret == 1)
			return (1);
	}
	return (1);
}

int	s_or_file(char **argv)
{
	int				fd;
	char			tmp;

	if (argv[1][1] == 'f')
		return (0);
	fd = open(argv[2], O_RDONLY);
	if (read(fd, &tmp, 1) == 0)
	{
		close(fd);
		return (1);
	}
	return (0);
}
