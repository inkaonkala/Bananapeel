/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:47:58 by iniska            #+#    #+#             */
/*   Updated: 2024/09/26 12:11:46 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*extrct_path(char *path, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(path, envp[i], ft_strlen(path)) == 0
			&& envp[i][ft_strlen(path)] == '=')
			return (ft_strchr(envp[i], '=') + 1);
		i++;
	}
	return (NULL);
}

char	**find_path_env(char **envp)
{
	char	*path;

	path = extrct_path("PATH", envp);
	if (!path)
		return (NULL);
	return (ft_split(path, ':'));
}

static char	*const_and_check(char *paths, char *path_name)
{
	char	*oneline;
	char	*full_path;

	if (paths == NULL && path_name == NULL)
		return (NULL);
	oneline = ft_strjoin(paths, "/");
	if (!oneline)
		return (NULL);
	full_path = ft_strjoin(oneline, path_name);
	free(oneline);
	if (!full_path)
		return (NULL);
	if (access(full_path, F_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

char	*get_path(char *path_name, char **envp)
{
	int		i;
	char	*full_path;
	char	**paths;

	if (access(path_name, F_OK) == 0)
		return (ft_substr(path_name, 0, ft_strlen(path_name)));
	paths = find_path_env(envp);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i] != NULL)
	{
		full_path = const_and_check(paths[i], path_name);
		if (full_path)
		{
			free_line(paths, -1);
			return (full_path);
		}
		i++;
	}
	free_line(paths, -1);
	return (NULL);
}
