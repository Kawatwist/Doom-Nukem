/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 13:19:22 by lomasse           #+#    #+#             */
/*   Updated: 2019/06/15 14:09:35 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	showconsole(t_win *wn)
{
	SDL_Rect	bg;

	if (wn->xscreen > 300)
	{
		bg.w = 600;
		bg.h = ARIEL_FONT_SIZE * (CONSOLE_MAX_LINE_NB + 1);
		bg.x = 0;
		bg.y = wn->yscreen - bg.h;
		SDL_SetRenderDrawColor(wn->rend, 50, 50, 50, 0);
		SDL_RenderFillRect(wn->rend, &bg);
		bg.w = 600;
		bg.h = ARIEL_FONT_SIZE;
		bg.x = 0;
		bg.y = wn->yscreen - bg.h;
		SDL_SetRenderDrawColor(wn->rend, 100, 100, 100, 0);
		SDL_RenderFillRect(wn->rend, &bg);
	}
}

void		print_one_line(t_win *wn, char *s, int posi_x, int posi_y)
{
	SDL_Color		color;
	int				w;
	int				h;
	SDL_Rect		position;

	color.r = 150;
	color.g = 150;
	color.b = 150;
	color.a = SDL_ALPHA_OPAQUE;
	TTF_SizeText(wn->fonts->ariel, s, &w, &h);
	position.x = posi_x;
	position.y = posi_y;
	// position.w = w < XSCREEN / 4 ? w : 200;
	position.w = w - 5;
 	position.h = h - 5;
	print_text_with_ariel_font(wn, s, color, position);
}

static void	print_console_history(t_win *wn)
{
	int		i;
	int		count;

	count = 1;
	i = (wn->console->index  - 1);
	if (wn->console->index == 0)
		return ;
	while (i  >= 0)
	{
		print_one_line(wn, wn->console->history[i % CONSOLE_MAX_LINE_NB], 35, wn->yscreen - (count + 1) * ARIEL_FONT_SIZE);
		i--;
		count++;
		if (count > CONSOLE_MAX_LINE_NB)
			break;
	}
}

void		print_command(t_win *wn, char *s, int posi_x, int posi_y)
{
	SDL_Color		color;
	int				w;
	int				h;
	SDL_Rect		position;

	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = SDL_ALPHA_OPAQUE;
	TTF_SizeText(wn->fonts->ariel, s, &w, &h);
	position.x = posi_x;
	position.y = posi_y - 5;
	// position.w = w < XSCREEN / 4 ? w : 200;
	position.w = w;
 	position.h = h;
	print_text_with_ariel_font(wn, s, color, position);
}


void		mainconsole(t_win *wn)
{
	showconsole(wn);
	inputconsole(wn);
	print_console_history(wn);
}
