/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fille_bresename.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 10:35:10 by jchardin          #+#    #+#             */
/*   Updated: 2019/07/21 17:17:01 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>
#include <header_bresenham.h>

void			ft_case_one(t_win *wn, t_myputtheline *s_line)
{
	while (s_line->i <= s_line->d_x)
	{
		(s_line->i)++;
		SDL_RenderDrawPoint(wn->rend, (int)s_line->deux.a,
(int)s_line->deux.b);
		s_line->deux.a += s_line->x_incr;
	}
}

void			ft_case_two(t_win *wn, t_myputtheline *s_line)
{
	while (s_line->i <= s_line->d_x)
	{
		SDL_RenderDrawPoint(wn->rend, (int)s_line->deux.a,
(int)s_line->deux.b);
		(s_line->i)++;
		s_line->deux.a += s_line->x_incr;
		s_line->ex -= s_line->dy;
		if (s_line->ex < 0)
		{
			s_line->deux.b += s_line->y_incr;
			s_line->ex += s_line->dx;
		}
	}
}

void			ft_case_three(t_win *wn, t_myputtheline *s_line)
{
	while (s_line->i <= s_line->d_x)
	{
		(s_line->i)++;
		SDL_RenderDrawPoint(wn->rend, (int)s_line->deux.a,
(int)s_line->deux.b);
		s_line->deux.a += s_line->x_incr;
		s_line->deux.b += s_line->y_incr;
	}
}

void			ft_case_four(t_win *wn, t_myputtheline *s_line)
{
	while (s_line->i <= s_line->d_y)
	{
		SDL_RenderDrawPoint(wn->rend, (int)s_line->deux.a,
(int)s_line->deux.b);
		(s_line->i)++;
		s_line->deux.b += s_line->y_incr;
		s_line->ey -= s_line->dx;
		if (s_line->ey < 0)
		{
			s_line->deux.a += s_line->x_incr;
			s_line->ey += s_line->dy;
		}
	}
}

void			ft_case_five(t_win *wn, t_myputtheline *s_line)
{
	while (s_line->i <= s_line->d_y)
	{
		(s_line->i)++;
		SDL_RenderDrawPoint(wn->rend, (int)s_line->deux.a,
(int)s_line->deux.b);
		s_line->deux.b += s_line->y_incr;
	}
}

void			ft_draw_line(t_win *wn, t_myputtheline *s_line)
{
	s_line->ex = abs((int)s_line->un.a - (int)s_line->deux.a);
	s_line->ey = abs((int)s_line->un.b - (int)s_line->deux.b);
	s_line->dx = 2 * s_line->ex;
	s_line->dy = 2 * s_line->ey;
	s_line->d_x = s_line->ex;
	s_line->d_y = s_line->ey;
	s_line->i = 0;
	s_line->x_incr = 1;
	s_line->y_incr = 1;
	if (s_line->deux.a > s_line->un.a)
		s_line->x_incr = -1;
	if (s_line->deux.b > s_line->un.b)
		s_line->y_incr = -1;
	if (s_line->dy == 0)
		ft_case_one(wn, s_line);
	if (s_line->d_x > s_line->d_y)
		ft_case_two(wn, s_line);
	if (s_line->dx == s_line->dy)
		ft_case_three(wn, s_line);
	if (s_line->d_x < s_line->d_y)
		ft_case_four(wn, s_line);
	if (s_line->dx == 0)
		ft_case_five(wn, s_line);
}

