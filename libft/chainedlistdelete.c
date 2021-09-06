/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chainedlistdelete.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 15:46:17 by ogenser           #+#    #+#             */
/*   Updated: 2021/08/19 15:48:02 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	delelement(t_list *l)
{
	t_element	*todelete;

	if (!(l))
		write(1, "list failed\n", 13);
	if (l->first != NULL && l->lenght > 0)
	{
		todelete = l->first;
		l->first = l->first->next;
		if (todelete != NULL)
			free(todelete);
		todelete = NULL;
	}
	l->lenght--;
}

void	delelementend(t_list *l)
{
	t_element	*todelete;
	t_element	*before;

	if (l->lenght > 0)
	{
		todelete = l->first;
		before = l->first;
		while (todelete->next != NULL )
		{
			before = todelete;
			todelete = todelete->next;
		}
		before->nb = 0;
		before->next = NULL;
		free(todelete);
		todelete = NULL;
		l->lenght--;
	}
}

void	destroylist(t_list *l)
{
	int		i;
	int		size;

	i = 0;
	size = l->lenght;
	while (i <= size)
	{
		delelement(l);
		i++;
	}
	free (l->first);
	free (l);
	l = NULL;
}
