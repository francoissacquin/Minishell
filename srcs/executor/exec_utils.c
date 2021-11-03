/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 20:21:15 by ogenser           #+#    #+#             */
/*   Updated: 2021/11/03 20:21:17 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_fileexits(char *testpath)
{
	struct stat	s_buf;
	int			ret;

	ret = -1;
	if (stat(testpath, &s_buf) == 0)
		ret = 0;
	return (ret);
}

// index table for the 4 correcponding variables
// yes I know it's ugly, I don't make the rules, go check the norm
// idx[0] => i;
// idx[1] => j;
// idx[2] => pathsize;
// idx[3] => pathfound;
char	*ft_pathtester(t_command *c, char ***minipath, int minisize)
{
	int			*idx;
	char		*tpath;
	char		*addcmd;

	idx = ft_path_idx_init();
	while (idx[0] < minisize && idx[3] == -1)
	{
		idx[2] = ft_strlen_array(minipath[idx[0]]);
		tpath = ft_strjoin("", "/");
		idx[1] = 0;
		while (idx[1] < idx[2] && idx[3] == -1)
		{
			addcmd = ft_path_sub(c, minipath[idx[0]][idx[1]], &tpath, &idx[3]);
			idx[1] = idx[1] + 1;
			if (idx[1] < idx[2] && idx[3] == -1)
				free(addcmd);
		}
		free(tpath);
		idx[0] = idx[0] + 1;
		if (idx[0] < minisize && idx[3] == -1)
			free(addcmd);
		idx[2] = 0;
	}
	free(idx);
	return (addcmd);
}

int	*ft_path_idx_init(void)
{
	int		*idx;

	idx = ft_malloc(&idx, 4 * sizeof(int));
	idx[3] = -1;
	idx[2] = 0;
	idx[0] = 0;
	return (idx);
}

char	*ft_path_sub(t_command *c, char *str, char **testpath, int *pathfound)
{
	char	*testpath2;
	char	*addcmd;

	testpath2 = ft_strjoin(*testpath, str);
	free(*testpath);
	*testpath = ft_strjoin(testpath2, "/");
	free(testpath2);
	addcmd = ft_strjoin(*testpath, c->command);
	if (ft_fileexits(addcmd) == 0)
		*pathfound = 1;
	return (addcmd);
}
