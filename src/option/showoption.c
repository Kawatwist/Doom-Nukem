/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   showoption.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 13:45:38 by lomasse           #+#    #+#             */
/*   Updated: 2019/04/25 11:23:36 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		showoption(t_win *wn)
{
	SDL_SetRenderDrawColor(wn->rend, 100, 0, 100, 0);
	SDL_RenderCopy(wn->rend, findtexture(wn,
				"invalide", "Nope", "Error"), NULL, NULL);
	SDL_RenderClear(wn->rend);
}
