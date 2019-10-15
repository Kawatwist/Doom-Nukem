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

#include <bsp.h>
#include "doom.h"

void	display_monsters(t_win *wn)
{
	SDL_Rect	dst;
	t_vec 		*sp_pos1;
	t_vec 		*sp_pos2;

	sp_pos1 = create_vec(1500.0, 0.0, 1000.0);
	sp_pos2 = create_vec(1500.0, 0.0, 1000.0);
	if (line_of_sight(wn->rasterizer->bsp, sp_pos1, sp_pos2, 0))
	{
		printf("Monster visible\n\n\n\n\n\n");
		dst = define_rect(0, 0, 100, 100);
		SDL_RenderCopy(wn->rend, findtexture(wn, "game", "monster", "alien"),
			 NULL, &dst);
	}
	else
	{
		printf("NO Monster\n\n");
	}
	free(sp_pos1);
	free(sp_pos2);
}
