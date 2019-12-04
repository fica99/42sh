/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 19:40:55 by aashara-          #+#    #+#             */
/*   Updated: 2019/12/04 19:40:56 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	fc_flag_l(int flags, char *first, char *last)
{
	int		first_i;
	int		last_i;
	char	*copy;
	char	*elem;

	if ((first_i = ft_atoi((!first) ? "-16" : first)) <= 0)
		first_i += get_hist_size();
	if ((last_i = ft_atoi((!last) ? "-1" : last)) <= 0)
		last_i += get_hist_size();
	if (flags & FC_FLAG_R)
		ft_swap(&first_i, &last_i);
	while (first_i != last_i)
	{
		(first_i > last_i) ? (copy = ft_itoa(first_i--)) :
		(copy = ft_itoa(first_i++));
		fc_print_command(flags, copy, elem = get_hist_expansions(copy));
		ft_strdel(&copy);
		ft_strdel(&elem);
	}
	copy = ft_itoa(first_i);
	fc_print_command(flags, copy, elem = get_hist_expansions(copy));
	ft_strdel(&copy);
	ft_strdel(&elem);
}

void	fc_print_command(int flags, char *nb, char *elem)
{
	if (!elem)
		return ;
	if (flags & FC_FLAG_N)
		ft_putstr("\t");
	else
		ft_putstr(nb);
	ft_putstr("\t");
	ft_putendl(elem);
}
