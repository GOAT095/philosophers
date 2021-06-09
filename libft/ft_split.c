/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anassif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 17:14:39 by anassif           #+#    #+#             */
/*   Updated: 2019/10/12 17:14:40 by anassif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	countt(char *s, char c)
{
	int i;
	int w;

	i = 0;
	w = 0;
	while (1)
	{
		if ((s[i] == c && i != 0 && s[i - 1] != c)
			|| (s[i] == '\0' && i > 0 && s[i - 1] != c))
			w++;
		if (s[i] == '\0')
			break ;
		i++;
	}
	return (w);
}

static char	**ft_free(char **s, int j)
{
	while (j)
	{
		free(s[j--]);
	}
	free(s);
	return (NULL);
}

char		**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	d;
	char	**str;

	if (!s)
		return (NULL);
	if (!(str = (char **)malloc(sizeof(char *) * (countt((char *)s, c) + 1))))
		return (NULL);
	i = 0;
	d = 0;
	j = 0;
	while (2)
	{
		if (((s[i] == c && i != 0) || (s[i] == '\0' && i > 0)) && s[i - 1] != c)
		{
			if (!(str[j++] = ft_substr((char *)s, d, i - d)))
				return (ft_free(str, j - 1));
		}
		d = (s[i] == c ? i + 1 : d);
		if (s[i++] == '\0')
			break ;
	}
	str[j] = NULL;
	return (str);
}
