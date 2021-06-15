/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anassif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 19:55:10 by anassif           #+#    #+#             */
/*   Updated: 2019/10/17 19:55:12 by anassif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *p;

	p = malloc(sizeof(t_list));
	if (p == NULL)
		return (NULL);
	p->content = content;
	p->next = NULL;
	return (p);
}

int main()
{
	char str[40];
	strlcpy(str,"testing123456789",40);

	t_list *e1;
	t_list *e2;
	t_list *e3;
	t_list *e4;
	t_list *e5;
	
	//printf("%d",ft_lstsize(e1));
	e1 = ft_lstnew(str);
	e2 = ft_lstnew(str + 3);
	e3 = ft_lstnew(str + 6);
	e4 = ft_lstnew (str + 10);
	e5 = ft_lstnew(str + 1);
	e1->next = e2;
	e2->next = e3;
	e3->next = e4;

	//ft_lstadd_front(&e1,e4);
	//printf("%p",ft_lstlast(e1));
		ft_lstprint(e1);
ft_lstadd_back(&e1,e5);
	ft_lstprint(e1);
}
