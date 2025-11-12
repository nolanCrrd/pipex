/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 15:30:48 by ncorrear          #+#    #+#             */
/*   Updated: 2025/11/12 08:41:49 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>
#include "../includes/ft_printf.h"
#include "../includes/pipex.h"

// write nothing if error -> create file anyway
// ls do ls in current folder without considering the in file

// if < file -> cat the file
// if < file command -> command file
// if < file command > file -> output the command in the file
// if file = dir send it without open

// top get multiple pipe -> create while and break it if its the parent
// get the path instead of /usr/bin

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

void	wait_all(int argv_i, int argc, int *childs, int *last_err)
{
	while (argv_i >= 2)
	{
		if (argv_i-- == argc - 3)
			waitpid(childs[argv_i], last_err, 0);
		else
			waitpid(childs[argv_i], NULL, 0);
	}
}

void	child_exec(t_pipex *pipex, t_cmd_lst *current_cmd)
{
	dup2(pipex->old_fd, STDIN_FILENO);
	dup2(pipex->pipfds[WR], STDOUT_FILENO);
	if (pipex->skip_all_pipe || current_cmd->next == NULL)
		dup2(pipex->end_fd, STDOUT_FILENO);
	close(pipex->pipfds[WR]);
	close(pipex->pipfds[RD]);
	close(pipex->old_fd);
	close(pipex->end_fd);
	if (current_cmd != NULL)
		execve(current_cmd->cmd_path, current_cmd->cmd_argv, pipex->envp);
	pipex_clear(pipex);
	exit(127);
}

int	exec_all(t_pipex *pipex, pid_t childs[1024])
{
	t_cmd_lst	*current_cmd;
	int			child_i;

	child_i = -1;
	current_cmd = pipex->cmds;
	if (pipex->skip_all_pipe)
		current_cmd = get_last(pipex->cmds);
	while (current_cmd != NULL)
	{
		pipe(pipex->pipfds);
		childs[++child_i] = fork();
		if (childs[child_i] == 0)
			child_exec(pipex, current_cmd);
		else if (childs[child_i] < 0)
		{
			ft_dprintf(2, "pipex: fork: %s", strerror(errno));
			pipex_clear(pipex);
			return (childs[child_i]);
		}
		close(pipex->old_fd);
		pipex->old_fd = pipex->pipfds[RD];
		close(pipex->pipfds[WR]);
		current_cmd = current_cmd->next;
	}
	return (child_i);
}

// TODO: split the function to norm
int	main(int argc, char **argv, char **envp)
{
	pid_t		childs[1024];
	t_pipex		*pipex;
	int			child_i;
	int			last_err;
	t_cmd_lst	*current_cmd;

	pipex = parsing(argv, argc, envp);
	if (pipex == NULL)
		exit(WEXITSTATUS(127));
	last_err = 0;
	current_cmd = pipex->cmds;
	child_i = exec_all(pipex, childs);
	wait_all(child_i, argc, childs, &last_err);
	if (child_i < 0)
		exit(WEXITSTATUS(4));
	close(pipex->old_fd);
	pipex_clear(pipex);
	exit(WEXITSTATUS(last_err));
}
