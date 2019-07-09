/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_names.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 06:58:05 by naali             #+#    #+#             */
/*   Updated: 2019/07/08 07:18:45 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>
#include <inventaire.h>

static void		ft_init_itemsname_pos(t_win *wn, SDL_Rect *dst, int pos, int size)
{
	dst->x = (wn->xscreen / 77);
	dst->y = (wn->yscreen / 18) + (pos * 30);
	dst->w = 10 * ((size <= 32) ? size : 32);
	dst->h = 25;
}

void			print_items_name(t_win *wn, char *name, int pos, int isselected)
{
	SDL_Rect	dst;
	SDL_Color	color;

	choose_item_color(&color, isselected);
	ft_init_itemsname_pos(wn, &dst, pos, ft_strlen(name));
	print_text_with_ariel_font(wn, name, color, dst);
}
