/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anassif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 10:47:06 by anassif           #+#    #+#             */
/*   Updated: 2019/10/10 10:47:08 by anassif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	x;
	size_t			i;

	str = (unsigned char *)s;
	x = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (str[i] == x)
			return ((void *)&str[i]);
		i++;
	}
	if (c == '\0')
		return ((void *)&str[i]);
	return (0);
}
