/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_prompt_time.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:56:37 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/11 16:22:19 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

short	rl_prompt_time(char *str, short i)
{
	time_t		t;
	short		j;
	struct tm	*info;

	time(&t);
	if (t == -1)
		rl_err("42sh", "time() error", UNDEFERR);
	info = localtime(&t);
	if ((j = rl_check_time_flags(str, i, info)) != i)
		return (j);
	return (i);
}

short	rl_check_time_flags(char *str, short i, struct tm *info)
{
	char	buffer[RL_MAX_BUFF];

	buffer[0] = '\0';
	if (!ft_strncmp(str + i, "\\A", 2))
		strftime(buffer, RL_MAX_BUFF, "%H:%M", info);
	else if (!ft_strncmp(str + i, "\\t", 2))
		strftime(buffer, RL_MAX_BUFF, "%H:%M:%S", info);
	else if (!ft_strncmp(str + i, "\\T", 2))
		strftime(buffer, RL_MAX_BUFF, "%I:%M:%S", info);
	else if (!ft_strncmp(str + i, "\\@", 2))
		strftime(buffer, RL_MAX_BUFF, "%I:%M %p", info);
	else if (!ft_strncmp(str + i, "\\d", 2))
		strftime(buffer, RL_MAX_BUFF, "%a %b %d", info);
	else if (!ft_strncmp(str + i, "\\D{", 3))
		i = rl_time_format_flag(str, i, info);
	else
		--i;
	ft_putstr(buffer);
	return (++i);
}

short	rl_time_format_flag(char *str, short i, struct tm *info)
{
	char	buffer[RL_MAX_BUFF];
	char	format[RL_MAX_BUFF];
	short	j;

	str = ft_strchr(str + i, '{') + 1;
	j = 0;
	while (*(str + j) != '\0' && *(str + j) != '}')
	{
		format[j] = *(str + j);
		j++;
	}
	format[j] = '\0';
	strftime(buffer, RL_MAX_BUFF, format, info);
	ft_putstr(buffer);
	i += (j + RL_PROMPT_TIME_BRACKETS);
	return (i);
}
