/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:43:32 by jchardin          #+#    #+#             */
/*   Updated: 2019/07/10 14:06:07 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header_game_engine.h>

void		ft_clear_window(t_win *wn)
{
	SDL_SetRenderDrawColor(wn->rend, 0, 0, 0, 255);
    SDL_RenderClear(wn->rend);
}
