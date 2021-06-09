/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anassif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:36:48 by anassif           #+#    #+#             */
/*   Updated: 2019/10/23 15:46:25 by anassif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>
void	*ft_lstprint(t_list *lst)
{
	while(lst)
	{
		printf("%s\n","_________________________________________");
		printf("ADRESS :%p\n",lst);
		printf("CONTENT :%s\n",lst->content);
		printf("ADRESS NEXT :%p\n",lst->next);
		printf("%s", "_________________________________________");
		lst = lst->next;
	}
	printf("\n\n\n");
}		
