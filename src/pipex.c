/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 19:31:11 by skharjo           #+#    #+#             */
/*   Updated: 2021/10/20 19:33:37 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_cmd(char **cmd, char **env)
{
	check_cmd(cmd, env);
	execve(cmd[0], cmd, env);
	msh_strerror_arg_2("pipex", cmd[0]);
	exit(EXIT_FAILURE);
}

void	first_step(int *pipefd, char **av, char **env, int fd)
{
	int		res;
	char	**cmd;
	pid_t	pid;

	cmd = ft_split(av[2], ' ');
	if (fd < 0)
	{
		msh_strerror_arg_2("pipex", av[1]);
		exit(EXIT_FAILURE);
	}
	res = dup2(pipefd[1], 1);
	if (res < 0)
		fatal(res);
	close(pipefd[1]);
	res = dup2(fd, 0);
	if (res < 0)
		fatal(res);
	close(fd);
	pid = fork();
	if (pid < 0)
		fatal((int)pid);
	if (pid == 0)
		exec_cmd(cmd, env);
	waitpid(-1, &res, 0);
	str_array_free(&cmd);
}

void	second_step(char **av, char **env, int *pipefd, int fd)
{
	int		res;
	char	**cmd;
	pid_t	pid;

	cmd = ft_split(av[3], ' ');
	if (fd < 0)
	{
		msh_strerror_arg_2("pipex", av[4]);
		exit(EXIT_FAILURE);
	}
	res = dup2(pipefd[0], 0);
	if (res < 0)
		fatal(res);
	close(pipefd[0]);
	res = dup2(fd, 1);
	if (res < 0)
		fatal(res);
	close(fd);
	pid = fork();
	if (pid < 0)
		fatal((int)pid);
	if (pid == 0)
		exec_cmd(cmd, env);
	waitpid(-1, &res, 0);	
	str_array_free(&cmd);
}

int	main(int arc, char *av[], char *env[])
{
	int		pipefd[2];
	int		i;
	int		fd1;
	int		fd2;

	i = 1;
	if (arc != 5)
		return (0);
	fd1 = open(av[1], O_RDWR);
	fd2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipe(pipefd) < 0)
		fatal(1);
	first_step(pipefd, av, env, fd1);
	second_step(av, env, pipefd, fd2);
	close(pipefd[1]);
	close(pipefd[0]);
	return (0);
}
