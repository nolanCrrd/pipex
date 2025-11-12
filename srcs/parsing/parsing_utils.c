/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:44:11 by ncorrear          #+#    #+#             */
/*   Updated: 2025/11/12 09:00:21 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"
#include "../../includes/ft_printf.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

char	*cmd_cat(char *cmd, char *path)
{
	char	*tmp_free;
	char	*cmd_line;

	cmd_line = ft_strjoin(path, "/");
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

	command_path = NULL;
	while (*envp && ft_strncmp(*envp, "PATH=", 4) != 0)
		envp++;
	if (!*envp)
		return (command_path);
	path_lst = ft_split(*envp + 5, ':');
	i = 0;
	while (path_lst[i])
	{
		tmp_cmd_path = cmd_cat(command, path_lst[i]);
		if (access(tmp_cmd_path, X_OK) == 0)
		{
			command_path = tmp_cmd_path;
			break ;
		}
		free(tmp_cmd_path);
		i++;
	}
	clear_split(path_lst);
	return (command_path);
}

void	open_fds(t_pipex *pipex, char **argv, int argc, int to_append)
{
	pipex->old_fd = open(argv[1 + to_append], O_RDONLY);
	if (pipex->old_fd <= -1)
	{
		ft_dprintf(1, "pipex: %s: %s\n", argv[1], strerror(errno));
		pipex->skip_all_pipe = 0;
		pipex->old_fd = open("/dev/null", O_RDONLY);
		if (pipex->old_fd < -1)
			ft_dprintf(1, "pipex: /dev/null: %s\n", strerror(errno));
	}
	if (to_append > 0)
		pipex->end_fd = open(argv[argc - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		pipex->end_fd = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pipex->end_fd < -1)
		ft_dprintf(1, "pipex: %s: %s\n", argv[argc - 1], strerror(errno));
}

void	clear_split(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}
