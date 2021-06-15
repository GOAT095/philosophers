/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anassif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 19:01:13 by anassif           #+#    #+#             */
/*   Updated: 2019/10/11 19:01:15 by anassif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	find_left(char const *s1, char const *set)
{
	int found1;
	int i;

	found1 = -1;
	i = 0;
	while (s1[i] != '\0' && found1 == -1)
	{
		if (ft_strchr(set, s1[i]) == NULL)
		{
			found1 = i;
		}
		i++;
	}
	if (found1 == -1)
		return (0);
	return (found1);
}

static	int	find_right(char const *s1, char const *set, int found1)
{
	int	found2;
	int	len;

	found2 = -1;
	len = ft_strlen((char *)s1);
	while (len > found1 && found2 == -1)
	{
		if (ft_strchr(set, s1[len - 1]) == NULL)
		{
			found2 = len;
		}
		len--;
	}
	if (found1 == -1)
		return (0);
	return (found2);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	int		found1;
	int		found2;
	int		i;
	int		size;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	found1 = find_left(s1, set);
	found2 = find_right(s1, set, found1);
	size = found2 - found1;
	str = (char *)malloc(sizeof(char) * size + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		str[i] = s1[found1];
		i++;
		found1++;
	}
	str[i] = '\0';
	return (str);
}
