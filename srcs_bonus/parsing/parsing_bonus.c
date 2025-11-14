/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 19:16:29 by ncorrear          #+#    #+#             */
/*   Updated: 2025/11/12 11:10:04 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"
#include "../../includes/ft_printf.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/**
 * @brief Create the command chained list based on program's arguments
 * 
 * @param argv Program's arguments
 * @param argc Number of arguments
 * @param envp Environnement variables of the user
 * @param skip_first Boolean (skip first command if input not found)
 * @return t_cmd_lst* 
 */
t_cmd_lst	*get_cmd_lst(char	**argv, int argc, char **envp, int skip_first)
{
	t_cmd_lst	*cmds;
	char		*current_cmd;
	char		**cu_argv;
	int			i;

	cmds = NULL;
	i = 2 + skip_first;
	while (i < argc - 1)
	{
		cu_argv = ft_split(argv[i], ' ');
		if (cu_argv != NULL)
		{
			current_cmd = get_path_command(cu_argv[0], envp);
			if (current_cmd == NULL)
				ft_dprintf(2, "pipex: command not found: %s\n", cu_argv[0]);
			if (ft_lstcmd_add(&cmds, current_cmd, cu_argv))
			{
				clear_split(cu_argv);
				clear_cmds(&cmds);
				return (NULL);
			}
		}
		i++;
	}
	return (cmds);
}

/**
 * @brief Initiate all important data for the execution
 * 
 * @param argv Program's arguments
 * @param argc Number of arguments
 * @param envp Environnement variables of the user
 * @return t_pipex*
 */
t_pipex	*parsing(char **argv, int argc, char **envp)
{
	t_pipex	*pipex;
	int		skip_here_doc;

	pipex = malloc(sizeof(t_pipex));
	if (pipex == NULL)
		return (NULL);
	skip_here_doc = ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0;
	pipex->cmds = get_cmd_lst(argv, argc, envp, skip_here_doc);
	pipex->skip_all_pipe = 0;
	open_fds(pipex, argv, argc, skip_here_doc);
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
