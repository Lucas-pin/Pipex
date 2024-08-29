/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 20:19:36 by lpin              #+#    #+#             */
/*   Updated: 2024/08/29 18:33:03 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_pipe_dup(int *pipes, int prev_pipe, int lstsize, int process_number)
{
	if (process_number > 0)
		dup2(prev_pipe, STDIN_FILENO);
	if (process_number < lstsize - 1)
		dup2(pipes[1], STDOUT_FILENO);
}
void	ft_pipe_closer(int* pipes, int prev_pipe, int lstsize, int process_number)
{
	if (process_number > 0)
        close(prev_pipe);
    if (process_number < lstsize - 1)
        close(pipes[1]);
}

void	ft_wait(int proccess_number)
{
	while (proccess_number > 0)
	{
		wait(NULL);
		proccess_number--;
	}
}

int	*ft_pipe_creator(int *pipes, int lstsize, int process_number)
{
	if (process_number < lstsize - 1)
    {
        if (pipe(pipes) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }
	return (pipes);
}

int	ft_check_entry(int argc, char **argv)
{
	int	fd_in;
	int	fd_out;

	if (argc < 5 || *argv == NULL)
		exit(-1);
	if ((fd_in = open(argv[1], O_RDONLY)) == -1)
	{
		perror("file");
		exit(EXIT_FAILURE);
	}
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	if ((fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT, 0664)) == -1)
	{
		perror("file");
		exit(EXIT_FAILURE);
	}
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	return (0);
}
