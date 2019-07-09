/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 13:59:10 by lomasse           #+#    #+#             */
/*   Updated: 2019/07/09 20:01:34 by lomasse          ###   ########.fr       */
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

	len = 0;
	printf("%c=> %d\n", msg[0], msg[0]);
	printf("%d\n", msg[1]);
	printf("%d\n", msg[2]);
	printf("%d\n", msg[3]);
	if (msg[1] == 1)
	{
		len = msg[2] != 65 ? (msg[2] << 8) : 0;
		len += msg[3] != 65 ? (msg[3]) : 0;
//		printf("Len du msg : %d\n", len);
		ret = malloc(sizeof(char) * len + 1);
		ft_memcpy(ret, &msg[4], len);
		ret[len] = 0;
//		if (ms[3 + len] != ';')
//			printf("Ohoh ? : %d\n", msg[3 + len]);
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
