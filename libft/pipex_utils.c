/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aysarrar <aysarrar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:05:21 by aysarrar          #+#    #+#             */
/*   Updated: 2021/12/10 15:44:18 by aysarrar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	execute(char *str, char *cmd, char *envp[], char **command)
{
	char	*full_cmd;
	char	*new_path;
	int		execve_r;

	new_path = ft_strjoin(str, "/");
	if (!new_path)
		handle_errors("ft_strjoin fail");
	full_cmd = ft_strjoin(new_path, cmd);
	if (!full_cmd)
		handle_errors("ft_strjoin fail");
	if ((access(full_cmd, X_OK) == 0) && (access(full_cmd, F_OK) == 0))
	{
		free(new_path);
		execve_r = execve(full_cmd, command, envp);
		if (execve_r == -1)
			handle_errors("error");
	}
	free(new_path);
	free(full_cmd);
}

int	get_path_and_execute(char **cmd, char *envp[])
{
	char	*get_env;
	int		index;
	char	**exec_path;
	char	*path;

	index = 0;
	get_env = get_path(envp);
	if (!get_env)
		handle_errors("couldnt get the path");
	path = ft_substr(get_env, 5, ft_strlen(get_env) - 5);
	if (!path)
		handle_errors("path error");
	free(get_env);
	exec_path = ft_split(path, ':');
	free(path);
	while (exec_path[index] != NULL)
	{
		execute(exec_path[index], cmd[0], envp, cmd);
		index++;
	}
	return (-1);
}

void	child_process(t_pipex *pipe_list, char *envp[], char *cmd1)
{
	char	**parse_cmd1;
	int		exec_r;

	pipe_list->dup2_r = dup2(pipe_list->infile, 0);
	parse_cmd1 = ft_split(cmd1, ' ');
	if (pipe_list->dup2_r < 0)
		handle_errors("dup2");
	pipe_list->dup2_r = dup2(pipe_list->fd[1], 1);
	if (pipe_list->dup2_r < 0)
		handle_errors("dup2");
	close(pipe_list->outfile);
	close(pipe_list->fd[0]);
	if (parse_cmd1[1] == NULL)
		execve(parse_cmd1[0], parse_cmd1, envp);
	exec_r = get_path_and_execute(parse_cmd1, envp);
	if (exec_r == -1)
	{
		perror("command not found");
		exit(127);
	}
}

void	second_child_process(t_pipex *pipe_list, char *envp[], char *cmd2)
{
	char	**parse_cmd2;
	int		exec_r;

	parse_cmd2 = ft_split(cmd2, ' ');
	pipe_list->dup2_r = dup2(pipe_list->outfile, 1);
	if (pipe_list->dup2_r < 0)
		handle_errors("dup2");
	pipe_list->dup2_r = dup2(pipe_list->fd[0], 0);
	if (pipe_list->dup2_r < 0)
		handle_errors("dup2");
	close(pipe_list->infile);
	close(pipe_list->fd[1]);
	if (parse_cmd2[1] == NULL)
		execve(parse_cmd2[0], parse_cmd2, envp);
	exec_r = get_path_and_execute(parse_cmd2, envp);
	if (exec_r == -1)
	{
		perror("command not found");
		exit(127);
	}
}
