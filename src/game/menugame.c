/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menugame.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 21:01:14 by lomasse           #+#    #+#             */
/*   Updated: 2019/07/05 16:12:35 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	game_interface(t_win *wn)
{
	if (wn->interface == RGAME)
		ft_game_engine(wn);
	else if (wn->interface == NGAME)
		newgame(wn);
	else if (wn->interface == LGAME)
		loadgame(wn);
	else
		menugame(wn);
}
		/* ingame(wn); */
