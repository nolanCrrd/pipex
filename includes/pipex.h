/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:02:22 by ncorrear          #+#    #+#             */
/*   Updated: 2025/11/06 13:45:48 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include "libft.h"
# define RD 0
# define WR 1

typedef struct	s_cmd_lst
{
	char				*cmd_path;
	char				**cmd_argv;
	struct s_cmd_lst	*next;
}				t_cmd_lst;

typedef struct	s_pipex
{
	int			pipfds[2];
	int			old_fd;
	int			skip_all_pipe;
	int			end_fd;
	t_cmd_lst	*cmds;
	char		**envp;
}				t_pipex;

// list manipulation
t_cmd_lst	*ft_cmdlst_new(char	*cmd, char	**argv);
void	clear_cmds(t_cmd_lst **lst);
int		ft_lstcmd_add(t_cmd_lst **lst, char *cmd, char **argv_cmd);
t_cmd_lst	*get_last(t_cmd_lst *lst);

// split
void	clear_split(char **strs);

// parsing
char	*cmd_cat(char *cmd, char *path);
char	*get_path_command(char	*command, char **envp);
void	open_fds(t_pipex *pipex, char **argv, int argc);
t_pipex	*parsing(char **argv, int argc, char **envp);

// pipex struct
void	pipex_clear(t_pipex *pipex);

#endif