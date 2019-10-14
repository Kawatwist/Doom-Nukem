/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:26:17 by jleblond          #+#    #+#             */
/*   Updated: 2019/10/14 14:26:36 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	display_monsters(t_win *wn)
{
	SDL_Rect	dst;

	dst = define_rect(0, 0, 100, 100);
	SDL_RenderCopy(wn->rend, findtexture(wn, "game", "monster", "alien"),
		 NULL, &dst);
}
