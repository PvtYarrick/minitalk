/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:38:55 by gregueir          #+#    #+#             */
/*   Updated: 2025/08/28 16:46:38 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <signal.h>
#include "../libft/libft.h"

int	send_char(unsigned char c, int ser_pid)
{
	unsigned char	bit;

	bit = 0b10000000;
	while (bit)
	{
		if (bit & c)
		{
			if (kill(ser_pid, SIGUSR1) == -1)
				return (0);
		}
		else
		{
			if (kill(ser_pid, SIGUSR2) == -1)
				return (0);
		}
		bit >>= 1;
		usleep(400);
	}
	return (1);
}

int	send_str(char *str, int ser_pid)
{
	int	i;

	i = 0;
	while (*str && str[i])
	{
		send_char(str[i], ser_pid);
		i++;
	}
	return (0);
}

int	main(int argn, char **args)
{
	int	ser_pid;

	if (argn != 3)
	{
		ft_printf("SINTAX: 'PID', 'STR'");
		return (-1);
	}
	ser_pid = ft_atoi(args[1]);
	if (kill(ser_pid, 0) == -1 && errno == ESRCH)
	{
		ft_printf("Invalid PID");
		return (-1);
	}
	send_str(args[2], ser_pid);
	return (0);
}
