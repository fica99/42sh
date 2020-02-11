/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_cycle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijerde <jijerde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 21:57:09 by jijerde           #+#    #+#             */
/*   Updated: 2020/02/12 00:02:27 by jijerde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

void	*exp_error(char *s)
{
    err("42sh", s, "operand expected", "syntax error");
    return (NULL);
}

/*void	triple_strcat()
{
	
}*/

//void	

char	*expansions_cycle(char *s)
{
	int		i;
	int		curr_doll;
	char	*for_replace;
	char	*final_s;

	i = 0;
	while (1)
	{
		while (s[i])
		{
			if (s[i] == '$')
				curr_doll = i;
			i++;
		}
		for_replace = expansions_validation(ft_strsub(s, curr_doll, 
		(check_bracket(s) - curr_doll) + 2));
	}
	return (final_s);
}