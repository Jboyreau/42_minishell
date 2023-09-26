/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:06:29 by jboyreau          #+#    #+#             */
/*   Updated: 2023/09/25 14:46:25 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include "minishell.h"

static char	fill_fifo2(t_leaf *lim, int fd)
{
	char	*str;
	int		temp_fd;

	while (1)
	{
		sigint_handler(-5);
		temp_fd = dup(STDIN_FILENO);
		if (ft_readline1(&str, "> ") == FAILURE)
			return (sigint_handler(-6),
				dup2(temp_fd, STDIN_FILENO), close(temp_fd), EXIT_FAILURE);
		dup2(temp_fd, STDIN_FILENO);
		close(temp_fd);
		sigint_handler(-6);
		if (str == NULL)
		{
			write(2, "minishell: warning: here_document delimited by EOF\n", 51);
			break ;
		}
		if (cmp_lim_str(str, (*lim).word, (*lim).len, 0))
			return (free(str), SUCCESS);
		(write(fd, str, ft_strlen1(str)), write(fd, "\n", 1));
		free(str);
	}
	return (SUCCESS);
}

static char	folder_len(DIR *dir, const char *path)
{
	int				i;
	struct dirent	*entry;

	dir = opendir(path);
	if (dir == NULL)
		perror("minishell: directory: ");
	i = 0;
	entry = readdir(dir);
	while (++i, entry)
		entry = readdir(dir);
	closedir(dir);
	return (i);
}

static char	**make_folder(int i, const char *path)
{
	struct dirent	*entry;
	char			**folder;
	DIR				*dir;
	int				len;

	len = folder_len(NULL, path);
	folder = malloc((len) * sizeof(char *));
	if (folder == NULL)
		return (NULL);
	dir = opendir(path);
	if (dir == NULL)
		perror("minishell: directory: ");
	entry = readdir(dir);
	*(folder + i) = ft_strdup((*entry).d_name);
	if (*(folder + i) == NULL)
		return (d_folder(folder), NULL);
	while (++i < len - 1)
	{
		entry = readdir(dir);
		*(folder + i) = ft_strdup((*entry).d_name);
		if (*(folder + i) == NULL)
			return (d_folder(folder), NULL);
	}
	return (*(folder + i) = NULL, closedir(dir), folder);
}

static char	fill_fifo(t_leaf *dl)
{
	static char	file_name[255] = "./.tmp/";
	char		**folder;

	folder = make_folder(0, "./.tmp/");
	if (folder == NULL)
		return (FAILURE);
	(back_tracking(folder, file_name + 7), d_folder(folder));
	(*dl).fdl = open(file_name, O_CREAT | O_WRONLY, 0666);
	if ((*dl).fdl == -1)
		perror("minishell: FIFO: ");
	(*dl).word = ft_strdup(file_name);
	if ((*dl).word == NULL)
		return (d_folder(folder), FAILURE);
	if (fill_fifo2(dl + 1, (*dl).fdl) == FAILURE)
		return (close((*dl).fdl), FAILURE);
	close((*dl).fdl);
	return (SUCCESS);
}

char	heredoc(t_leaf *tr)
{
	int	i;

	i = -1;
	while ((*(tr + (++i))).type != -1)
		if ((*(tr + i)).type == DL)
			if (fill_fifo(tr + i) == FAILURE)
				return (FAILURE);
	return (SUCCESS);
}
