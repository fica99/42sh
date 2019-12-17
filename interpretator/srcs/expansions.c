/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijerde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 06:05:14 by jijerde           #+#    #+#             */
/*   Updated: 2019/12/11 15:02:49 by jijerde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

// int		check_bracket(char *s)
// {
// 	int i;

// 	i = 0;
// 	if (s[i++] == '}')
// 		return (0);
// 	while (s[i])
// 	{
// 		if (s[i] == '}')
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// void	*expansions(char *s)
// {
// 	//if we see $ character, and the next is {, we go here with pointer
// 	//after {. And we sure for } at the end.
// 	int		i;
// 	char	var[100];

// 	ft_bzero(var, 100);
// 	i = 0;
// 	if (s[i] == '#')
// 		return ((int *)ft_strlen(sh_getenv(s + i)));
// 	while (s[i] != '}' && s[i] != ':' && s[i] != '%' && s[i] != '#')
// 	{
// 		var[i] = s[i];
// 		i++;
// 	}
// 	return (0);
// }

char *ft_stricut(char *str, int i)
{
	if (!str || !*str)
		return (0);
	if (i > (int)ft_strlen(str) - 1)
		return (str);
	str += i;
	while (*++str)
		*(str - 1) = *str;
	*(str - 1) = 0;
	return (str);
}

char *get_var_name(char *str, int start)
{
	static char delim[2] = {'$', '/'};
	int end;
	char *res;
	int namelen;
	
	end = start;
	if (!str[start])
		return(NULL);
	while (str[++end])
	{
		if (ft_strchr(delim, str[end]))
			break;
	}
	res = ft_strsub(str, start, end - start);
	namelen = ft_strlen(res);
	while (namelen--)
		ft_stricut(str, start);
	return (res);
}

char *var_substitution(char *str, int ind)
{
	char *varname;
	int i;
	char *new;
	char *value;

	i = 0;
	if (!(varname = get_var_name(str, ind)))
		return (NULL);
	if (!(value = get_env(varname + 1, ALL_ENV)))
		value = "";
	if (!(new = (char *)ft_memalloc(ft_strlen(str) + ft_strlen(value) + 1)))
		err_exit("42sh", "malloc() error", NULL, NOERROR);
	while (ind)
	{
		new[i] = str[i];
		i++;
		ind--;
	}
	ft_strcat(new, value);
	ft_strcat(new, &str[i]);
	free(str);
	free(varname);
	str = NULL;
	return(new);
}	

char *tilda_substitution(char *str)
{
	char *value;
	char *new;

	if (!(value = get_env("HOME", ALL_ENV)))
		value = "";
	if (!(new = (char *)ft_memalloc(ft_strlen(value) + ft_strlen(str))))
		err_exit("42sh", "malloc() error", NULL, NOERROR);
	ft_stricut(str, 0);
	ft_strcat(new, value);
	ft_strcat(new, str);
	free(str);
	return(new);
}

char *substitution(char *str)
{
	char *tmp;

	if (*str == '~' && *(str + 1) != '~')
		str = tilda_substitution(str);
	while ((tmp = ft_strchr(str, '$')))
		str = var_substitution(str, tmp - str);
	return (str);
}