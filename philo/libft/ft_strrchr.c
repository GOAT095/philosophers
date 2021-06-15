/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anassif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 12:24:30 by anassif           #+#    #+#             */
/*   Updated: 2019/10/11 12:24:32 by anassif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	x;
	int				i;
	int				p;

	x = (unsigned char)c;
	i = 0;
	p = 0;
	while (s[i] != '\0')
	{
		if (s[i] == x)
			p = i;
		i++;
	}
	if (x == '\0')
		return ((char *)&s[i]);
	if (s[p] == x)
		return ((char*)&s[p]);
	return (0);
}
