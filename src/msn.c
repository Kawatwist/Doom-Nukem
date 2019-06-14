/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msn.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 12:55:16 by lomasse           #+#    #+#             */
/*   Updated: 2019/06/14 15:24:46 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static char	*convmsg(char *msg)
{
	int		i;
	int		nb;
	char	*ret;

	i = -1;
	nb = 0;
	while (msg[++i])
		msg[i] != -66 ? nb++ : 0;
	ret = malloc(sizeof(char) * nb + 1);
	i = -1;
	nb = 0;
	while (msg[++i])
	{
		if (msg[i] != -66)
		{
			ret[nb] = msg[i];
			nb++;
		}
	}
	ret[nb] = '\0';
	return (ret);
}

void		add_chat(t_win *wn)
{
	char *msg;
	
	while (TRUE)
	{
		msg = NULL;
		msg = (wn->serv == NULL ? get_msg_client(wn) : get_msg_server(wn));
		msg = convmsg(msg);
		if (ft_strncmp(msg, "/msg", 4))
		{
			free(msg);
			msg = NULL;
		}
		if (wn->console->index < CONSOLE_MAX_LINE_NB && msg != NULL)
		{
			wn->console->history[wn->console->index] = ft_strdup(msg);
			wn->console->index++;
		}
		else if (msg != NULL)
		{
			free(wn->console->history[wn->console->index % CONSOLE_MAX_LINE_NB]);
			wn->console->history[wn->console->index % CONSOLE_MAX_LINE_NB] = NULL;
			wn->console->history[wn->console->index % CONSOLE_MAX_LINE_NB] = ft_strdup(msg);
			wn->console->index++;
		}
	}
}

void		chat_box(t_win *wn, char *msg)
{
	wn->serv == NULL && key_pressed(wn, SDL_SCANCODE_RETURN) ? send_msg_from_client(wn, msg) : send_msg_from_server(wn, msg);
}
