/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 13:19:22 by lomasse           #+#    #+#             */
/*   Updated: 2019/04/22 12:00:17 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	readcommand(t_win *wn)
{
	ft_strcmp(wn->command, "kill") == 0 ? stop_exec("KILL !\n", wn) : 0;
	ft_strncmp(wn->command, "value", 5) == 0
		&& ft_strlen(wn->command) > 5
		? wn->debugconsole = ft_atoi(&(wn->command[5])) : 0;
	free(wn->command);
	wn->command = NULL;
}

static void	historyconsole(t_win *wn)
{
	static char **history = NULL;

	(void)history;
	(void)wn;
}


void	sub_print_command(t_win *wn, SDL_Texture *texture, int len)
{
	int				tex_width;
	int				tex_height;
	SDL_Rect		position;

	tex_width = 0;
	tex_height = 0;
	SDL_QueryTexture(texture, NULL, NULL, &tex_width, &tex_height);
	position.x = 35;
	position.y = YSCREEN - 70;
	position.w = 20 * len;
 	position.h = 20;
	SDL_RenderCopy(wn->rend, texture, NULL, &position);
}

static void		print_command(t_win *wn, char *s)
{
	SDL_Color		color;
	SDL_Surface		*surface;
	SDL_Texture		*texture;
	TTF_Font		*font;

	font = TTF_OpenFont("/Library/Fonts/Arial.ttf", 35);  //init font outside the loop later
	if (font == NULL)
		stop_exec("TTF_OpenFont()failed", wn);
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = SDL_ALPHA_OPAQUE;
	surface = TTF_RenderText_Solid(font, s, color);
	if (surface == NULL)
		stop_exec("TTF_RenderText()failed", wn);
	texture = SDL_CreateTextureFromSurface(wn->rend, surface);
	if (texture == NULL)
		stop_exec("SDL_CreateTextureFromSurface()failed", wn);
	SDL_FreeSurface(surface);
	sub_print_command(wn, texture, ft_strlen(s));
	TTF_CloseFont(font); // replace it outside the loop
}


static char	find_which_key_pressed(int i)
{
	if ((i >= SDL_SCANCODE_A) && (i <= SDL_SCANCODE_Z))
		return (i - SDL_SCANCODE_A + 'a');
	else if ((i >= SDL_SCANCODE_1) && (i <= SDL_SCANCODE_9))
		return (i - SDL_SCANCODE_1 + '1');
	else if ((i >= SDL_SCANCODE_KP_1) && (i <= SDL_SCANCODE_KP_9))
		return (i - SDL_SCANCODE_KP_1 + '1');
	else if ( i == SDL_SCANCODE_SPACE)
		return (' ');
	else if (i == SDL_SCANCODE_0)
		return ('0');
	else if (i == SDL_SCANCODE_KP_0)
		return ('0');
	else
		return (INVALID);
}

static int	 key_pressed(t_win *wn, int i)
{
	if (wn->state[i] && !(wn->old[i]))
		return (TRUE);
	return (FALSE);
}

static void	inputconsole(t_win *wn)
{
	static char		 *command = NULL;
	int			i;
	char		str[2];
	char		key_val;

	i = 0;
	key_val = 0;
	while (i <= 99)
	{
		if (key_pressed(wn, i) == TRUE)
		{
			key_val = find_which_key_pressed(i);
			if (key_val != INVALID)
			{
				str[0] = key_val;
				str[1] = '\0';
				if (command == NULL)
					command = ft_strdup(str);
				else
					command = ft_strjoinfree(command, ft_strdup(str), 3);
			}
		}
		i++;
	}
	if ((command != NULL) && ft_strlen(command))
		print_command(wn, command);



	(wn->state[SDL_SCANCODE_BACKSPACE]
		&& !wn->old[SDL_SCANCODE_BACKSPACE])
		&& command != NULL && ft_strlen(command)
		? (command[ft_strlen(command) - 1] = 0) : 0;
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
		bg.y = YSCREEN * 2 / 3;
		bg.w = XSCREEN / 3;
		bg.h = YSCREEN / 3;
		SDL_SetRenderDrawColor(wn->rend, 50, 50, 50, 0);
		SDL_RenderFillRect(wn->rend, &bg);
		bg.x = 30;
		bg.y = YSCREEN - 70;
		bg.w = XSCREEN / 3 - 60;
		bg.h = 30;
		SDL_SetRenderDrawColor(wn->rend, 150, 150, 150, 0);
		SDL_RenderFillRect(wn->rend, &bg);
	}
}

void		mainconsole(t_win *wn)
{
	showconsole(wn);
	inputconsole(wn);
	if (wn->command && wn->command != NULL)
		readcommand(wn);
	historyconsole(wn);
}
