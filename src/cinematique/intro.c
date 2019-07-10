/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intro.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 20:46:22 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/22 11:48:47 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

char	*changename(char *name, int place)
{
	int		value;

	value = ft_atoi(&(name[place]));
	value++;
	place += 3;
	while (value > 0)
	{
		name[place] = (value % 10) + '0';
		value /= 10;
		place -= 1;
	}
	return (name);
}

void	intro(t_win *wn)
{
	int			img;
	char		*name;
	SDL_Texture	*texture;

	name = ft_strdup("texture/intro/menu/test0001.tga");
	img = 1;
	while (img < 60)
	{
		texture = initload2(&wn, name);
		SDL_RenderCopy(wn->rend, texture, NULL, NULL);
		SDL_RenderPresent(wn->rend);
		name = changename(name, 23);
		img += 1;
	}
}

void	showreverseintro(t_win *wn, t_text *img)
{
	Uint32 difftime;
	Uint32 time;
	
	if (img != NULL)
	{
		while (img->before != NULL)
		{
			time = SDL_GetTicks();
			SDL_RenderCopy(wn->rend, img->txt, NULL, NULL);
			SDL_RenderPresent(wn->rend);
			img = img->before;
			difftime = SDL_GetTicks();
			SDL_Delay(difftime - time < 1000 / 30 ? (1000 / 30) - (difftime - time) :  0);
		}
	}
}

void	showintro(t_win *wn, t_text *img)
{
	Uint32 difftime;
	Uint32 time;
	
	if (img != NULL)
	{
		while (img->next != NULL)
		{
			time = SDL_GetTicks();
			SDL_RenderCopy(wn->rend, img->txt, NULL, NULL);
			SDL_RenderPresent(wn->rend);
			img = img->next;
			difftime = SDL_GetTicks();
			SDL_Delay(difftime - time < 1000 / 30 ? (1000 / 30) - (difftime - time) :  0);
			while (wn->flag & CINE) //DEBUG
			{
				setkeyboard(wn->old, wn->state);
				SDL_PollEvent(&(wn->ev));
				wn->state = (Uint8*)SDL_GetKeyboardState(NULL);
				if (!wn->old[SDL_SCANCODE_RETURN] && wn->state[SDL_SCANCODE_RETURN])
					break;
				if (!wn->old[SDL_SCANCODE_ESCAPE] && wn->state[SDL_SCANCODE_ESCAPE])
					exit(0);
				if (wn->state[SDL_SCANCODE_R])
					break;
			}
		}
	}
}
