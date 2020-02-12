/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_history_exp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 21:33:13 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/13 00:04:56 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

static size_t	lex_gstrlen(const char *s1, const char *s2)
{
	size_t		len;

	len = ft_strlen(s1);
	len += ft_strlen(s2);
	return (len);
}

int				lex_is_hist_exp(const char *str, size_t pos)
{
	if (str[pos] != '!')
		return (0);
	if (pos > 0 && (str[pos - 1] == '[' || str[pos - 1] == '{'))
		return (0);
	pos++;
	if (str[pos] == '!')
		return (++pos);
	if (str[pos] == '-')
		pos++;
	if (ft_isdigit(str[pos]))
	{
		while (ft_isdigit(str[pos]))
			pos++;
		return (pos);
	}
	while (ft_isalnum(str[pos]))
		pos++;
	if (str[pos - 1] != '!')
		return (pos);
	return (0);
}

static char		*lex_add_hist_to_str(char *str, char *hist_str,
	size_t ins_index)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	if (!str || !hist_str)
		return (NULL);
	if (!(new_str = ft_strnew(lex_gstrlen(str, hist_str))))
		return (NULL);
	i = 0;
	j = 0;
	while (i < ins_index)
		new_str[j++] = str[i++];
	i = 0;
	while (hist_str[i])
		new_str[j++] = hist_str[i++];
	if (!(i = lex_is_hist_exp(str, ins_index)))
		return (NULL);
	while (str[i])
		new_str[j++] = str[i++];
	new_str[j] = '\0';
	free(str);
	free(hist_str);
	return (new_str);
}

static char		*lex_he_cut_n_w(const char *str, size_t pos)
{
	size_t		start;
	size_t		end;
	char		*new_str;

	if (!str)
		return (NULL);
	start = pos;
	if (str[pos] != '!')
		return (NULL);
	if (pos > 0 && (str[pos - 1] == '['
		|| str[pos - 1] == '['))
		return (NULL);
	pos++;
	if (str[pos] == '-')
		pos++;
	if (!(end = lex_is_hist_exp(str, start)))
		return (NULL);
	start = pos;
	if (!(new_str = ft_strsub(str, start, end - start)))
		return (NULL);
	return (new_str);
}

int				lex_history_exp(char **str, size_t pos)
{
	char		*temp;
	char		*hist_str;

	if (!str || !*str)
		return (0);
	if (!(temp = lex_he_cut_n_w(*str, pos)))
		return (0);
	if (!(hist_str = get_hist_expansions(temp)))
		return (0);
	free(temp);
	if (!(temp = lex_add_hist_to_str(*str, hist_str, pos)))
		return (0);
	*str = temp;
	return (1);
}
