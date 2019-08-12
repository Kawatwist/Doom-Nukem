/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llejeune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 16:48:09 by llejeune          #+#    #+#             */
/*   Updated: 2019/08/06 19:59:33 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H

# include <doom.h>

typedef enum		e_cursor
{
	CURSOR = 0,
	DRAW = 1,
	ERASE = 2,
	ZOOM = 3,
	HAND = 4,
	SELECT = 5,
	WAND = 6,
	FORM = 7,
	SWAP = 8,
	RESIZE = 9,
}					t_cursor;

typedef struct		s_elem
{
	t_point			*point;
	int 			nb_pt;
	struct s_elem	*next;
}					t_elem;

typedef struct		s_map
{
	float			w;
	float			h;
	float			x;
	float			y;
	float			size;
}					t_map;

typedef struct 		s_loadbg
{
	char 			*path;
} 					t_loadbg;

typedef struct 		s_tab
{
	SDL_Texture 	*texture_tools;
	SDL_Texture 	*texture_bgh;
	SDL_Texture 	*texture_tab;
	SDL_Texture 	*bg_path;
	SDL_Texture 	*fleche;
	SDL_Rect		bg;
	SDL_Rect 		pos_path;
	SDL_Rect 		arrow;
	SDL_Rect 		tab;
	int 			bgh;
	int 			in;
	int 			onglet;
}					t_tab;

typedef struct 		s_indice
{
	SDL_Surface 	*surface;
	SDL_Texture 	*texture_x;
	SDL_Texture 	*texture_y;
	SDL_Texture 	*texture_z;
	SDL_Rect 		src;
	int 			val_z;
	int 			on;
	int 			map_h;
	int 			map_w;
}					t_indice;

typedef struct 		s_var
{
	int				cursor;
	int				swapvar;
	int 			nb_point;
	int 			map_saved;
}					t_var;

typedef struct 		s_edit
{
	t_map 			*map;
	t_elem 			*elem;
	t_loadbg 		*loadbg;
	t_tab 			*tab;
	t_indice 		*indice;
	t_var 			*var;
	t_point			**selected;
	void			(*cursor_fct[10]) (t_win *wn, struct s_edit *edit);
}					t_edit;

void				cursor(t_win *wn, t_edit *edit);
void				draw_cursor(t_win *wn, t_edit *edit);
void				erase_cursor(t_win *wn, t_edit *edit);
void				zoom_cursor(t_win *wn, t_edit *edit);
void				hand_cursor(t_win *wn, t_edit *edit);
void				select_cursor(t_win *wn, t_edit *edit);
void				wand_cursor(t_win *wn, t_edit *edit);
void				form_cursor(t_win *wn, t_edit *edit);
void				swap_cursor(t_win *wn, t_edit *edit);
void				resize_cursor(t_win *wn, t_edit *edit);

t_point				**find_box_point(t_win *wn, t_edit *edit, SDL_Rect box);
t_point				*find_point_before(t_win *wn, t_edit *edit);
t_point				*find_closer_point(t_win *wn, t_edit *edit);
void				inputeditor(t_win *wn);
void				printeditor(t_win *wn);
SDL_Color			making_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
void				print_x_y_z(t_win *wn, t_edit *edit);
void 				create_text_texture(t_win *wn, SDL_Texture *texture, int x, SDL_Color color);
void 				which_cursor(t_win *wn, t_edit *edit);
void 				print_background_editor(t_win *wn);
void 				print_tools_editor(t_win *wn, t_edit *edit);
void				print_bgh_editor(t_win *wn, t_edit *edit);
void				print_tab_editor(t_win *wn, t_edit *edit);
void 				change_bloc(t_win *wn, t_edit *edit);
t_point 			create_t_point(int x, int y);
void 				showmap(t_win *wn, t_edit *edit);
int 				mouse_pressed(t_win *wn, Uint32 Mask);
int           		check_point(t_win *wn, t_point *point);
void         		mouse_input_poly(t_win *wn, t_edit *edit);
void				bg_or_h(t_win *wn, t_edit *edit);
void 				print_bg(t_win *wn, t_edit *edit);
void				print_path(t_win *wn, char *s, int posi_x, int posi_y);
void				print_text_with_arial_path(t_win *wn, char *s, SDL_Color color, SDL_Rect position);
SDL_Rect			define_rect(int x, int y, int w, int h);
void				print_text_with_arial_font(t_win *wn, char *s, SDL_Color color, SDL_Rect position);
void				print_text_with_arial_path_full(t_win *wn, char *s, SDL_Color color, SDL_Rect position);
void 				message_bg_editor(t_win *wn, t_edit *edit, char *message);
void 				load_background(t_win *wn);
// int 				is_path_ok(t_win *wn, char *path);
void   				find_last_poly(t_elem **curr);
void     			find_last_point(t_edit *edit, t_point **point);
t_mypolygon		 	*polygon_map(t_win *wn);
t_poly 				*poly_map(t_win *wn);
int 				pop_up_message(t_win *wn, char *msg, SDL_Rect *rect);
void 				print_save_and_reset(t_win *wn, t_edit *edit);
void 				print_message(t_win *wn, char *msg, SDL_Color color);
void				display_tab(t_win *wn, t_edit *edit);
void    			exec_tab(t_win *wn, t_edit *edit);
void		resetmap(t_edit *edit)

#endif
