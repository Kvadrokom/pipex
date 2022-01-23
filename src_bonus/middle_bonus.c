/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   middle_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 20:18:16 by skharjo           #+#    #+#             */
/*   Updated: 2021/10/17 19:56:12 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	middle(int *pipefd, char **av, char **env, int i)
{
	int		fd[2];
	int		res;
	char	**cmd;
	pid_t	pid;

	cmd = ft_split(av[i], ' ');
	res = dup2(pipefd[0], 0);
	if (res < 0)
		fatal(res);
	close(pipefd[0]);
	if (pipe(fd) < 0)
		fatal(1);
	res = dup2(fd[1], 1);
	if (res < 0)
		fatal(res);
	close(fd[1]);
	pid = fork();
	if (pid < 0)
		fatal((int)pid);
	if (pid == 0)
		exec_cmd(cmd, env);
	wait(NULL);
	pipefd[0] = fd[0];
	pipefd[1] = fd[1];
	str_array_free(&cmd);
}
