/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:59:23 by lomasse           #+#    #+#             */
/*   Updated: 2019/06/12 16:15:26 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>

typedef struct	s_server
{
	int			sockfd;
	int			newsockfd;
	int			port;
	int			len;
	struct sockaddr_in serv_addr;
	struct sockaddr_in cli_addr;
}				t_server;

#endif
