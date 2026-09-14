/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 14:33:59 by gregueir          #+#    #+#             */
/*   Updated: 2025/09/02 12:58:01 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include "../../libft/libft.h"

int	g_bit_control;

static void	action(int sig)
{
	if (sig == SIGUSR1)
		g_bit_control = 1;
	else
	{
		ft_printf("Message sent successfully\n");
		exit(0);
	}
}

static void	send_char(char c, int ser_pid)
{
	int	bit;

	bit = __CHAR_BIT__ * sizeof(c) - 1;
	while (bit >= 0)
	{
		g_bit_control = 0;
		if (c & (1 << bit))
			kill(ser_pid, SIGUSR1);
		else
			kill(ser_pid, SIGUSR2);
		bit--;
		while (g_bit_control != 1)
			usleep(10);
	}
}

static void	send_str(char *str, int ser_pid)
{
	int	i;

	i = 0;
	while (*str && str[i])
	{
		send_char(str[i], ser_pid);
		i++;
	}
	send_char(str[i], ser_pid);
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
	signal(SIGUSR1, action);
	signal(SIGUSR2, action);
	send_str(args[2], ser_pid);
	while (1)
		sleep(1);
	return (0);
}
