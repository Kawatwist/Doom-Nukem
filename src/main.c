/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 15:27:26 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/11 14:43:59 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	stop_exec(char *msg, t_win *wn)
{
	ft_putstr(msg);
	(void)wn;
	exit(0);
}

int		main(int argc, char **argv)
{
	t_win	*wn;

	(wn = malloc(sizeof(t_win))) == NULL ? stop_exec("Malloc failed\n", wn): 0;
	init(&wn, argc, argv) == 0 ? stop_exec("Init failed\n", wn) : 0;
	ft_jeronemo(wn);
	turn(wn);
}
