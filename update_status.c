/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:36:45 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/23 15:21:56 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putnbr_tab(t_string *str, int power, unsigned int n_abs, int n)
{
	if (n < 0)
	{
		*((*str).content + (*str).cursor) = '-';
		(*str).cursor++;
	}
	while (power)
	{
		*((*str).content + ((*str).cursor++)) = (n_abs / power) + 48;
		n_abs = n_abs % power;
		power /= 10;
	}
}

void	ft_putnbr_q(int n, t_string *str)
{
	int				power;
	unsigned int	n_abs;
	unsigned int	save_abs;

	n_abs = n;
	if (n < 0)
		n_abs = -n;
	save_abs = n_abs / 10;
	power = 1;
	while (save_abs)
	{
		save_abs /= 10;
		power *= 10;
	}
	ft_putnbr_tab(str, power, n_abs, n);
}

// int	update_exit_stat(t_lv *va, int code)
// {
// 	int	index;

// 	if (find_name("?", va, &index) == SUCCESS)
// 		ft_putnbr_q(code, (*(va + index)).content);
// 	return (SUCCESS);
// }
