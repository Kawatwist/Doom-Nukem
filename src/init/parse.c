/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:02:47 by lomasse           #+#    #+#             */
/*   Updated: 2019/04/20 13:29:36 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		parsearg(int argc, char **argv, t_win **wn)
{
	if (argc == 1)
	{
		ft_putstr("Wesh besoin de plus d'arg\n");
		return (0);
	}
	else if (argc >= 3)
	{
		ft_strcmp(argv[2], "DEBUG") == 0 ? (*wn)->debug = 1 : 0;
		ft_strcmp(argv[2], "EASY") == 0 ? (*wn)->difficulty = 0 : 0;
		ft_strcmp(argv[2], "HIGH") == 0 ? (*wn)->difficulty = 2 : 0;
		ft_strcmp(argv[2], "HARDCORE") == 0 ? (*wn)->difficulty = 3 : 0;
		ft_strcmp(argv[2], "DEATH") == 0 ? (*wn)->difficulty = 4 : 0;
		ft_strcmp(argv[2], "LQ") == 0 ? (*wn)->quality = 1 : 0;
		if (argc > 3)
			ft_strcmp(argv[3], "CONSOLE") == 0 ? (*wn)->debug = 1 : 0;
	}
	return (1);
}
