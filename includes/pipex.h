/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:02:22 by ncorrear          #+#    #+#             */
/*   Updated: 2025/11/05 15:45:38 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include "libft.h"
# define RD 0
# define WR 1

typedef struct	s_pipex
{
	t_list	*cmds;
}				t_pipex;

typedef struct	s_cmd
{
	char	*cmd;
	char	**args;
}				t_cmd;

#endif