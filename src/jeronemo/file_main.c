/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:55:47 by jchardin          #+#    #+#             */
/*   Updated: 2019/07/08 14:31:13 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <jeronemo.h>

void			ft_quit(char *txt, t_mywin *s_win)
{
//	printf("%s\n", txt);
//	if (s_wn->window[J_EDITOR] != NULL)
//		SDL_DestroyWindow(s_win->window[J_EDITOR]);
//	if (s_win->renderer[J_EDITOR] != NULL)
//		SDL_DestroyRenderer(s_win->renderer[J_EDITOR]);
//	SDL_Quit();
//	exit(1);
(void)txt;
(void)s_win;
}

t_mycolor	ft_setcolor(int rrr, int ggg, int bbb)
{
	t_mycolor	s_color;

	s_color.rrr = rrr;
	s_color.ggg = ggg;
	s_color.bbb = bbb;
	return (s_color);
}

void	ft_game_engine(t_win *wn)
{
	t_mywin		s_win;
	int			choice;

	choice = 0;
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
