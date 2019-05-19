/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 15:27:26 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/16 14:04:50 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	stop_exec(char *msg, t_win *wn)
{
	int			fd;

	ft_putstr(msg);
	if (!access("/tmp/doom_log2", F_OK))
		fd = open("/tmp/doom_log2", O_WRONLY | O_APPEND);
	else
		fd = creat("/tmp/doom_log2", O_WRONLY | O_APPEND);
	if (fd != 0)
		write(fd, msg, ft_strlen(msg));
	(void)wn; // FREE WN
	exit(0);
}

int		main(int argc, char **argv)
{
	t_win	*wn;

	printf("AVANT\n");
	(wn = malloc(sizeof(t_win))) == NULL ? stop_exec("Malloc failed\n", wn): 0;
	printf("MALLOC\n");
	init(&wn, argc, argv) == 0 ? stop_exec("Init failed\n", wn) : 0;
	printf("INIT\n");
	turn(wn);
}
