/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_map_editor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:35:59 by jchardin          #+#    #+#             */
/*   Updated: 2019/05/09 20:13:35 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

void			ft_quit(char *txt, t_mywin *s_win)
{
	printf("%s\n", txt);
	if (s_win->window[J_EDITOR] != NULL)
		SDL_DestroyWindow(s_win->window[J_EDITOR]);
	if (s_win->renderer[J_EDITOR] != NULL)
		SDL_DestroyRenderer(s_win->renderer[J_EDITOR]);
	SDL_Quit();
	exit(1);
}

void		ft_launch_window(t_mywin *s_win)
{
	s_win->window[J_EDITOR] = NULL;
	s_win->renderer[J_EDITOR] = NULL;
	SDL_Init(SDL_INIT_EVERYTHING);
	if (!(s_win->window[J_EDITOR] = SDL_CreateWindow("J map editor", 10, 10, 600, 400, SDL_WINDOW_SHOWN)))
		ft_quit("Erreur alloc window\n", s_win);
	if (!(s_win->renderer[J_EDITOR] = SDL_CreateRenderer(s_win->window[J_EDITOR],0, SDL_RENDERER_SOFTWARE)))
		ft_quit("Erreur alloc window\n", s_win);
}


void	ft_draw_square(t_mywin *s_win, t_mysquare *s_square)
{
	printf("ft_draw_square\n");

	int i;
	int j;

	SDL_SetRenderDrawColor(s_win->renderer[J_EDITOR], s_square->color.rrr, s_square->color.ggg, s_square->color.bbb, 255);
	j = 0;
	while ((j + s_square->y) < (s_square->y + s_square->height))
	{
		i = 0;
		while ((i + s_square->x) < (s_square->x + s_square->width))
		{
			SDL_RenderDrawPoint(s_win->renderer[J_EDITOR], (i + s_square->x), (s_square->y + j));
			i++;
		}
		j++;
	}
}


void	ft_draw_wall(void)
{
	printf("ft_draw_wall\n");
}

void	ft_save_map(void)
{
	printf("ft_save_map\n");
}

t_mysquare	ft_setsquare(int x, int  y, int  width, int  height, t_mycolor s_color )
{
	t_mysquare	s_square;

	s_square.x = x;
	s_square.y = y;
	s_square.width = width;
	s_square.height = height;
	s_square.color = s_color;
	return (s_square);
}

t_mycolor	ft_setcolor(int rrr, int ggg, int bbb)
{
	t_mycolor	s_color;

	s_color.rrr = rrr;
	s_color.ggg = ggg;
	s_color.bbb = bbb;
	return (s_color);
}

void	ft_draw_cross(t_mywin *s_win, t_mycross *s_cross)
{
	printf("ft_draw_cross\n");
	t_mysquare		s_square1;
	s_square1 = ft_setsquare(s_cross->x - (s_cross->size / 2), s_cross->y, s_cross->size, s_cross->thickness, s_cross->color);
	ft_draw_square(s_win, &s_square1);
	t_mysquare		s_square2;
	s_square2 = ft_setsquare(s_cross->x - (s_cross->thickness / 2), s_cross->y + (s_cross->thickness / 2) - (s_cross->size / 2), s_cross->thickness, s_cross->size, s_cross->color);
	ft_draw_square(s_win, &s_square2);
}

t_mycross	ft_setcross(int x, int y, int size, int thickness, t_mycolor color)
{
	t_mycross	s_cross;

	s_cross.x = x;
	s_cross.y = y;
	s_cross.size = size;
	s_cross.thickness = thickness;
	s_cross.color = color;
	return (s_cross);
}

t_mywrite	ft_setwrite(int x, int y, t_mycolor color, int size, char *str)
{
	t_mywrite	s_write;

	s_write.x = x;
	s_write.y = y;
	s_write.str = ft_strdup(str);
	TTF_Init();
	s_write.color = color;
	s_write.font = TTF_OpenFont("./OpenSans-Bold.ttf", size);
	if (!s_write.font)
		printf("TTF_OpenFont: %s\n", TTF_GetError());
	return (s_write);
}

void	ft_write(t_mywin *s_win, t_mywrite *s_write)
{
	printf("ft_write\n");

	SDL_Surface	*surface;
	SDL_Color color;

	color.r = s_write->color.rrr;
	color.g = s_write->color.ggg;
	color.b = s_write->color.bbb;
	surface = TTF_RenderText_Solid(s_write->font, s_write->str, color);

	SDL_Texture	*texture;
	texture = SDL_CreateTextureFromSurface(s_win->renderer[J_EDITOR], surface);

	int	w;
	int	h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	SDL_Rect	rect;
	rect.x = s_write->x;
	rect.y = s_write->y;
	rect.w = w;
	rect.h = h;
	SDL_RenderCopy(s_win->renderer[J_EDITOR], texture, NULL, &rect);
	TTF_CloseFont(s_write->font);
	TTF_Quit();
}

int		ft_get_number_of_line(void)
{
	int			nbr_line;
	int			fd;
	char		*line;

	line = NULL;

	nbr_line = 0;
	fd = open("./src/jeronemo/file_wall", O_RDWR);
	while(get_next_line(fd, &line))
		nbr_line++;
	close(fd);
	return (nbr_line);
}


int		ft_get_next_value(char *line, int *j)
{
	int k;
	char		nbr[100];

	k = 0;
	while( !ft_isdigit(line[*j]) )
		*j = *j + 1;
	while(ft_isdigit(line[*j]))
	{
		nbr[k] = line[*j];
		*j = *j + 1;
		k++;
	}
	nbr[k] = '\0';
	//printf("la value =%d\n", ft_atoi(nbr));
	return (ft_atoi(nbr));
}

t_mywall	*ft_read_map(void)
{
	printf("ft_read_map\n");
	int			fd;
	char		*line;
	int			nbr_line;
	t_mywall	*s_wall;
	int			i;
	int			j;

	line = NULL;
	nbr_line = ft_get_number_of_line();
	s_wall = (t_mywall*)malloc(sizeof(t_mywall) * nbr_line);
	fd = open("./src/jeronemo/file_wall", O_RDWR);
	i = 0;
	while(get_next_line(fd, &line))
	{
		j = 0;
		//printf("%s\n", line);
		s_wall[i].x_a = ft_get_next_value(line, &j);
		s_wall[i].y_a = ft_get_next_value(line, &j);
		s_wall[i].x_b = ft_get_next_value(line, &j);
		s_wall[i].y_b = ft_get_next_value(line, &j);
		s_wall[i].height = ft_get_next_value(line, &j);
		s_wall[i].texture = ft_get_next_value(line, &j);
		i++;
	}
	close(fd);
	return (s_wall);
}

void	ft_draw_grid(void)
{
	printf("ft_draw_grid\n");
}

void	ft_launch_map_editor(t_mywin *s_win)
{
	ft_launch_window(s_win);
	SDL_SetRenderDrawColor(s_win->renderer[J_EDITOR], 0, 0, 0, 255);
    SDL_RenderClear(s_win->renderer[J_EDITOR]);
	//t_mycolor		s_color;
	//	SQUARE
	//	s_color = ft_setcolor(255, 255, 255);
	//	t_mysquare		s_square;
	//	s_square = ft_setsquare(10, 10, 100, 100, s_color);
	//	ft_draw_square(s_win, &s_square);
	// CROSS
	//	s_color = ft_setcolor(0, 255, 0);
	//	t_mycross		s_cross;
	//	s_cross = ft_setcross(100, 100, 50, 10, s_color);
	//	ft_draw_cross(s_win, &s_cross);
	//WRITE
	//	s_color = ft_setcolor(0, 0, 255);
	//	t_mywrite	s_write;
	//	s_write = ft_setwrite(10, 10, s_color, 24, "ma phrase");
	//	ft_write(s_win, &s_write);
	//READMAP
	//t_mywall	*s_wall;
	//s_wall = ft_read_map();
	//DRAW GRID
	ft_draw_grid();

	ft_save_map();
	ft_draw_wall();
	SDL_RenderPresent(s_win->renderer[J_EDITOR]);
}

void	ft_jeronemo(t_win *wn)
{
	(void)wn;
	t_mywin	s_win;

	printf("hello chef inca\n");
	ft_launch_map_editor(&s_win);
	int i = 1;
	while(i)
		SDL_Delay(10);
	ft_quit("je quite\n", &s_win);
}
