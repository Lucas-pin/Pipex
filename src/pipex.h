/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 20:20:19 by lpin              #+#    #+#             */
/*   Updated: 2024/08/17 22:42:15 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H 
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../libft/libft.h"

typedef struct s_command
{
	char			*cmd_path;
	char			**cmd_option;
	char			*cmd_error;
}					t_command;

typedef struct s_process
{
	int				process_qty;
	int				process_number;
	int				prev_pipe;
}					t_process;

// pipex_utils.c

void	ft_wait(int proccess_number);

int		*ft_pipe_creator(int *pipes, int lstsize, int process_number);

void	ft_pipe_dup(int *pipes, int prev_pipe, int lstsize, int process_number);

void	ft_pipe_closer(int* pipes, int prev_pipe, int lstsize, int process_number);

int		ft_check_entry(int argc, char **argv);

// pipex_cmd_list.c

char	**ft_path_cleaner(char **env);

char	*ft_access_check(char *cmd_path, char **path);

void	ft_path_match(t_list *cmd_list, char **path);

t_list	*ft_list_creator(int argc, char **argv, int bonus_flag);

void	ft_node_destroyer(void *content);

#endif