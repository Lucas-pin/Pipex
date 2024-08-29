/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:06:40 by lpin              #+#    #+#             */
/*   Updated: 2024/08/29 18:35:06 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void ft_cmd_exec(t_list *cmd_list, char **envp)
{
	char	*cmd_path;
	char	**cmd_option;
	char	*cmd_error;

	cmd_path = ((t_command *)(cmd_list->content))->cmd_path;
	cmd_option = ((t_command *)(cmd_list->content))->cmd_option;
	cmd_error = ((t_command *)(cmd_list->content))->cmd_error;

	if (cmd_error == NULL)
		execve(cmd_path, cmd_option, envp);
	else
	{
		ft_node_destroyer(cmd_list->content);
		perror("execve");
	}
}
void	ft_child_process(int *pipes, t_process *process, t_list *cmd_list, char **envp)
{
	ft_pipe_dup(pipes, process->prev_pipe, process->process_qty, process->process_number);
	ft_pipe_closer(pipes, process->prev_pipe, process->process_qty, process->prev_pipe);
	ft_cmd_exec(cmd_list, envp);
	exit(EXIT_SUCCESS);
}
void	ft_father_process(int *pipes, t_process *process)
{
	ft_pipe_closer(pipes, process->prev_pipe, process->process_qty, process->process_number);
    if (process->process_number < process->process_qty - 1)
        process->prev_pipe = pipes[0];
}

void	ft_fork_creator(t_list *cmd_list, char **envp)
{
	t_process	process;
	int pid;
	int pipes[2];

	process.process_number = 0;
	process.prev_pipe = -1;
	process.process_qty = ft_lstsize(cmd_list);
	while (process.process_number < process.process_qty)
	{
		ft_pipe_creator(pipes, process.process_qty, process.process_number);
		pid = fork();
		if (pid < 0)
			perror("fork");
		if (pid == 0) 
			ft_child_process(pipes, &process, cmd_list, envp);
		else
			ft_father_process(pipes, &process);
		cmd_list = cmd_list->next;
		process.process_number++;
	}
	ft_wait(process.process_qty);
}

int main(int argc, char *argv[], char **envp)
{
	t_list		*cmd_list;
	char		**path;
	int			entry_ret;

	entry_ret = ft_check_entry(argc, argv);
	cmd_list = ft_list_creator(argc, argv, entry_ret);
	path = ft_path_cleaner(envp);
	ft_path_match(cmd_list, path);
	ft_fork_creator(cmd_list, envp);
	ft_lstclear(&cmd_list, &ft_node_destroyer);
	return (0);
}
