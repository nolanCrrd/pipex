/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 19:08:37 by ncorrear          #+#    #+#             */
/*   Updated: 2025/11/06 13:38:23 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"
#include <stdlib.h>
#include <unistd.h>

/**
 * @brief Create an element of a chained list with the given content
 * 
 * @param content value of the element
 * @return t_list* the created element
 */
t_cmd_lst	*ft_cmdlst_new(char	*cmd, char	**argv)
{
	t_cmd_lst	*new;

	new = malloc(sizeof(t_cmd_lst));
	if (new == NULL)
		return (new);
	new->cmd_path = cmd;
	new->cmd_argv = argv;
	new->next = NULL;
	return (new);
}

/**
 * @brief add new chained list at the end of the given one
 * 
 * @param lst chained list to edit
 * @param new new head of the other chained list
 */
int	ft_lstcmd_add(t_cmd_lst **lst, char *cmd, char **cmd_argv)
{
	t_cmd_lst	*current;
	t_cmd_lst	*new;

	new = ft_cmdlst_new(cmd, cmd_argv);
	if (new == NULL)
		return (1);
	if (*lst == NULL)
		*lst = new;
	else
	{
		current = *lst;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	return (0);
}

void	clear_cmds(t_cmd_lst **lst)
{
	t_cmd_lst	*current;
	t_cmd_lst	*tmp;

	current = *lst;
	while (current)
	{
		tmp = current->next;
		clear_split(current->cmd_argv);
		free(current->cmd_path);
		free(current);
		current = tmp;
	}
	*lst = NULL;
}

t_cmd_lst	*get_last(t_cmd_lst *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	pipex_clear(t_pipex *pipex)
{
	clear_cmds(&pipex->cmds);
	close(pipex->end_fd);
	close(pipex->old_fd);
	close(pipex->pipfds[0]);
	close(pipex->pipfds[1]);
	free(pipex);
}