/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 15:05:16 by lomasse           #+#    #+#             */
/*   Updated: 2019/06/15 11:47:31 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static char *special_key(t_win *wn, char *line)
{
	int	i;

	if (line != NULL)
	{
		i = ft_strlen(line);
		if (key_pressed(wn, SDL_SCANCODE_BACKSPACE))
			line[i - 1] = '\0';
		if (key_pressed(wn, SDL_SCANCODE_KP_DIVIDE))
			line = ft_strjoinfree(line, "/", 1);
	}
	else
	{
		if (key_pressed(wn, SDL_SCANCODE_KP_DIVIDE))
			line = ft_strdup("/\0");
	}
	return (line);
}

static char	printable_key_check(int i)
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
	else if (i == SDL_SCANCODE_PERIOD || i == SDL_SCANCODE_KP_PERIOD)
		return ('.');
	else
		return (INVALID);
}

static char	*basic_key(t_win *wn, char *line)
{
	int				i;
	char			str[2];
	char			key_val;

	i = 0;
	key_val = 0;
	while (i <= 99)
	{
		if (key_pressed(wn, i))
		{
			key_val = printable_key_check(i);
			if (key_val != INVALID)
			{
				str[0] = key_val;
				str[1] = '\0';
				if (line == NULL)
					line = ft_strdup(str);
				else
					line = ft_strjoinfree(line, ft_strdup(str), 3);
			}
		}
		i++;
	}
	return (line);
}

char		*text_box(t_win *wn, char *line)
{

	line = basic_key(wn, line);
	line = special_key(wn, line);
	return (line);
}
