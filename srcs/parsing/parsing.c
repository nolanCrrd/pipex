/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 19:16:29 by ncorrear          #+#    #+#             */
/*   Updated: 2025/11/06 14:58:17 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

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
			if (current_cmd == NULL || ft_lstcmd_add(&cmds, current_cmd, current_argv))
			{
				clear_split(current_argv);
				clear_cmds(&cmds);
				return (NULL);
			}
		}
		i++;
	}
	return (cmds);
}

// TODO: make >> work -> O_APPEND
t_pipex	*parsing(char **argv, int argc, char **envp)
{
	t_pipex	*pipex;

	pipex = malloc(sizeof(t_pipex));
	if (pipex == NULL)
		return (NULL);
	pipex->cmds = get_cmd_lst(argv, argc, envp);
	pipex->skip_all_pipe = 0;
	open_fds(pipex, argv, argc);
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
