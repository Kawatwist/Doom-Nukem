/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 13:19:22 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/11 09:16:57 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	readcommand(t_win *wn)
{
	ft_strcmp(wn->command, "kill") == 0 ? stop_exec("KILL !\n", wn) : 0;
	ft_strcmp(wn->command, "slow") == 0 ? wn->debugcine *= -1 : 0;
	ft_strncmp(wn->command, "value", 5) == 0
		&& ft_strlen(wn->command) > 5
		? wn->debugconsole = ft_atoi(&(wn->command[5])) : 0;
	ft_strncmp(wn->command, "sky", 3) == 0
		&& ft_strlen(wn->command) > 3
		? wn->sky = ft_atoi(&(wn->command[3])) : 0;
	free(wn->command);
	wn->command = NULL;
}

static void	historyconsole(t_win *wn)
{
	static char **history = NULL;

	(void)history;
	(void)wn;
}

static void	inputconsole(t_win *wn)
{
	static char *command = NULL;
	int			i;
	char		a[2];

	i = 3;
	a[1] = 0;
	while (i++ < 29)
	{
		a[0] = (i + 'a') - 4;
		if (command == NULL)
			(wn->state[i] && !wn->old[i]) ? (command = ft_strdup(a)) : 0;
		else
			(wn->state[i] && !wn->old[i])
				? (command = ft_strjoinfree(command, ft_strdup(a), 3)) : 0;
	}
	i = 88;
	while (i++ < 97)
	{
		a[0] = (i + '1') - 89;
		if (command == NULL)
			(wn->state[i] && !wn->old[i]) ? (command = ft_strdup(a)) : 0;
		else
			(wn->state[i] && !wn->old[i])
				? (command = ft_strjoinfree(command, ft_strdup(a), 3)) : 0;
	}
	a[0] = '0';
	(command == NULL && wn->state[98]
		&& !wn->old[98]) ? (command = ft_strdup(a)) : 0;
	(command != NULL && wn->state[98]
		&& !wn->old[98])
		? (command = ft_strjoinfree(command, ft_strdup(a), 3)) : 0;
	a[0] = ' ';
	(wn->state[SDL_SCANCODE_SPACE]
		&& !wn->old[SDL_SCANCODE_SPACE])
		? command = ft_strjoinfree(command, ft_strdup(a), 3) : 0;
	(wn->state[SDL_SCANCODE_BACKSPACE]
		&& !wn->old[SDL_SCANCODE_BACKSPACE])
		&& command != NULL && ft_strlen(command)
		? (command[ft_strlen(command) - 1] = 0) : 0;
	!wn->old[SDL_SCANCODE_ESCAPE] && wn->state[SDL_SCANCODE_ESCAPE] ? wn->debug *= -1 : 0;
	if (wn->state[SDL_SCANCODE_RETURN]
			&& !wn->old[SDL_SCANCODE_RETURN] && command != NULL)
	{
		wn->command = ft_strdup(command);
		free(command);
		command = NULL;
	}
}

static void	showconsole(t_win *wn)
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

void		mainconsole(t_win *wn)
{
	inputconsole(wn);
	if (wn->command && wn->command != NULL)
		readcommand(wn);
	historyconsole(wn);
	showconsole(wn);
}
