/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 13:59:10 by lomasse           #+#    #+#             */
/*   Updated: 2019/07/09 16:36:44 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "server.h"
#include "client.h"

char		*parse_packet(t_win *wn, char *msg)
{
	(void)wn;
	char	*ret;
	int		len;

//	if (msg[0] != ';')
//		return (NULL);
	printf("%s\n", msg);
	if (msg[1] == 1)
	{
		len = msg[2] << 8;
		len += msg[3];
		ret = ft_strndup(msg, len);
		free(msg);
		if (msg[3 + len] != ';')
			printf("Ohoh ? : %d\n", msg[3 + len]);
	}
	else
		return (NULL);
	return (ret);
}

char		*get_msg_client(t_win *wn)
{
	char	*buff;

	buff = malloc(sizeof(char) * 1024);
	recv(((t_client *)wn->client)->sockfd, buff, 1024, 0);
	buff = parse_packet(wn, buff);
	return (buff);
}

char		*get_msg_server(t_win *wn, int user)
{
	char	*buff;

	buff = malloc(sizeof(char) * 1024);
	recv(((t_server *)wn->serv)->user[user].socket, buff, 1024, 0);
	buff = parse_packet(wn, buff);
	return (buff);
}
