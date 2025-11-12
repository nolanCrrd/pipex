/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 15:47:22 by ncorrear          #+#    #+#             */
/*   Updated: 2025/11/12 10:38:00 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"
#include <unistd.h>
#include <stdlib.h>

/**
 * @brief Delete properly all the pipex structure
 * 
 * @param pipex Datas
 */
void	pipex_clear(t_pipex *pipex)
{
	clear_cmds(&pipex->cmds);
	close(pipex->end_fd);
	close(pipex->old_fd);
	close(pipex->pipfds[0]);
	close(pipex->pipfds[1]);
	free(pipex);
}
