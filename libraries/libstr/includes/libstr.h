/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libstr.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 00:14:35 by ggrimes           #+#    #+#             */
/*   Updated: 2019/11/15 23:39:51 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBSTR_H
# define LIBSTR_H

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

size_t	ft_get_cnt_words(const char *str, char *spr);
char	*ft_last_word_pos(const char *str, char *seps);
int		ft_is_str_contain(char *str, char sym);
char	*ft_del_sym_str(char *str, char *delsym);
int		ft_match(char *s1, char *s2);
size_t	ft_num_match(char **str, char *arg);
char	*ft_strdup_realloc(char *str, short len);
char	*ft_strdel_el(char *buf, int i);
char	*ft_stradd(char *buf, char *s, size_t i);

#endif
