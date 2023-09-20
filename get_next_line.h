/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 18:22:11 by jboyreau          #+#    #+#             */
/*   Updated: 2023/09/18 18:41:27 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 80
# endif
# if (BUFFER_SIZE < 0)
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif
# define FMA 1023
# define FMI 0

int		ft_strlen_gnl(char *str, char mode);
char	*gnl(int fd);
char	ft_check_next_line(char *next_line, int test);
char	*ft_reshape(char *next_line);
#endif
