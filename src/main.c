/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 15:27:26 by lomasse           #+#    #+#             */
/*   Updated: 2019/06/17 17:53:28 by jchardin         ###   ########.fr       */
/*   Updated: 2019/05/19 16:39:45 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

void	stop_exec(char *msg, t_win *wn)
{
	int			fd;

	ft_putstr(msg);
	wn->fonts->ariel != NULL ? TTF_CloseFont(wn->fonts->ariel) : 0;
	SDL_Quit();
	TTF_Quit();
	if (!access("/tmp/doom_log", F_OK))
		fd = open("/tmp/doom_log", O_WRONLY | O_APPEND);
	else
		fd = creat("/tmp/doom_log2", O_WRONLY | O_APPEND);
	if (fd != 0)
		write(fd, msg, ft_strlen(msg));
	exit(0);
}

int		main(int argc, char **argv)
{
	t_win	*wn;

	(wn = malloc(sizeof(t_win))) == NULL ? stop_exec("Malloc failed\n", wn): 0;
	init(&wn, argc, argv) == 0 ? stop_exec("Init failed\n", wn) : 0;
	printf("le champ =%s\n", argv[1]);
	if (ft_strcmp(argv[1], "doom_engine") == 0)
		ft_game_engine(wn);
	else
		turn(wn);
}
