/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_draw_triangle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 11:54:33 by jchardin          #+#    #+#             */
/*   Updated: 2019/07/16 16:48:49 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header_game_engine.h>
#include <header_bresenham.h>

void	ft_draw_triangle_base(t_myvec *v1, t_myvec *v2, t_myvec *v3, t_win *wn)
{
	SDL_SetRenderDrawColor(wn->rend, 0, 0, 0, 255);
	t_myputtheline		s_line;;

	s_line.un.a = v1->x;
	s_line.un.b = v1->y;
	s_line.deux.a = v2->x;
	s_line.deux.b = v2->y;
	ft_draw_line(wn, &s_line);
	s_line.un.a = v2->x;
	s_line.un.b = v2->y;
	s_line.deux.a = v3->x;
	s_line.deux.b = v3->y;
	ft_draw_line(wn, &s_line);
	s_line.un.a = v3->x;
	s_line.un.b = v3->y;
	s_line.deux.a = v1->x;
	s_line.deux.b = v1->y;
	drawlinexyz(wn, 0xFF000000, s_line.un, s_line.deux);
}
