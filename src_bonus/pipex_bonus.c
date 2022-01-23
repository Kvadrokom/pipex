/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 19:31:11 by skharjo           #+#    #+#             */
/*   Updated: 2021/10/17 20:04:55 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exec_cmd(char **cmd, char **env)
{
	check_cmd(cmd, env);
	execve(cmd[0], cmd, env);
	msh_strerror_arg_2("pipex", cmd[0]);
	exit(EXIT_FAILURE);
}

int	count_arg(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	return (i);
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
	wait(NULL);
	str_array_free(&cmd);
}

void	second_step(char **av, char **env, int *pipefd, int fd)
{
	int		res;
	char	**cmd;
	pid_t	pid;
	int		arc;

	arc = count_arg(av);
	cmd = ft_split(av[arc - 2], ' ');
	if (fd < 0)
		call_msh_error("pipex", av[4]);
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
	wait(NULL);
	str_array_free(&cmd);
}

int	main(int arc, char *av[], char *env[])
{
	int		i;
	t_fd	allfd;

	i = 3;
	if (arc < 5 || (!ft_strcmp(av[1], "here_doc") && arc != 6))
		return (0);
	allfd.fd1 = open(av[1], O_RDWR);
	allfd.fd2 = open(av[arc - 1], O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (pipe(allfd.pipefd) < 0)
		fatal(1);
	if (!ft_strcmp(av[1], "here_doc"))
	{
		heredoc(allfd.pipefd, av, env);
		i = 4;
	}
	else
		first_step(allfd.pipefd, av, env, allfd.fd1);
	while (i < arc - 2)
	{
		middle(allfd.pipefd, av, env, i);
		i++;
	}
	second_step(av, env, allfd.pipefd, allfd.fd2);
	close_all_fd(allfd.pipefd, allfd.fd1, allfd.fd2);
	return (0);
}
