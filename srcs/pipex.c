/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:53:40 by ncorrear          #+#    #+#             */
/*   Updated: 2025/11/05 10:23:30orrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/ft_printf.h"
#include "../includes/pipex.h"
#include "../includes/libft.h"

// write nothing if error -> create file anyway
// ls do ls in current folder without considering the in file

// if < file -> cat the file
// if < file command -> command file
// if < file command > file -> output the command in the file
// if file = dir send it without open

// top get multiple pipe -> create while and break it if its the parent
// get the path instead of /usr/bin

void	clear_split(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}

int	file_open_init(char **argv)
{
	int	old_wr_pipe;

	old_wr_pipe = open(argv[1], O_RDONLY);
	if (old_wr_pipe < 0)
	{
		ft_dprintf(2, "pipex: %s: %s", argv[1], strerror(errno));
		old_wr_pipe = open("/dev/null", O_RDONLY);
		if (old_wr_pipe < 0)
		{
			ft_dprintf(2, "pipex: %s: %s", "/dev/null", strerror(errno));
			exit(WEXITSTATUS(old_wr_pipe));
		}
		return (old_wr_pipe);
	}
	return (old_wr_pipe);
}

void	close_all(int fd1, int fd2, int fd3)
{
	close(fd1);
	close(fd2);
	close(fd3);
}

void	wait_all(int argv_i, int argc, int *childs, int *last_err)
{
	while (argv_i >= 2)
	{
		if (argv_i-- == argc - 1)
			waitpid(childs[argv_i], last_err, 0);
		else
			waitpid(childs[argv_i], NULL, 0);
	}
}

// Alloc need to be in the parent and not the child
// int	main(int argc, char **argv, char **envp)
// {
// 	pid_t	childs[1024];
// 	int		pipfd[2];
// 	int		old_wr_pipe;
// 	int		argv_i;
// 	char	**cmd_args;
// 	char	*cmd;
// 	int		last_err;

// 	last_err = 0;
// 	old_wr_pipe = file_open_init(argv);
// 	argv_i = 2;
// 	// PAS BON CAR OPEN REUSSI AVEC /dev/null
// 	if (old_wr_pipe < 0)
// 		argv_i = argc - 2;
// 	while (argv_i < argc - 1)
// 	{
// 		pipe(pipfd);
// 		cmd_args = ft_split(argv[argv_i], ' ');
// 		cmd = get_path_command(cmd_args[0], envp);
// 		childs[argv_i] = fork();
// 		if (childs[argv_i] == 0)
// 		{
// 			dup2(old_wr_pipe, STDIN_FILENO);
// 			if (argv_i == argc - 2)
// 				// leak du open il faut une var temp
// 				dup2(open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644), STDOUT_FILENO);
// 			dup2(pipfd[WR], STDOUT_FILENO);
// 			close_all(pipfd[RD], pipfd[WR], old_wr_pipe);
// 			execve(cmd, cmd_args, envp);
// 			ft_dprintf(2, "pipex: %s: %s", cmd_args[0], strerror(errno));
// 			exit(127);
// 		}
// 		else if (childs[argv_i] < 0)
// 		{
// 			ft_dprintf(2, "pipex: fork: %s", strerror(errno));
// 			clear_split(cmd_args);
// 			free(cmd);
// 			close_all(pipfd[RD], pipfd[WR], old_wr_pipe);
// 			exit(WEXITSTATUS(childs[argv_i]));
// 		}
// 		clear_split(cmd_args);
// 		free(cmd);
// 		close(old_wr_pipe);
// 		old_wr_pipe = pipfd[RD];
// 		close(pipfd[WR]);
// 		argv_i++;
// 	}
// 	close(old_wr_pipe);
// 	wait_all(argv_i, argc, childs, &last_err);
// 	exit(WEXITSTATUS(last_err));
// }

// TODO: SEGV -> WHEEEEERE
int	main(int argc, char **argv, char **envp)
{
	pid_t		childs[1024];
	t_pipex		*pipex;
	int			child_i;
	int			last_err;
	t_cmd_lst	*current_cmd;

	pipex = parsing(argv, argc, envp);
	if (pipex == NULL)
		exit(1); // TODO: trouver le bon exit code malloc failed
	last_err = 0;
	child_i = 0;
	current_cmd = pipex->cmds;
	if (pipex->skip_all_pipe)
		current_cmd = get_last(pipex->cmds);
	while (current_cmd != NULL)
	{
		pipe(pipex->pipfds);
		childs[child_i] = fork();
		if (childs[child_i] == 0)
		{
			dup2(pipex->old_fd, STDIN_FILENO);
			if (pipex->skip_all_pipe)
				dup2(pipex->end_fd, STDOUT_FILENO);
			dup2(pipex->pipfds[WR], STDOUT_FILENO);
			close(pipex->pipfds[WR]);
			close(pipex->pipfds[RD]);
			close(pipex->old_fd);
			close(pipex->end_fd);
			execve(current_cmd->cmd_path, current_cmd->cmd_argv, pipex->envp);
			ft_dprintf(2, "pipex: %s: %s", current_cmd->cmd_argv[0], strerror(errno));
			exit(127);
		}
		else if (childs[child_i] < 0)
		{
			ft_dprintf(2, "pipex: fork: %s", strerror(errno));
			pipex_clear(pipex);
			exit(WEXITSTATUS(childs[child_i]));
		}
		close(pipex->old_fd);
		pipex->old_fd = pipex->pipfds[RD];
		close(pipex->pipfds[WR]);
		child_i++;
		current_cmd = current_cmd->next;
	}
	close(pipex->old_fd);
	pipex_clear(pipex);
	wait_all(child_i, argc, childs, &last_err);
	exit(WEXITSTATUS(last_err));
}
