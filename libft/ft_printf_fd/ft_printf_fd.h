/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 00:16:36 by ankammer          #+#    #+#             */
/*   Updated: 2024/10/10 14:23:59 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_FD_H

# define FT_PRINTF_FD_H

# include <stdarg.h>
# include <unistd.h>

int	ft_printf_fd(int fd, const char *format, ...);
int	ft_printchar(char arg, int fd);
int	ft_printstr(char *str, int fd);
int	ft_printnbr(int nbr, int fd);
int	ft_print_unsigned(unsigned int nbr, int fd);
int	ft_printhex(unsigned long nbr, char arg, int fd);
int	ft_printptr(unsigned long ptr, int fd);

#endif