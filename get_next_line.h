/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoch <jakoch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 11:50:52 by jakoch            #+#    #+#             */
/*   Updated: 2026/05/30 15:44:24 by jakoch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <fcntl.h> // open
#include <unistd.h> // read, close
#include <stdio.h> // printf

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

char *get_next_line(int fd);


#endif