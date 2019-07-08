/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_qty.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 07:18:36 by naali             #+#    #+#             */
/*   Updated: 2019/07/08 07:33:11 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>
#include <inventaire.h>

static void		ft_init_itemsqty_pos(t_win *wn, SDL_Rect *dst, int pos, int size)
{
	dst->x = (wn->xscreen / 5) - (10 * ((size < 2) ? size : 2));
	dst->y = (wn->yscreen / 18) + (pos * 30);
	dst->w = 10 * ((size <= 4) ? size : 4);
	dst->h = 25;
}

void			print_items_qty(t_win *wn, char *qty, int pos, int isselected)
{
	SDL_Rect	dst;
	SDL_Color	color;

	choose_item_color(&color, isselected);
	ft_init_itemsqty_pos(wn, &dst, pos, ft_strlen(qty));
	print_text_with_ariel_font(wn, qty, color, dst);
}
