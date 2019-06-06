/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_fonts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 14:32:38 by jleblond          #+#    #+#             */
/*   Updated: 2019/05/17 14:32:41 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		load_fonts(t_win *wn)
{
	wn->fonts = (t_fonts*)malloc(sizeof(t_fonts));
	if (wn->fonts == NULL)
		stop_exec("malloc failed in load_fonts()", wn);
	wn->fonts->ariel = TTF_OpenFont("/Library/Fonts/Arial.ttf", ARIEL_FONT_SIZE);
	if (wn->fonts->ariel == NULL)
		stop_exec("TTF_OpenFont() failed in load_font()", wn);
}
