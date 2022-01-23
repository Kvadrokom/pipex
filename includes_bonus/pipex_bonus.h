/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 19:31:02 by skharjo           #+#    #+#             */
/*   Updated: 2021/10/17 20:04:01 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>

typedef struct s_fd
{
	int		pipefd[2];
	int		fd1;
	int		fd2;
}				t_fd;

size_t	ft_strlen(const char *str);
void	msh_strerror_arg_2(char *arg_1, char *arg_2);
int		ft_putstr_fd(const char *s, int fd);
void	fatal(int res);
char	**ft_split(char const *s, char c);
char	**str_array_free(char **str_array[]);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	check_cmd(char **cmd, char **env);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
void	middle(int *pipefd, char **av, char **env, int i);
void	exec_cmd(char **cmd, char **env);
int		get_next_line(int fd, char **line);
char	*ft_strdup(const char *str);
void	heredoc(int *pipefd, char **av, char **env);
void	close_all_fd(int *pipefd, int fd1, int fd2);
void	call_msh_error(char *str1, char *str2);

#endif