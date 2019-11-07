/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:54:41 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/05 20:07:35 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	init_curr_pwd(void)
{
	if (!(g_curr_dir = getwd(NULL)))
		err_exit(g_argv[0], "getwd() error", NULL, NOERROR);
	ft_setenv("PWD", g_curr_dir);
}

//char 	check_loop(char **argv, char *path)
//{
//	struct stat buf;
//
//	if ((lstat(path, &buf)) < 0)
//		err_exit(g_argv[0], "lstat() error", NULL, NOERROR);
//
//}

char	check_request(char **argv, char *path)
{
	struct stat	buf;

	if (path && !access(path, F_OK))
	{
		if ((stat(path, &buf)) < 0)
			err_exit(g_argv[0], "stat() error", NULL, NOERROR);
		if (!S_ISDIR(buf.st_mode))
			err(argv[0], "not a directory", path, NOERROR);
		else if (access(path, R_OK))
			err(argv[0], NULL, path, EACCES);
//		else if (chdir(path) == -1)
//			err_exit(g_argv[0], "chdir() error", path, NOERROR);
		return (TRUE);
	}
	err("42sh", argv[0], "no such file or directory", path);
	return (FALSE);
}

//void	check_ch_dir(int argc, char **argv)
//{
//	char	*path;
//
//	if ((argc == 1 || !ft_strcmp(argv[1], "--")))
//		path = sh_getenv("HOME");
//	else if (!ft_strcmp(argv[1], "-"))
//	{
//		ft_putstr_fd(path = sh_getenv("OLDPWD"), STDOUT_FILENO);
//		ft_putchar_fd('\n', STDOUT_FILENO);
//	}
//	else
//		path = argv[1];
//	if (!check_request(argv, path))
//	{
//		if ((path = check_cdpath(path)))
//		{
//			(!check_request(argv, path)) ? err(argv[0], NULL, path, ENOENT)
//			: ft_putstr_fd(ft_strcat(path, "\n"), STDOUT_FILENO);
//			ft_memdel((void**)&path);
//			return ;
//		}
//		err(argv[0], NULL, path, ENOENT);
//	}
//}
//
//char	*check_cdpath(char *path)
//{
//	char	**paths;
//	char	*final_path;
//	short	i;
//	char	*cdpath;
//
//	if (!(cdpath = sh_getenv("CDPATH")))
//		return (NULL);
//	if (!(paths = ft_strsplit(cdpath, ':')))
//		err_exit(g_argv[0], "malloc() error", NULL, ENOMEM);
//	if (!(final_path = ft_strnew(FT_PATH_MAX)))
//		err_exit(g_argv[0], "malloc() error", NULL, ENOMEM);
//	i = -1;
//	while (paths[++i])
//	{
//		ft_strcat(final_path, *paths);
//		ft_strcat(final_path, "/");
//		ft_strcat(final_path, path);
//		if (!access(final_path, F_OK))
//			break ;
//		ft_strclr(final_path);
//	}
//	ft_free_dar(paths);
//	if (!(*final_path))
//		ft_strcat(final_path, path);
//	return (final_path);
//}
//
//void	cd(int argc, char **argv, char **env_cp)
//{
//	char	buf[MAXDIR];
//	char	*pwd;
//
//	(void)env_cp;
//	if (argc >= 3)
//	{
//		if (argc > 3)
//			err(argv[0], "too many arguments", NULL, NOERROR);
//		else if (argc == 3)
//			err(argv[0], "string not in pwd", argv[1], NOERROR);
//		return ;
//	}
//	else
//		check_ch_dir(argc, argv);
//	if (!(getcwd(buf, MAXDIR)))
//		err_exit(g_argv[0], "getcwd() error", argv[1], NOERROR);
//	if ((pwd = sh_getenv("PWD")))
//	{
//		ft_setenv("OLDPWD", pwd);
//		ft_setenv("PWD", buf);
//	}
//}

char **check_flags(char **av, t_cdf *flags)
{
	int i;
	int j;

	j = 1;
	i = 1;
	flags->P = 0;
	flags->L = 0;
	while (av[j] && av[j][0] == '-')
	{
		while (av[j][i])
		{
			if (**av == 'L')
				flags->L = 1;
			else if (**av == 'P')
				flags->P = 1;
			else
				return (0);
			i++;
		}
		j++;
		i = 0;
	}
	return (&av[j]);
}

//int check_args(size_t dirc, char **av)
//{
//	if (dirc >= 3)
//	{
//		if (dirc > 3)
//			err(av[0], "too many arguments", NULL, NOERROR);
//		else if (dirc == 3)
//			err(av[0], "string not in pwd", av[1], NOERROR);
//		return (-1);
//	}
//	return (0);
//}
//char	*ft_pathjoin(char const *s1, char const *s2)
//{
//	char	*dst;
//	int		i;
//
//	if (!s1 || !s2)
//		return (NULL);
//	i = 0;
//	dst = (char *)ft_memalloc(ft_strlen(s1) + ft_strlen(s2) + 2);
//	if (!dst)
//		return (NULL);
//	while (*s1)
//		dst[i++] = *s1++;
//	if (dst[i] != '/')
//		dst[i++] = '/';
//	while (*s2)
//		dst[i++] = *s2++;
//	return (dst);
//}

void	path_back(void)
{
	int i;

	i = ft_strlen(g_curr_dir) - 1;
	if (i <= 0)
		return ;
	while (g_curr_dir[i] != '/')
		--i;
	ft_bzero(&g_curr_dir[i], ft_strlen(&g_curr_dir[i]));
}

void	path_add(char *tmp)
{
	int len;

	len = ft_strlen(g_curr_dir) - 1;
	if (g_curr_dir[len] != '/')
		g_curr_dir[len + 1] = '/';
	ft_strcat(g_curr_dir, tmp);
}

void	rewrite_global(char **split_path)
{
	char **tmp;

	if (!split_path)
		err_exit(g_argv[0], "malloc() error", NULL, NOERROR);
	tmp = split_path;
	while (*split_path)
	{
		if (!ft_strcmp(*split_path, "."))
		{
			split_path++;
			continue ;
		}
		else if (!ft_strcmp(*split_path, ".."))
			path_back();
		else
			path_add(*split_path);
		split_path++;
	}
	ft_free_dar(tmp);
}

void	remove_slashes(void)
{
	char **tmp;
	int i;

	i = -1;
	if ((tmp = ft_strsplit(g_curr_dir, '/')) == 0)
		err_exit(g_argv[0], "malloc() error", NULL, NOERROR);
	ft_bzero(g_curr_dir, ft_strlen(g_curr_dir));
	*g_curr_dir = '/';
	while (tmp[++i])
		path_add(tmp[i]);
	ft_free_dar(tmp);
}

void	rewrite(char *path, t_cdf flags)
{
	ft_setenv("OLDPWD", ft_getenv("PWD", g_env.env));
	if (flags.P)
	{
		free(g_curr_dir);
		getwd(g_curr_dir);
	}
	if (*path == '/')
	{
		ft_bzero(g_curr_dir, ft_strlen(g_curr_dir));
		ft_memcpy(g_curr_dir, path, ft_strlen(path));
		remove_slashes();
	}
	else
		rewrite_global(ft_strsplit(path, '/'));
	ft_setenv("PWD", g_curr_dir);
}

void cd(char **av)
{
	char 	**dir;
	t_cdf	flags;
	char	*path;

	if (!(dir = check_flags(av, &flags)))
	{
		ft_error("42sh", av[0], CD_USAGE, "invalid option\n");
		return;
	}
	if (!*dir || !ft_strcmp(*dir, "--"))
		path = ft_getenv("HOME", g_env.env);
	else if (!ft_strcmp(*dir, "-"))
		path = ft_getenv("OLDPWD", g_env.env);
	else
		path = (*dir);
	if ((chdir(path)) < 0)
		check_request(av, path);
	else
		rewrite(path, flags);
}

//int		check_args(char **arg, int *p)
//{
//	int	i;
//
//	i = 0;
//	if (!arg[1])
//		return (0);
//	while (arg[1][++i])
//	{
//		if (arg[1][i] == 'P')
//			*p = 1;
//		if (arg[1][i] == 'L')
//			*p = 0;
//		else
//		{
//			ft_putstr_fd("pwd: bad option: -", STDERR_FILENO);
//			ft_putchar_fd(arg[1][i], STDERR_FILENO);
//		}
//	}
//	return (0);
//}
//
void	pwd(char **av)
{
	char 	*dir;
	t_cdf	flags;

	dir = 0;
	if (!check_flags(av, &flags))
		ft_error("42sh", av[0], PWD_USAGE, NULL);
	if (!flags.P)
		getwd(dir);
	else
		dir = ft_strdup(g_curr_dir);
	ft_putstr_fd(dir, STDOUT_FILENO);
	free(dir);
}