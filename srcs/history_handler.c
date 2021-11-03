/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 20:18:37 by ogenser           #+#    #+#             */
/*   Updated: 2021/11/03 20:18:39 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_add_history(t_mother *s)
{
	if (s->line != NULL)
		add_history(s->line);
}

void	ft_clear_history(void)
{
	clear_history();
}
