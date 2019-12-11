/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 17:28:01 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/19 18:14:02 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

/*int		ft_ishx(char c)
{
	if ((20 <= (90 - c) <= 25) || (20 <= (122 - c) <= 25))
		return (1);
	return (0);
}

int		ft_ifx(char *s)
{
	int i;

	i = 0;
	if (ft_isdigit(s[i]) || ft_ishx(s[i]))
	{
		if (ft_isdigit)
	}
	return (i);
}*/

int		ft_eflag(int i, char **argv, int argc, int *flags)
{
	int				j;

	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == '\\' && argv[i][j + 1] == '\\' && argv[i][j + 2])
			{
				j += 2;
				if (argv[i][j] == 'n')
					ft_putchar_fd('\n', STDOUT_FILENO);
				else if (argv[i][j] == 'a')
					ft_putchar_fd('\a', STDOUT_FILENO);
				else if (argv[i][j] == 'b')
					ft_putchar_fd('\b', STDOUT_FILENO);
				else if (argv[i][j] == 'f')
					ft_putchar_fd('\f', STDOUT_FILENO);
				else if (argv[i][j] == 'r')
					ft_putchar_fd('\r', STDOUT_FILENO);
				else if (argv[i][j] == 't')
					ft_putchar_fd('\t', STDOUT_FILENO);
				else if (argv[i][j] == 'v')
					ft_putchar_fd('\v', STDOUT_FILENO);
				else if (argv[i][j] == '\\')
					ft_putchar_fd('\\', STDOUT_FILENO);
				else if (argv[i][j] == 'c')
				{
					flags[0] = 1;
					return (argc);
				}
				/*else if (argv[i][j] == 'x')
				{
					j += ft_ifx(argv[i] + j);
				}*/
				else
				{
					if (argv[i][j - 3] != '\\')
						ft_putchar_fd('\\', STDOUT_FILENO);
					ft_putchar_fd(argv[i][j], STDOUT_FILENO);
				}
			}
			else if (argv[i][j] == '\\')
				;
			else
				ft_putchar_fd(argv[i][j], STDOUT_FILENO);
			j++;
		}
		if (argc != (i + 1))
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	return (i);
}

int		ft_echoflags(int *flags, char **argv)
{
	int	i;
	int				j;

	i = 1;
	ft_bzero(flags, 3 * sizeof(int));
	while (argv[i] && argv[i][0] == '-' && argv[i][1])
	{
		j = 1;
		while (argv[i][j])
		{
			if (argv[i][j] == 'n')
				flags[0] = 1;
			else if (argv[i][j] == 'e' || argv[i][j] == 'E')
			{
				if (argv[i][j] == 'e')
					flags[1] = 1;
				else
					flags[1] = 0;
			}
			else
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

void	ft_echo(int argc, char **argv, char **env_cp)
{
	int				i;
	int				j;
	int				flags[3];

	i = ft_echoflags(flags, argv);
	if (flags[1] == 1)
		i = ft_eflag(i, argv, argc, flags);
	(void)env_cp;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == '$' && argv[i][j + 1] != '$' && argv[i][j + 1] == '{')
				if (check_bracket(&(argv[i][j + 2])))
					expansions(&(argv[i][j + 2]));
			while (argv[i][j] == '\\')
			{
				if (argv[i][j + 1] == '\\')
				{
					ft_putchar_fd('\\', STDOUT_FILENO);
					j += 2;
				}
				else
					j++;
			}
			if (argv[i][j])
				ft_putchar_fd(argv[i][j], STDOUT_FILENO);
			j++;
		}
		i++;
		if (argc != i)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (flags[0] == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
