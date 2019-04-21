/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainintro.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 17:05:46 by lomasse           #+#    #+#             */
/*   Updated: 2019/04/11 18:30:42 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void		mainintro(t_win *wn, char *type, char *subtype, int	pos)
{
	t_text	*img;
	int		place;

	place = (pos & 0x7FFFFFFF);
	img = findpostxt(wn, type, subtype, ft_itoa(place));
	if ((pos & 0x80000000) == 0)
		showintro(wn, img);
	else
		showreverseintro(wn, img);
}
