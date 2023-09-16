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

static char	fill_fifo2(t_leaf lim, int fd, char *str, char test)
{
	if (*((*lim).word) == '\"' && *((*lim).word + (*lim).len - 1) == '\"')
		test = 1;
	if (*((*lim).word) == '\'' && *((*lim).word + (*lim).len - 1) == '\'')
		test = 1;
//printf("test = %d\n", test);
	while (1)
	{
		write(1, "> ", 2);
		str = gnl(stdin);
		if (str == (char *)FAILURE) //mem fail
			return (FAILURE);
		if (str == NULL) //ctr + D
		{
			write(2, "minishell: warning: here_document delimited by EOF\n", 51);
			break ;
		}
		if (cmp_lim_str(str, (*(dl + 1)).word) == SUCCESS) //limiter
			break ;
		if (test == 0)
			//string_sub2(&str); TODO : char  string_sub2(char **str);
		write(fd, str, ft_strlen(str));
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

static char	make_folder(void)
{
	char		**folder;
	const char	*path = "/var/tmp";
	DIR			*dir;
	int			len;

	len = folder_len(NULL, path);
	folder = malloc((len + 1));
	dir = opendir(path);
	if (dir == NULL)
		perror("minishell: directory: ");
	i = 0;
	entry = readdir(dir);
	*(folder + i) = ft_strdup((*entry).d_name);
	if (*(folder + i) == NULL)
		return (d_folder(folder), FAILURE);
	while (++i, entry)
	{
		entry = readdir(dir);
		*(folder + i) = ft_strdup((*entry).d_name);
		if (*(folder + i) == NULL)
			return (d_folder(folder), FAILURE);
	}
	*(folder + i) = NULL;
	closedir(dir);
	return (folder);
}

static char	fill_fifo(t_leaf *dl)
{
	char	file_name[255];
	char	**folder;
	int		fd;

	//TODO : Remplir un buffer avec tout les noms de fichiers du dossier.
	folder = make_folder();
	if	(folder == NULL);
		return (FAILURE);
	//TODO : Chercher un nom de fichier qui n'existe pas, back tracking.
	(back_tracking(folder, file_name), d_folder(folder));
	//TODO : Ouvrir un fichier et stoker son fd dans (*dl).fdl.
	(*dl).fdl = open(nomFichier, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	if ((*dl).fdl == -1)
		perror("minishell: FIFO: ");
	//TODO : Remplir le fichier avec gnl tant que j'ai une entrée diférente de lim.
	if (fill_fifo2(dl + 1, fd, NULL, 0) == FAILURE)
		return (FAILURE);
	//TODO : Fermer le fichier.
	close(fd);
	return (SUCCESS);
}

char	heredoc(t_leaf *tr)
{
	int	i;

	i = 0;
	while ((*(tr + (++i))).type != -1)
		if ((*(tr + i)).type == DL)
			if (fill_fifo(tr + i) == FAILURE)
				return (FAILURE);
	return (SUCCESS);
}
