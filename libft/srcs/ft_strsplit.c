/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 12:25:02 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/02 22:50:14 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_count_words(const char *str, char c)
{
	int	word;
	int	i;

	i = 0;
	word = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c && str[i + 1] != c)
			word++;
		i++;
	}
	if (str[0] != '\0')
		word++;
	return (word);
}

static void		free_mem(char **str, int i)
{
	while (i != -1)
	{
		free(str[i]);
		i--;
	}
}

static	char	*ft_word(char **s1, const char *str, char c, int *i)
{
	char	*s;
	int		k;

	if (!(s = (char *)malloc(sizeof(s) * (ft_strlen(str)))))
	{
		free_mem(s1, *i);
		return (NULL);
	}
	k = 0;
	while (str[*i] != c && str[*i])
	{
		s[k] = str[*i];
		k++;
		*i += 1;
	}
	s[k] = '\0';
	while (str[*i] == c && str[*i])
		*i += 1;
	return (s);
}

char			**ft_strsplit(char const *str, char c)
{
	int		i;
	int		j;
	char	**s;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	if (!(s = (char **)malloc(sizeof(s) * (ft_count_words(str, c) + 2))))
		return (NULL);
	while (str[i] == c && str[i])
		i++;
	while (j < ft_count_words(str, c) && str[i])
	{
		s[j] = ft_word(s, (char*)str, c, &i);
		if (s[j] == NULL)
		{
			free(s);
			return (NULL);
		}
		j++;
	}
	s[j] = NULL;
	return (s);
}
