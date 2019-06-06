/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 15:27:26 by lomasse           #+#    #+#             */
/*   Updated: 2019/06/06 11:00:55 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	stop_exec(char *msg, t_win *wn)
{
	int			fd;

	ft_putstr(msg);
	if (!access("/tmp/doom_log", F_OK))
		fd = open("/tmp/doom_log", O_WRONLY | O_APPEND);
	else
		fd = creat("/tmp/doom_log", O_WRONLY | O_APPEND);
	if (fd != 0)
		write(fd, msg, ft_strlen(msg));
	(void)wn; // FREE WN
	exit(0);
}

int		main(int argc, char **argv)
{
	t_win	*wn;

	(wn = malloc(sizeof(t_win))) == NULL ? stop_exec("Malloc failed\n", wn): 0;
	init(&wn, argc, argv) == 0 ? stop_exec("Init failed\n", wn) : 0;
	/* ft_jeronemo(wn); */
	/* exit(0); */
	turn(wn);
}
