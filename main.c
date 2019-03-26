/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:05:12 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/26 11:41:13 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_prompt(void)
{
	char	buf[PROMPT_LEN + 1];
	char	*arr;
	char	*arr1;
	uint8_t	nb;

	arr = NULL;
	while ((nb = read(0, buf, PROMPT_LEN)) > 0)
	{
		buf[nb] = '\0';
		if (!arr)
			arr = ft_strdup(buf);
		else
		{
			arr1 = ft_strjoin(arr, buf);
			ft_memdel((void**)&arr);
			arr = arr1;
		}
		if ((arr1 = check_new_line(arr)) != NULL)
			break;
	}
	parse_string(arr1);
}

int		main(int argc, char **argv, char **environ)
{
	(void)argc;
	(void)argv;
	env_cp = copy_double_arr(environ);
	shell_start();
	free_double_arr(env_cp);
	return (0);
}
