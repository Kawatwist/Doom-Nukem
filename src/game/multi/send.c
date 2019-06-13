/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 13:57:48 by lomasse           #+#    #+#             */
/*   Updated: 2019/06/13 17:24:14 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "server.h"
#include "client.h"

void		send_msg_from_client(t_win *wn, char *msg)
{
	send(((t_client *)wn->client)->sockfd, msg, ft_strlen(msg), 0);
}

void		send_msg_from_server(t_win *wn, char *msg)
{
	send(((t_server *)wn->serv)->newsockfd, msg, ft_strlen(msg), 0);
}
