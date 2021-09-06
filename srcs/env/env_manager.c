/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsacquin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 16:49:10 by fsacquin          #+#    #+#             */
/*   Updated: 2021/09/02 16:49:12 by fsacquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../inc/minishell.h"

void	env_init(t_mother *s, char **envp)
{
	char	*temp;
	int		i;
	int		len;

	len = ft_strlen_array(envp);
	s->env = malloc((len + 1) * sizeof(char *));
	i = 0;
	while (i < len)
	{
		s->env[i] = ft_strdup(envp[i]);
		i++;
	}
	s->env[i] = NULL;
}

//Ajout d'une variable d'environement a env en regardant si la variable existe deja
void	create_env(t_mother *s, char *str)
{
	int		i;
	int		len;
	int		pos;

	i = 0;
	len = ft_strlen_array(s->env);
	pos = -1;
	while (i < len)
	{
		if (ft_env_cmp(s->env[i], str) == 1)
			pos = i;
		i++;
	}
	if (pos == -1)
		add_env(s, str);
	else
		change_env(s, str, pos);
}

void	change_env(t_mother *s, char *str, int pos)
{
	char **temp;
	int		i;
	int		len;
	
	len = ft_strlen_array(s->env);
	temp = ft_malloc(&temp, (len + 1) * sizeof(char *));
	i = 0;
	while (i < len)
	{
		if (i = pos)
			temp[i] = strdup(str);
		else
			temp[i] = strdup(s->env[i]);
		i++;
	}
	temp[i] = NULL;
	ft_free_array(s->env);
	s->env = temp;
}

// permet d'ajouter une varaible str a la liste des env
void	add_env(t_mother *s, char *str)
{
	char **temp;
	int		i;
	int		len;
	
	len = ft_strlen_array(s->env);
	temp = ft_malloc(&temp, (len + 2) * sizeof(char *));
	i = 0;
	while (i < len)
	{
		temp[i] = strdup(s->env[i]);
		i++;
	}
	temp[i++] = ft_strdup(str);
	temp[i] = NULL;
	ft_free_array(s->env);
	s->env = temp;
}

// permet de retirer une variable str a la liste des env en comparant str avec la liste des varaibles existentes
void	rm_env(t_mother *s, char *str)
{
	char	**temp;
	int		i;
	int		len;

	len = ft_strlen_array(s->env);
	temp = ft_malloc(&temp, len * sizeof(char *));
	i = 0;
	while (i < len)
	{
		if (!(ft_env_cmp(s->env[i], str)))
			temp[i] = strdup(s->env[i]);
		i++;
	}
	temp[i] = NULL;
	ft_free_array(s->env);
	s->env = temp;
}
