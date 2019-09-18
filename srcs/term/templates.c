/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   templates.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 19:03:09 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/18 19:36:24 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

t_temp	*init_templates(void)
{
	if (TRANSMIT_MODE == (char*)-1 || CUR_CORD == (char*)-1 ||
	K_LFT == (char*)-1 || K_HOME == (char*)-1 ||
	K_RGHT == (char*)-1 || K_END == (char*)-1 || SET_CUR == (char*)-1 ||
	SAVE_CUR == (char*)-1 || RESTORE_CUR == (char*)-1 ||
	CLEAR_END_SCREEN == (char*)-1 || CLEAR_SCREEN == (char*)-1 ||
	K_DEL == (char*)-1 || K_UP == (char*)-1 || K_DOWN != (char*)-1 ||
	SHIFT_LFT == (char*)-1 || SHIFT_RGHT == (char*)-1 ||
	STOP_TRANSMIT_MODE == (char*)-1 || !TRANSMIT_MODE || !CUR_CORD ||
	! K_LFT|| !K_HOME || !K_RGHT || !K_END || !SET_CUR || !SAVE_CUR ||
	!RESTORE_CUR || !CLEAR_END_SCREEN || !CLEAR_SCREEN || !K_DEL ||
	!K_UP || !K_DOWN || !SHIFT_LFT || !SHIFT_RGHT || !STOP_TRANSMIT_MODE)
		err_exit("42sh", "no correct capabilities", NULL, NOERROR);
	return (set_templates());
}

t_temp	*init_temp_struct(char *template, void (*handler)())
{
	t_temp	*temp;

	if (!(temp = (t_temp*)malloc(sizeof(t_temp))))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	temp->template = template;
	temp->handler = handler;
	temp->next = NULL;
	return (temp);
}

void	free_templates(t_temp **head)
{
	t_temp	*copy;
	t_temp	*temp;

	temp = *head;
	while (temp)
	{
		copy = temp;
		ft_memdel((void**)&copy->template);
		temp = temp->next;
		ft_memdel((void**)&copy);
	}
	*head = NULL;
}
