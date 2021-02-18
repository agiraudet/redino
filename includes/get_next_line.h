/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 22:21:38 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/18 21:51:33 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 256

# include <stdlib.h>
# include <unistd.h>

int		get_next_line(int fd, char **line);
int		getnl(const char *str);
char	*ft_strdup(char *str);
int		clean_join(char **cont, char *buf);
int		get_first_line(char **line, char **cont);

#endif
