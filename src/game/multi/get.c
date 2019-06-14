/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 13:59:10 by lomasse           #+#    #+#             */
/*   Updated: 2019/06/14 14:08:42 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "server.h"
#include "client.h"

char		*get_msg_client(t_win *wn)
{
	char	*buff;

	buff = malloc(sizeof(char) * 1024);
	recv(((t_client *)wn->client)->sockfd, buff, 1024, 0);
	return (buff);
}

char		*get_msg_server(t_win *wn)
{
	char	*buff;

	buff = malloc(sizeof(char) * 1024);
	recv(((t_server *)wn->serv)->newsockfd, buff, 1024, 0);
	return (buff);
}
