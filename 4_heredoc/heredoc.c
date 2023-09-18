/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboyreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:06:29 by jboyreau          #+#    #+#             */
/*   Updated: 2023/09/16 20:23:32 by jboyreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "minishell.h"

static char	fill_fifo2(t_leaf *lim, int fd, char *str, char test)
{
	if (*((*lim).word) == '\"' && *((*lim).word + (*lim).len - 1) == '\"')
		test = 1;
	if (*((*lim).word) == '\'' && *((*lim).word + (*lim).len - 1) == '\'')
		test = 1;
	while (1)
	{
		str = gnl(1);
		if (str == (char *)FAILURE) //mem fail
			return (FAILURE);
		if (str == NULL) //ctr + D
		{
			write(2, "minishell: warning: here_document delimited by EOF\n", 51);
			break ;
		}
		if (cmp_lim_str(str, (*lim).word, (*lim).len)) //limiter
			return (free(str), SUCCESS);
		if (test == 0)
			//string_sub2(&str); TODO : char  string_sub2(char **str);
		write(fd, str, ft_strlen1(str));
		free(str);
	}
	return (SUCCESS);
}

static char	folder_len(DIR *dir, const char *path)
{
	int		i;
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
	static char	file_name[255] = "./temp/";
	char		**folder;

	//Remplir un buffer avec tout les noms de fichiers du dossier.
	folder = make_folder(0, "./temp");
	if	(folder == NULL)
		return (FAILURE);
	//Chercher un nom de fichier qui n'existe pas, back tracking.
	(back_tracking(folder, file_name + 7), d_folder(folder));
	//Ouvrir un fichier et stoker son fd dans (*dl).fdl.
	(*dl).fdl = open(file_name, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	if ((*dl).fdl == -1)
		perror("minishell: FIFO: ");
	(*dl).word = ft_strdup(file_name);
	if ((*dl).word == NULL)
		return (d_folder(folder), FAILURE);
	//Remplir le fichier avec gnl tant que j'ai une entrée diférente de lim.
	if (fill_fifo2(dl + 1, (*dl).fdl, NULL, 0) == FAILURE)
		return (FAILURE);
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
