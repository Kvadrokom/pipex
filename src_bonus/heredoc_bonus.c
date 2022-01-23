/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 15:28:02 by skharjo           #+#    #+#             */
/*   Updated: 2021/10/17 19:55:40 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	write_to_heredoc(char *heredoc, int *fd)
{
	int	res;

	res = pipe(fd);
	if (res < 0)
		fatal(1);
	write(fd[1], heredoc, ft_strlen(heredoc));
}

void	exec_heredoc(char *heredoc, char **env, int *pipefd, char **av)
{
	char	**cmd;
	pid_t	pid;
	int		fd[2];

	cmd = ft_split(av[3], '\n');
	write_to_heredoc(heredoc, fd);
	if (!cmd)
		fatal(1);
	if (dup2(pipefd[1], 1) < 0)
		fatal(1);
	if (dup2(fd[0], 0) < 0)
		fatal(1);
	close(pipefd[1]);
	close(fd[0]);
	pid = fork();
	if (pid < 0)
		fatal(1);
	close(fd[1]);
	if (pid == 0)
		exec_cmd(cmd, env);
	wait(NULL);
	free(heredoc);
	str_array_free(&cmd);
}

void	heredoc(int *pipefd, char **av, char **env)
{
	char	*line;
	char	*heredoc;
	char	*tmp;

	heredoc = ft_strdup("");
	while (1)
	{
		write(1, "pipe heredoc> ", ft_strlen("pipe heredoc> "));
		get_next_line(0, &line);
		if (!ft_strcmp(line, av[2]))
		{
			free(line);
			break ;
		}
		tmp = heredoc;
		heredoc = ft_strjoin(heredoc, line);
		free(tmp);
		free(line);
		tmp = heredoc;
		heredoc = ft_strjoin(heredoc, "\n");
		free(tmp);
	}
	exec_heredoc(heredoc, env, pipefd, av);
}
