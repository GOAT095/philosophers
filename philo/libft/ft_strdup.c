/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anassif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 15:02:58 by anassif           #+#    #+#             */
/*   Updated: 2019/10/11 15:03:01 by anassif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*r;
	int		i;

	i = ft_strlen((char *)s1);
	r = malloc(sizeof(*s1) * (i + 1));
	if (r == NULL)
		return (NULL);
	ft_strlcpy(r, s1, i + 1);
	return (r);
}
