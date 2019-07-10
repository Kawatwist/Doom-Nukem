/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optioninput.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 13:44:37 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/22 11:45:37 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		optioninput(t_win *wn)
{
	!(wn->flag & CONSOLE) && key_pressed(wn, SDL_SCANCODE_ESCAPE)
		? wn->interface = MENU : 0;
}
