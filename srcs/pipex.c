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
char	*cmd_cat(char *cmd, char *path)
{
	char	*tmp_free;
	char	*cmd_line;

	cmd_line = NULL;
	cmd_line = ft_strjoin(cmd_line, path);
	tmp_free = cmd_line;
	cmd_line = ft_strjoin(cmd_line, "/");
	free(tmp_free);
	tmp_free = cmd_line;
	cmd_line = ft_strjoin(cmd_line, cmd);
	free(tmp_free);
	return (cmd_line);
}

char	*get_path_command(char	*command, char **envp)
{
	char	**path_lst;
	char	*command_path;
	char	*tmp_cmd_path;
	int		i;

	while (*envp && ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	path_lst = ft_split(*envp + 5, ':');
	command_path = NULL;
	i = 0;
	while (path_lst[i])
	{
		tmp_cmd_path = cmd_cat(command, path_lst[i]);
		if (access(tmp_cmd_path, X_OK) == 0)
		{
			command_path = tmp_cmd_path;
			break;
		}
		free(tmp_cmd_path);
		i++;
	}
	clear_split(path_lst);
	return (command_path);
}

void	parse_cmds(int argc, char **argv, t_pipex *pipex)
{
	int	i;

	pipex->cmds = NULL;
	while (argv)
	{
		code
	}
}

// Alloc need to be in the parent and not the child
int	main(int argc, char **argv, char **envp)
{
	pid_t	childs[1024];
	int		pipfd[2];
	int		old_wr_pipe;
	int		child_i;
	int		argv_i;
	char	**cmd_args;
	char	*cmd;
	int		go_to_last;
	int		last_err;

	child_i = 0;
	last_err = 0;
	go_to_last = 0;
	old_wr_pipe = open(argv[1], O_RDONLY);
	if (old_wr_pipe < 0)
	{
		ft_dprintf(2, "pipex: %s: %s", argv[1], strerror(errno));
		old_wr_pipe = open("/dev/null", O_RDONLY);
		go_to_last = 1;
		if (old_wr_pipe < 0)
		{
			ft_dprintf(2, "pipex: %s: %s", "/dev/null", strerror(errno));
			exit(WEXITSTATUS(old_wr_pipe));
		}
	}
	argv_i = 2;
	if (go_to_last)
		argv_i = argc - 2;
	while (argv_i < argc - 1)
	{
		pipe(pipfd);
		cmd_args = ft_split(argv[argv_i], ' ');
		cmd = get_path_command(cmd_args[0], envp);
		childs[child_i] = fork();
		if (childs[child_i] == 0)
		{
			dup2(old_wr_pipe, STDIN_FILENO);
			dup2(pipfd[WR], STDOUT_FILENO);
			if (argv_i == argc - 2)
				dup2(open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644), STDOUT_FILENO);
			close(pipfd[WR]);
			close(pipfd[RD]);
			close(old_wr_pipe);
			execve(cmd, cmd_args, envp);
			ft_dprintf(2, "pipex: %s: %s", cmd_args[0], strerror(errno));
			exit(127);
		}
		else if (childs[child_i] < 0)
		{
			ft_dprintf(2, "pipex: fork: %s", strerror(errno));
			clear_split(cmd_args);
			free(cmd);
			close(old_wr_pipe);
			close(pipfd[RD]);
			close(pipfd[WR]);
			exit(WEXITSTATUS(childs[child_i]));
		}
		clear_split(cmd_args);
		free(cmd);
		close(old_wr_pipe);
		old_wr_pipe = pipfd[RD];
		close(pipfd[WR]);
		argv_i++;
		child_i++;
	}
	close(old_wr_pipe);
	while (child_i >= 0)
	{
		if (child_i-- == argv_i - 2)
			waitpid(childs[child_i], &last_err, 0);
		else
			waitpid(childs[child_i], NULL, 0);
	}
	exit(WEXITSTATUS(last_err));
}
