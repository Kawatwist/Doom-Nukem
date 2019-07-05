/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:55:47 by jchardin          #+#    #+#             */
/*   Updated: 2019/07/05 19:05:56 by pi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <jeronemo.h>

void	ft_game_engine(t_win *wn)
{
	t_mywin		s_win;

	/* while (1) */
	/* { */
		system("@cls||clear");
		printf("Hello chef inca\n");
		printf("GAME ENGINE MENU\n");
		printf("=> 1 <= Map editor\n");
		printf("=> 2 <= BSP Generator\n");
		printf("=> 3 <= Graphic engine\n");
		printf("=> 4 <= QUIT\n");
		printf("\n");
		printf("Please make your choice\n");
		/* scanf("%d", &choice); */
		/* if (choice == 1) */
			/* ft_launch_map_editor(&s_win, wn); */
		/* else if (choice == 2) */
			/* ft_launch_bsp_tree(&s_win, wn); */
		/* else if (choice == 3) */
			ft_launch_rasterization(&s_win, wn);
		/* else if (choice == 4) */
			ft_quit("je quite\n", &s_win);
	/* } */
}
