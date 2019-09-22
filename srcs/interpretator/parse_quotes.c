/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 23:33:07 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/22 16:07:57 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char	**parse_quotes(char *buff)
{
	char	**args;
	int		i;

	if (!(args = ft_darnew(ft_strlen(buff))))
		err_exit(g_argv[0], "malloc() error", NULL, ENOMEM);
	i = 0;
	while (*buff)
	{
		if (*buff == '\'')
			args[i++] = remove_quotes(&buff);
		else if (*buff == '\"')
			args[i++] = remove_dquotes(&buff);
		else if (*buff != ' ')
			args[i++] = fill_quotes_buff(&buff);
		else
			buff++;
	}
	return (args);
}

char	*fill_quotes_buff(char **buff)
{
	int		j;
	char	*str;
	char	*copy;

	j = 0;
	copy = *buff;
	if (!(str = ft_strnew(ft_strlen(copy))))
		err_exit(g_argv[0], "malloc() error", NULL, ENOMEM);
	while (*copy && *copy != ' ' && *copy != '\'' && *copy != '\"')
		str[j++] = *(copy++);
	*buff = copy;
	return (spec_symbols(str));
}

char	*remove_quotes(char **buff)
{
	char	*str;
	char	*new;
	int		i;

	str = *buff;
	if (!(new = ft_strnew(ft_strlen(*buff))))
		err_exit(g_argv[0], "malloc() error", NULL, ENOMEM);
	i = 0;
	while (*(++str))
	{
		if (*str == '\'')
			break ;
		new[i++] = *str;
	}
	if (*str == '\'')
		str++;
	*buff = str;
	return (new);
}

char	*remove_dquotes(char **buff)
{
	char	*str;
	char	*new;
	int		i;

	str = *buff;
	if (!(new = ft_strnew(ft_strlen(*buff))))
		err_exit(g_argv[0], "malloc() error", NULL, ENOMEM);
	i = 0;
	while (*(++str))
	{
		if (*str == '\"')
			break ;
		new[i++] = *str;
	}
	if (*str == '\"')
		str++;
	*buff = str;
	return (spec_symbols(new));
}
