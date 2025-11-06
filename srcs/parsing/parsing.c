/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 19:16:29 by ncorrear          #+#    #+#             */
/*   Updated: 2025/11/06 09:43:57 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"
#include "../../includes/ft_printf.h"
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

static char	*cmd_cat(char *cmd, char *path)
{
	char	*tmp_free;
	char	*cmd_line;

	cmd_line = ft_strjoin(path, "/");
	tmp_free = cmd_line;
	cmd_line = ft_strjoin(cmd_line, cmd);
	free(tmp_free);
	return (cmd_line);
}

static char	*get_path_command(char	*command, char **envp)
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

t_cmd_lst	*get_cmd_lst(char	**argv, int argc, char **envp)
{
	t_cmd_lst	*cmds;
	char		*current_cmd;
	char		**current_argv;
	int			i;

	cmds = NULL;
	i = 2;
	while (i < argc - 1)
	{
		current_argv = ft_split(argv[i], ' ');
		if (current_argv != NULL)
		{
			current_cmd = get_path_command(current_argv[0], envp);
			if (ft_lstcmd_add(&cmds, current_cmd, current_argv))
			{
				clear_cmds(&cmds);
				return (NULL);
			}
		}
		i++;
	}
	return (cmds);
}

t_pipex	*parsing(char **argv, int argc, char **envp)
{
	t_pipex	*pipex;

	pipex = malloc(sizeof(t_pipex));
	if (pipex == NULL)
		return (NULL);
	pipex->cmds = get_cmd_lst(argv, argc, envp);
	pipex->skip_all_pipe = 0;
	pipex->old_fd = open(argv[1], O_RDONLY);
	if (pipex->old_fd < 0)
	{
		ft_dprintf(2, "pipex: %s: %s\n", argv[1], strerror(errno));
		pipex->skip_all_pipe = 1;
		pipex->old_fd = open("/dev/null", O_RDONLY);
		if (pipex->old_fd < 0)
			ft_dprintf(2, "pipex: %s: %s\n", argv[1], strerror(errno));
	}
	pipex->end_fd = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pipex->end_fd < 0)
		ft_dprintf(2, "pipex: %s: %s\n", argv[1], strerror(errno));
	if (pipex->cmds == NULL || pipex->old_fd < 0 || pipex->end_fd < 0)
	{
		if (pipex->end_fd > 0)
			close(pipex->end_fd);
		if (pipex->old_fd > 0)
			close(pipex->old_fd);
		free(pipex);
		return (NULL);
	}
	pipex->envp = envp;
	return (pipex);
}
