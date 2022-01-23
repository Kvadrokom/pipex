/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 20:43:25 by skharjo           #+#    #+#             */
/*   Updated: 2021/10/19 17:33:59 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*get_path(char *path)
{
	int	i;

	i = 0;
	while (path[i] != '=')
		i++;
	return (ft_substr(&path[i + 1], 0, ft_strlen(&path[i + 1])));
}

char	*ft_getenv(char *path, char **env)
{
	char	*tmp;

	tmp = NULL;
	while (*env)
	{
		if (!ft_strncmp(path, *env, ft_strlen(path)))
		{
			tmp = *env;
			break ;
		}
		env++;
	}
	if (tmp)
		return (get_path(tmp));
	return (NULL);
}

char	**split_path(char *path, char **env)
{
	char	**splitpath;
	char	*tmp;

	tmp = ft_getenv(path, env);
	if (!tmp)
		return (NULL);
	splitpath = ft_split(tmp, ':');
	if (!splitpath)
		fatal(1);
	return (splitpath);
}

void	check_cmd(char **cmd, char **env)
{
	char	**arr;
	char	*str;
	char	*tmp;

	arr = split_path("PATH", env);
	if (!arr)
		return ;
	while (*arr)
	{
		str = ft_strjoin(*arr, "/");
		if (!str)
			fatal(1);
		tmp = str;
		str = ft_strjoin(tmp, *cmd);
		if (!str)
			fatal(1);
		free(tmp);
		if (!access(str, 0))
		{
			*cmd = str;
			return ;
		}	
		arr++;
		free(str);
	}
}
