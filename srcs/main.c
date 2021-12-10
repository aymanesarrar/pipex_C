/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aysarrar <aysarrar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:23:04 by aysarrar          #+#    #+#             */
/*   Updated: 2021/12/10 17:51:20 by aysarrar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// !i will allocate the t_pipex list that contains some variables which i'm gonna use in the project
// ?check if the allocation fails
// !if it fails exit with failure
// ?else we gonna check for arguments list
// ?if we have enough arguments to call the mandatory function we call it with the required arguments
//!i'm gonna make a function to check if the commands exists and can be executed then i'm gonna fork
//!
// and we gonna add some other if checks for bonuses
// the first one if the arguments count is 6 and there is a here_doc arg we call the here_doc func that we gonna use later
// if there is no enough arguments we gonna print informations about the project and return 1 (failure)
// return 0
char	*get_path(char *envp[])
{
	//!this function is gonna return the path (PATH);
	//!loop through the envp and search for the PATH keyword
	//!return it
	int		index;

	index = 0;
	while (envp[index])
	{
		if (ft_strnstr(envp[index], "PATH", ft_strlen(envp[index])) != NULL)
			return (envp[index]);
		index++;
	}
	return (NULL);
}
char	*full_command(char *cmd, char *path)
{
	char	*full_path;
	char	*full_cmd;

	full_path = ft_strjoin(path, "/");
	full_cmd = ft_strjoin(full_path, cmd);
	if (!full_cmd || !full_path)
		return (NULL);
	free(full_path);
	return (full_cmd);
}
int		check_cmd(char *cmd, char *path)
{
	//! split the path var into multiple paths
	//! join every path with the / + the command name
	//! check if it does exist and it is executable (return 1)
	char	*new_path;
	char	**split_path;
	char	*full_cmd;
	int		path_len;
	int		index;

	index = -1;
	if (!cmd || !path)
		return (0);
	path_len = ft_strlen(path);
	new_path = ft_substr(path, 5, path_len - 5);
	if (!new_path)
		return (0);
	split_path = ft_split(new_path, ':');
	if (!split_path)
		return (0);
	while (split_path[++index])
	{
		full_cmd = full_command(cmd, split_path[index]);
		if ((access(full_cmd, X_OK) == 0 && access(full_cmd, F_OK) == 0) || (access(cmd, X_OK) == 0 && access(cmd, F_OK)))
			return (1);
		free(full_cmd);
	}
	return (0);
}
int main(int argc, char **argv, char *envp[])
{
	t_pipex	*pipe_list;

	pipe_list = malloc(sizeof(t_pipex *));
	if (!pipe_list)
		return (1);
	
}