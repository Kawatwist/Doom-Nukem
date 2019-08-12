/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copytxt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 13:41:04 by lomasse           #+#    #+#             */
/*   Updated: 2019/07/27 13:57:09 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

void	fillcopy(wn, unsigned int *img, SDL_Rect pos, SDL_Rect dir, int size) // SIZE SIDE img <= DO NOT RESIZE
{
	int	indexx;
	int	indexy;

	indexx = pos.x;
	while (indexx < pos.x + pos.w)
	{
		indexy = pos.y;
		while (indexy < pos.y + pos.h)
		{
			if (dir.x + (dir.y * size) + indexx + (indexy * size) > wn->xscreen * wn->yscreen)
				break;
			else
				((unsigned int *)wn->pixels)[dir.x + (dir.y * size) + indexx + (indexy * size)] = img[indexx + (indexy * size)];
			indexy++;
		}
		indexx++;
	}
}
