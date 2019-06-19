/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 13:57:48 by lomasse           #+#    #+#             */
/*   Updated: 2019/06/19 16:48:01 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "server.h"
#include "client.h"

static char	*add_user(char *msg, char *user)
{
	int		i;
	char	*ret;

	i = ft_strlen(user);
	ret = malloc(sizeof(char) * i + 3);
	ft_strcpy(&ret[1], user);
	ret[0] = '[';
	ret[i + 1] = ']';
	ret[i + 2] = ' ';
	ret = ft_strjoinfree(ret, msg, 1);
	return (ret);
}

void		send_msg_from_client(t_win *wn, char *msg)
{
	printf("(CLIENT)JE VAIS ENVOYER SE MESSAGE : %s\n", msg);
	if (((t_client *)wn->client)->username == NULL)
		getlogin_r(((t_client *)wn->client)->username, 8);
	msg = add_user(msg, ((t_client *)wn->client)->username);
	send(((t_client *)wn->client)->sockfd, msg, ft_strlen(msg), 0);
	printf("Message envoyer !\n");
}

void		send_msg_from_server(t_win *wn, char *msg, int	user)
{
	printf("(SERVER)JE VAIS ENVOYER SE MESSAGE : %s\n", msg);
	if (((t_server *)wn->serv)->username == NULL)
	{
		printf("C'est quoi mon login ?\n");
		((t_server *)wn->serv)->username = malloc(sizeof(char) * 8);
		getlogin_r(((t_server *)wn->serv)->username, 8);
	}
	printf("J'envoie !\n");
	msg = add_user(msg, ((t_server *)wn->serv)->username);
	send(((t_server *)wn->serv)->user[user].socket, msg, ft_strlen(msg), 0);
	printf("Message envoyer !\n");
}
