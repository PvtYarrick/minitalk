/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:38:46 by gregueir          #+#    #+#             */
/*   Updated: 2025/08/28 14:23:34 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "../libft/libft.h"

void	recieve_signal(int sigsent)
{
	static int				bits;
	static unsigned char	buff;

	buff |= (sigsent == SIGUSR1);
	bits++;
	if (bits == 8)
	{
		ft_printf("%c", buff);
		bits = 0;
		buff = 0;
	}
	else
		buff <<= 1;
}

int	main(void)
{
	int	pid;

	pid = getpid();
	ft_printf("PID: %i\n", pid);
	signal(SIGUSR2, recieve_signal);
	signal(SIGUSR1, recieve_signal);
	while (1)
		pause();
	return (0);
}
