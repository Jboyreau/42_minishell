/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:27:06 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/25 12:38:08 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"

int	open_file(t_leaf *redirect_to, t_leaf *redirection, t_lv *va, t_cmd *hll)
{
	int		flag;
	char	*file;
	int		fd;

	file = string_sub(redirect_to, va);
	if (file == 0)
		return (write(2, "file malloc failed\n", 20), exit_failure(hll), -1);
	if (redirection->type == L)
		fd = open(file, O_RDONLY);
	else
	{
		if (redirection->type == DR)
			flag = O_APPEND;
		else
			flag = O_TRUNC;
		fd = open(file, O_WRONLY | flag | O_CREAT, 0666);
	}
	if (fd == -1)
		return (write(2, "minishell : ", 12), write(2, file, ft_strlen(file)),
			write(2, ": No such file or directory\n", 29), free(file), -1);
	return (free(file), fd);
}

void	expand_heredoc(t_leaf *redirect, t_lv *va, char *str, int fd)
{
	t_list	*head;
	t_list	*lst;

	head = NULL;
	fd = open(redirect->word, O_RDONLY);
	if (fd == -1)
		return (perror("heredoc : fifo"));
	while (1)
	{
		str = gnl(fd);
		if (str == NULL)
			break ;
		if (string_sub2(&str, va) == FAILURE)
			ft_lstclear(&head);
		lst = ft_lstnew(str);
		ft_lstadd_back(&head, lst);
	}
	close(fd);
	fd = open(redirect->word, O_WRONLY | O_TRUNC);
	lst = head;
	while (lst)
		(write(fd, lst->content, ft_strlen(lst->content)),
			write(fd, "\n", 1), lst = lst->next);
	(close(fd), ft_lstclear(&head));
}

int	file_redirect(t_leaf *redirect, t_exec *ex)
{
	int	fd;

	if (redirect->type == DL)
	{
		expand_heredoc(redirect, ex->cmd_ptr->va, NULL, 0);
		fd = open(redirect->word, O_RDONLY);
		if (dup2(redirect->fdl, STDIN_FILENO) == -1)
			perror("dup2 failed");
		close(fd);
		return (0);
	}
	fd = open_file((redirect + 1), redirect, ex->cmd_ptr->va, ex->cmd_ptr);
	if (fd == -1)
		return (-1);
	if (redirect->type == L)
		dup2(fd, STDIN_FILENO);
	else if (redirect->type == R)
		dup2(fd, STDOUT_FILENO);
	else if (redirect->type == DR)
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	pre_redir(t_leaf *token, int i, t_exec *ex)
{
	int	first_redir;

	first_redir = -1;
	while (i >= 0 && (token[i].type >= L && token[i].type <= DR))
	{
		first_redir = i;
		i -= 2;
	}
	if (first_redir == -1)
		return (0);
	i = first_redir;
	while (token[i].type != -1 && token[i].type != W)
	{
		if (file_redirect(token + i, ex) == -1)
			return (-1);
		i += 2;
	}
	return (0);
}

int	suf_redir(t_leaf *token, t_exec *ex)
{
	t_leaf	*cmd;

	cmd = token;
	cmd->arg = NULL;
	while (token->type != -1)
	{
		if (token->type >= L && token->type <= DR)
		{
			if (file_redirect(token, ex) == -1)
				return (-1);
			token += 2;
		}
		else if (token->type == W)
		{
			if (fill_arg(cmd, token, ex) == -1)
				return (-1);
			token++;
		}
		else
			break ;
	}
	return (0);
}
