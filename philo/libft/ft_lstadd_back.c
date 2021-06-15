/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anassif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 23:06:52 by anassif           #+#    #+#             */
/*   Updated: 2019/10/17 23:06:54 by anassif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *x;

	if (!*alst)
	{
		*alst = new;
		return ;
	}
	x = *alst;
	while (x->next != NULL)
		x = x->next;
	x->next = new;
}
