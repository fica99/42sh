/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:02:53 by filip             #+#    #+#             */
/*   Updated: 2019/04/27 15:41:33 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			print_symb(char *c, char *buf, short len)
{
	short	i;

	buf = ft_stradd(buf, c, len);
	CLEAN_SCREEN(STDIN_FILENO);
	ft_putstr_cord(buf + len);
	i = ft_strlen(buf + len);
	go_left(i - 1);
}

char	*ft_strdel_el(char	*buf, size_t i)
{
	char	*str;

	if (i >= ft_strlen(buf))
		return (buf);
	str = NULL;
	if (buf + i + 1)
	{
		if (!(str = ft_strdup(buf + i + 1)))
		{
			ft_putchar_fd('\n', STDERR_FILENO);
			reset_input_mode();
			print_error("minishell", "malloc() error", NULL, ENOMEM);
		}
	}
	*(buf + i) = '\0';
	buf = ft_strcat(buf, str);
	ft_memdel((void**)&str);
	return (buf);
}

char	*ft_stradd(char	*buf, char *s, size_t i)
{
	char	*str;

	if (i >= ft_strlen(buf))
		return (ft_strcat(buf, s));
	if (!(str = ft_strdup(buf + i)))
	{
		ft_putchar_fd('\n', STDERR_FILENO);
		reset_input_mode();
		print_error("minishell", "malloc() error", NULL, ENOMEM);
	}
	*(buf + i) = '\0';
	buf = ft_strcat(ft_strcat(buf, s), str);
	ft_memdel((void**)&str);
	return (buf);
}

pid_t	make_process(void)
{
	pid_t	p;

	p = fork();
	if (p < 0)
		print_error("minishell", "fork() error", NULL, 0);
	return (p);
}

void	ft_setenv(char *name, char *new_value)
{
	short	j;
	char	**envp;

	if ((j = get_count_var(name)) >= 0)
	{
		free(g_term.env_cp[j]);
		g_term.env_cp[j]= join_env(name, new_value);
	}
	else
	{
		if (!(envp = (char**)malloc(sizeof(char*) * (double_arr_len(g_term.env_cp) + 2))))
			print_error("minishell", "malloc() error", NULL, ENOMEM);
		while(g_term.env_cp[++j])
			envp[j] = g_term.env_cp[j];
		envp[j] = join_env(name, new_value);
		envp[++j] = NULL;
		free(g_term.env_cp);
		g_term.env_cp = envp;
	}
}