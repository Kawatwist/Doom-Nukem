/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 13:19:22 by lomasse           #+#    #+#             */
/*   Updated: 2019/04/20 18:04:57 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

static void	historyconsole(t_win *wn)
{
	static char **history = NULL;

	(void)history;
	(void)wn;
}

static void inputconsole(t_win *wn)
{
	static char *command = NULL;
	int			i;
	char		a;

	i = 3;
	if (command == NULL)
	{
		while (i++ < 30)
		{
			a = (i + 'a') - 4;
			(wn->state[i] && !wn->old[i]) ? command = ft_strdup(&(a)) : 0;
		}
	}
	else
	{
		while (i++ < 30)
		{
			a = i - 4 + 'a';
			printf("%d\n", a);
			(wn->state[i] && !wn->old[i]) ? command = ft_strjoinfree(command, ft_strdup(&(a)),3) : 0;
		}
	}
	a = ' ';
	(wn->state[SDL_SCANCODE_SPACE] && !wn->old[SDL_SCANCODE_SPACE]) ? command = ft_strjoinfree(command, ft_strdup(&(a)),3) : 0;
	printf("=> %s\n", command);
}

static void showconsole(t_win *wn)
{
	SDL_Rect	bg;

	if (XSCREEN > 300)
	{
		bg.x = 0;
		bg.y = YSCREEN - 500;
		bg.w = 600;
		bg.h = 500;
		SDL_SetRenderDrawColor(wn->rend, 50, 50, 50, 0);
		SDL_RenderFillRect(wn->rend, &bg);
		bg.x = 30;
		bg.y = YSCREEN - 70;
		bg.w = 540;
		bg.h = 30;
		SDL_SetRenderDrawColor(wn->rend, 150, 150, 150, 0);
		SDL_RenderFillRect(wn->rend, &bg);
	}
}

void	mainconsole(t_win *wn)
{
	inputconsole(wn);
	historyconsole(wn);
	showconsole(wn);
}
