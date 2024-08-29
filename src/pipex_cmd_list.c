/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_cmd_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 20:34:13 by lpin              #+#    #+#             */
/*   Updated: 2024/08/17 22:41:59 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_path_cleaner(char **env)
{
	char	*raw_path;
	char	*temp;
	char	**path;

	raw_path = NULL;
	path = NULL;
	while(*env && raw_path == NULL)
	{
		raw_path = ft_strnstr(*env, "PATH=/usr", ft_strlen(*env)); // Change the path to "PATH=/home" for 42's tests
		env++;
	}
	path = ft_split(raw_path, ':');
	if (path == NULL)
		return(NULL);
	temp = *path;
	*path = ft_strdup(ft_strchr(*path, '/'));
	free(temp);
	return (path);
}
char	*ft_access_check(char *cmd_path, char **path)
{
	char	*new_cmd_path;

	new_cmd_path = NULL;
	while (*path)
	{
		new_cmd_path = ft_strjoin("/", cmd_path);
		if (new_cmd_path == NULL)
			return (ft_destroyer(&new_cmd_path));
		new_cmd_path = ft_strjoin_free(*path, new_cmd_path);
		if (new_cmd_path == NULL)
			return (ft_destroyer(&new_cmd_path));
		if (access(new_cmd_path, F_OK) == 0)
			break;
		path++;
		free(new_cmd_path);
		new_cmd_path = NULL;
	}
	return(new_cmd_path);
}
void	ft_path_match(t_list *cmd_list, char **path)
{
	int		i;
	char	*access_ret;
	char	*cmd_path;

	i = ft_lstsize(cmd_list);
	while (i > 0)
	{
		cmd_path = ((t_command *)cmd_list->content)->cmd_path;
		access_ret = ft_access_check(cmd_path, path);
		if (access_ret == NULL)
		{
			((t_command *)cmd_list->content)->cmd_error = ft_strjoin("zsh: command not found:", cmd_path);
			if (((t_command *)cmd_list->content)->cmd_error == NULL)
				return (free(((t_command *)cmd_list->content)->cmd_error));
		}	
		else
			((t_command *)cmd_list->content)->cmd_path = access_ret;
		i--;
		cmd_list = cmd_list->next;
	}
	ft_split_destroyer(path);
	free(path);
}

t_list	*ft_list_creator(int argc, char **argv, int bonus_flag)
{
	t_command	*cmd_data;
	t_list		*cmd_list;
	char		**split_data;
	int			i;

	split_data = NULL;
	cmd_data = NULL;
	cmd_list = NULL;
	i = 2 + bonus_flag;
	while (i < argc - 1)
	{
		cmd_data = malloc(sizeof(t_command));
		if (cmd_data == NULL)
			return (NULL);
		split_data = ft_split(argv[i], ' ');
		if (split_data == NULL)
			return (ft_node_destroyer((void *)cmd_data), NULL);
		cmd_data->cmd_path = split_data[0];
		cmd_data->cmd_option = split_data;
		cmd_data->cmd_error = NULL;
		ft_lstadd_back(&cmd_list, ft_lstnew(cmd_data));
		i++;
	}
	return (cmd_list);
}
void	ft_node_destroyer(void *content)
{
	t_command	*cmd_list;

	cmd_list = (t_command *)content;
	if (cmd_list->cmd_error == NULL)
	{
		free(cmd_list->cmd_path);
		cmd_list->cmd_path = NULL;
	}	
	if (cmd_list->cmd_option != NULL)
	{
		ft_split_destroyer(cmd_list->cmd_option);
		free(cmd_list->cmd_option);
	}
	if (cmd_list->cmd_error != NULL)
		ft_destroyer(&(cmd_list->cmd_error));
	free(cmd_list);
}