/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msn.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 12:55:16 by lomasse           #+#    #+#             */
/*   Updated: 2019/07/08 19:24:56 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "client.h"
#include "server.h"

static char *removemsg(char *msg)
{
	char *ret;

	ret = ft_strjoin(&msg[4], "\0");
	free(msg);
	return(ret);
}

static char	*convmsg(char *msg)
{
	int		i;
	int		nb;
	char	*ret;

	i = -1;
	nb = 0;
	while (msg[++i] != 0)
		msg[i] <= 126 && msg[i] >= 20 ? nb++ : 0;
	ret = malloc(sizeof(char) * nb + 1);
	i = -1;
	nb = 0;
	while (msg[++i] != 0)
	{
		if (msg[i] <= 126 && msg[i] >= 20)
		{
			ret[nb] = msg[i];
			nb++;
		}
	}
	ret[nb] = '\0';
	return (ret);
}

void		add_chat(t_win *wn, int user)
{
	char	*msg;
	char	dc;
	
	dc = 0;
	while (TRUE)
	{
		msg = NULL;
		msg = (wn->serv == NULL ? get_msg_client(wn) : get_msg_server(wn, user));
		msg = convmsg(msg);
//		msg != NULL && wn->serv != NULL ? printf("(SERVER)J'AI RECU SE MESSAGE : %s\n", msg) : 0;
//		msg != NULL && wn->client != NULL ? printf("(CLIENT)J'AI RECU SE MESSAGE : %s\n", msg) : 0;
		if (ft_strncmp(msg, "/msg", 3))
		{
			free(msg);
			msg = NULL;
			dc++;
		}
		else
			msg = removemsg(msg);
		if (dc > 2)
		{
			stop_com(wn, user);
			break;
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
		msg != NULL ? free(msg) : 0;
	}
	stop_com(wn, user);
}

int			chat_box(t_win *wn, char *msg)
{
	if (ft_strlen(msg) <= 4)
		return (0);
	if (key_pressed(wn, SDL_SCANCODE_RETURN) && wn->client != NULL)
		send_msg_from_client(wn, msg);
	else if (key_pressed(wn, SDL_SCANCODE_RETURN) && wn->serv != NULL)
	{
		printf("(user 0) : wn->menu->ask == |%d|\n", wn->menu->ask & 0x03);
		printf("(user 1) : wn->menu->ask == |%d|\n", (wn->menu->ask & 0x0C) >> 2);
		printf("(user 2) : wn->menu->ask == |%d|\n", (wn->menu->ask & 0x30) >> 4);
		(wn->menu->ask & 0x03) == 3 ? send_msg_from_server(wn, msg, 0) : 0;
		((wn->menu->ask & 0x0C) >> 2) == 3 ? send_msg_from_server(wn, msg, 1) : 0;
		((wn->menu->ask & 0x30) >> 4) == 3 ? send_msg_from_server(wn, msg, 2) : 0;
	}
	if (ft_strncmp(msg, "/msg", 4))
		return (0);
	return (1);
}
