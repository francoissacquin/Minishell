/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chainedlists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 14:27:52 by ogenser           #+#    #+#             */
/*   Updated: 2021/08/19 15:48:07 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*listinit(void)
{
	t_list		*l;
	t_element	*element;

	l = NULL;
	element = NULL;
	l = ft_malloc(l, sizeof(*l));
	element = ft_malloc(element, sizeof(*element));
	if (l == NULL || element == NULL)
		write(1, "malloc failed\n", 14);
	element->nb = 0;
	element->next = NULL;
	element->previous = NULL;
	l->first = element;
	l->lenght = 0;
	return (l);
}

void	addelement(t_list *l, int nb)
{
	t_element	*new;

	new = NULL;
	new = ft_malloc(new, sizeof(*new));
	if (new == NULL || !(l))
		write(1, "list failed\n", 13);
	new->next = l->first;
	new->previous = NULL;
	new->nb = nb;
	l->first = new;
	l->lenght++;
}

void	addelementend(t_list *l, int nb)
{
	t_element	*new;
	t_element	*tmp;

	new = NULL;
	new = ft_malloc(new, sizeof(*new));
	tmp = NULL;
	if (!(l) || new == NULL)
		write(1, "list failed\n", 13);
	tmp = l->first;
	while (l->first->next != NULL)
	{
		l->first = l->first->next;
	}
	l->first->nb = nb;
	new->next = NULL;
	new->nb = 0;
	l->first->next = new;
	l->first = tmp;
	l->lenght++;
}

/*
void	listdisplay(t_list *l)
{
	t_element	*current;

	if (l == NULL)
		write(1, "list failed\n", 12);
	current = l->first;
	while (current != NULL)
	{
		printf("%d->", current->nb);
		current = current->next;
	}
	printf("\n");
}

void	listdisplayreverse(t_list *l)
{
	t_element	*current;

	if (l == NULL)
		write(1, "list failed\n", 12);
	current = NULL;
	while (current != NULL)
	{
		printf("%d->", current->nb);
		current = current->previous;
	}
	printf("\n");
}*/
