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

typedef enum		e_flag
{
	WRITE = 1,
	LOCK = 2,	//BG FOLLOW MAP
	MAP = 4,	//ONLY MAP or ONLY BG

}					t_flag;

typedef enum		e_cursor
{
	CURSOR = 0,
	SELECT = 1,
	WAND = 2,
	DRAW = 3,
	FORM = 4,
	ERASE = 5,
	ZOOM = 6,
	RESIZE = 7,
	ROTATE = 8, // NO KEYBOARD INPUT ENABLE
	HAND = 9,
	SWAP = 10,
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
	char			*name;
}					t_map;

typedef struct 		s_loadbg
{
	char 			*path;
	int				x; // Pos of texture x
	int				y;
	int				w;
	int				h;
	float			size;
	char			flag; // active mouvement + write enable
} 					t_loadbg;

typedef struct 		s_tab
{
	SDL_Texture 	*texture_tools;
	SDL_Texture 	*texture_bgh;
	SDL_Texture 	*texture_tab;
	SDL_Texture 	*bg_pics;
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
	int 			on;
	int				w;
	int				h;
	int 			find;
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
	t_point			**center;	// SHOW CENTER
	void			(*cursor_fct[11]) (t_win *wn, struct s_edit *edit);
}					t_edit;

void    			ft_ftoafd(float nbr, int fd);
void        		save_panel(t_win *wn, t_edit *edit);

t_point				**addtmptoselection(t_point **tmp, t_point **select);
t_point     		**cpy_elem_selected(t_elem *elem);
t_point				*find_center_linked(t_elem **lst);
t_point				*find_center(t_point **lst);

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
void				rotate_cursor(t_win *wn, t_edit *edit);

void				check_hitbox(t_win *wn, t_edit *edit);

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
void   				find_last_poly(t_elem **curr);
void     			find_last_point(t_edit *edit, t_point **point);
t_mypolygon		 	*polygon_map(t_win *wn);
t_poly 				*poly_map(t_win *wn);
t_popup				param_pop_up(char *question, char *yes, char *no, SDL_Rect *rect);
int 				pop_up_message(t_win *wn, t_popup popup);
void 				print_save_and_reset(t_win *wn, t_edit *edit);
void 				print_message(t_win *wn, char *msg, SDL_Color color);
void				display_tab(t_win *wn, t_edit *edit);
void    			exec_tab(t_win *wn, t_edit *edit);
void				resetmap(t_win *wn, t_edit *edit);
void				remove_poly(t_elem *curr);
void				display_slider(t_win *wn, SDL_Rect rect, SDL_Texture *texture);
void   				info_bar(t_win *wn, t_edit *edit);
void    			draw_to_find_position(t_win *wn, t_edit *edit);
SDL_Texture			*print_coor(t_win *wn, t_edit *edit);
void 				zoom_mouse_map(t_win *wn, t_edit *edit, int zoom);
void 				test_slider(t_win *wn);

#endif
