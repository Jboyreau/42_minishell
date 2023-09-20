/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:27:06 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/19 11:27:07 by cbessonn         ###   ########.fr       */
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

int	open_file(t_leaf *redirect_to, t_leaf *redirection, t_lv *va)
{
    int flag;
	char *file;
	int	fd;

	file = string_sub(redirect_to, va);
	if (file == 0)
		return (fprintf(stderr, "file malloc failed"), -1);
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
	free(file);
	if (fd == -1)
	{
		fprintf(stderr, "minishell: %s: No such file or directory\n", file); //a remplacer
		exit(1);
	}
	return (fd);
}

void	expand_heredoc(t_leaf *redirect, t_lv *va)
{
	char 	*str;
	t_list 	*head;
	t_list 	*lst;
	int		fd;

	head = NULL;
	fd = open(redirect->word, O_RDONLY);
	if (fd == -1)
		perror("heredoc : fifo :");
	while (1)
	{
		str = gnl(fd);
		if (str == NULL) //EOF
			break ;
		if (string_sub2(&str, va) == FAILURE)
			ft_lstclear(&head);
		lst = ft_lstnew(str);
		ft_lstadd_back(&head, lst);
	}
	close(fd);
	fd = open(redirect->word, O_WRONLY | O_TRUNC);
	while (head)
	{
		write(fd, head->content, ft_strlen(head->content));
		write(fd, "\n", 1);
		head = head->next;
	}
	close(fd);
	ft_lstclear(&head);
}

void	file_redirect(t_leaf *redirect, t_exec *ex)
{
	int	fd;

	if (redirect->type == DL)
	{
		expand_heredoc(redirect, ex->cmd_ptr->va);
		fd = open(redirect->word, O_RDONLY);
		if (dup2(redirect->fdl, STDIN_FILENO) == -1)
			perror("dup2 failed");
		close(fd);
		return ;
	}
	fd = open_file((redirect + 1), redirect, ex->cmd_ptr->va);
	if (redirect->type == L)
		dup2(fd, STDIN_FILENO);
	else if (redirect->type == R)
		dup2(fd, STDOUT_FILENO);
	else if (redirect->type == DR)
		dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	prefix_redirect(t_leaf *token, int i, t_exec *ex)
{
	int	first_redir;

	first_redir = -1;
	while (i >= 0 && (token[i].type >= L && token[i].type <= DR))
	{
		first_redir = i;
		i -= 2;		
	}
	if (first_redir == -1)
		return ;
	i = first_redir;
	while (token[i].type != -1 && token[i].type != W)
	{
		file_redirect(token + i, ex);
		i += 2;
	}
}

void	suffix_redirect(t_leaf *token, t_exec *ex)
{
	t_leaf	*cmd;

	cmd = token;
	cmd->arg = NULL;
	while (token->type != -1)
	{
		if (token->type >= L && token->type <= DR)
		{
			file_redirect(token, ex);
			token += 2;
		}
		else if (token->type == W)
		{
			args_to_array(cmd, token, ex->cmd_ptr->va);
			token++;
		}
		else
			break ;
	}
}
