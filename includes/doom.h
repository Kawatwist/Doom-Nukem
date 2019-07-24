/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:14:06 by lomasse           #+#    #+#             */
/*   Updated: 2019/07/10 17:53:57 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include <stdlib.h>
# include <math.h>
# include <pthread.h>
# include <libft.h>
# include <game.h>
# include <rasterisation.h>
# include <skybox.h>
# include <SDL.h>
# include <SDL_ttf.h>

# include <SDL2/SDL.h>
# include <SDL_image.h>

//# define XSCREEN 1500
//# define YSCREEN 1200
# define XSCREEN 1920
# define YSCREEN 1080
# define TIMEOUT 5000
# define CONSOLE_MAX_LINE_NB 10
# define ARIEL_FONT_SIZE 35
# define U_MAX		4294967295
# define LQ			1 << 0
# define FS			1 << 1
# define CINE		1 << 2
# define CONSOLE	1 << 3
# define SKY        1 << 16
# define DIFFICULTY 1 << 18
# define SKY2		1 << 20


# define WHITE 255, 255, 255
# define RED 255, 0, 0
# define GREEN 0, 255, 0
# define BLUE 0, 0, 255
# define BLACK 0, 0, 0
# define PINK 255, 0, 255
# define YELLOW 255, 255, 0
# define ORANGE 255, 128, 0
# define TURQUOISE 0, 255, 255
# define WHITE 255, 255, 255



typedef enum		e_bool
{
	FALSE = 0,
	TRUE = 1,
}					t_bool;

typedef enum  		e_val
{
	INVALID = -1,
}					t_val;

typedef enum		e_interface
{
	MENU,
	MGAME,
	NGAME,
	LGAME,
	DGAME,
	RGAME,
	EDITEUR,
	MEDITEUR,
	LEDITEUR,
	NEDITEUR,
	REDITEUR,
	MOPTION,
	COPTION,
	GOPTION,
	KOPTION,
	LOADING,
	PAUSE,
	GAME_ENGINE,
	GAME_EDITOR,
	MULTI,
	CLIENT,
	HOST,
}					t_interface;

typedef struct		s_myvec
{
	float			x;
	float			y;
	float			z;
	float			w;
	int				obj_indice;
	float			shade;
	struct s_myvec	*next;
}					t_myvec;

typedef struct		s_point
{
	float				x;
	float				y;
	float 				z;
	struct s_point	*next;
}					t_point;

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

typedef struct		s_text
{
	char			*type;
	char			*subtype;
	char			*name;
	SDL_Texture		*txt;
	struct s_text	*next_type;
	struct s_text	*next_subtype;
	struct s_text	*next;
	struct s_text	*before;
}					t_text;

typedef struct		s_load
{
	char			*path;
	char			*type;
	char			*subtype;
	char			*name;
	void			*tga;
	t_text			*txt;
	struct s_load	*next;
}					t_load;

typedef struct		s_thread
{
	pthread_t		thd;
	t_load			*file;
	struct s_win	*wn;
	int				value;
	char			*str;
}					t_thread;

typedef struct		s_menu
{
	int				ask;
	int				choice;
	int				connected;
	void			*conv[3];
}					t_menu;

typedef	struct		s_input
{
	Uint32			mouse;
	Uint32			oldmouse;
	int				x;
	int				y;
}					t_input;

typedef struct		s_mut
{
	int				load;
	void			*next;
	pthread_cond_t	condition;
	pthread_mutex_t	mutex;
}					t_mut;

typedef struct 		s_color
{
	SDL_Color		noir;
	SDL_Color 		violetfonce;
	SDL_Color		violet;
	SDL_Color		violetrose;
	SDL_Color 		red;
	SDL_Color 		blanc;
}					t_color;

typedef struct 		s_loadbgmap
{
	char 			*path;
} 					t_bg_map;

typedef struct 		s_texture_editor
{
	SDL_Texture 	*texture_tools;
	int 			bgh;
	SDL_Texture 	*texture_bgh;
	SDL_Texture 	*bg_path;
	SDL_Rect		bg;
	SDL_Rect 		pos_path;
	int 			in;
	int 			tbp;
	SDL_Texture 	*texture_tbp;
	SDL_Texture 	*fleche;
}					t_edit;

typedef struct 		s_written
{
	SDL_Surface 	*surface;
	SDL_Texture 	*texture_x;
	SDL_Texture 	*texture_y;
	SDL_Texture 	*texture_z;
	int 			val_z;
	SDL_Rect 		src;
	int 			on;
	int 			map_h;
	int 			map_w;
}					t_written;

typedef struct 		s_var_edit
{
	int 			nb_point;
}					t_var_edit;

typedef struct 		s_bresenham 
{
	int 			x;
	int 			y;
	int 			x1;
	int 			y1;
	int 			dx;
	int 			dy;
	int 			sx;
	int 			sy;
	int 			e;
}					t_bres;

typedef struct 		s_console
{
	char			**history;
	int				index;
}					t_console;

typedef struct  	s_fonts
{
	TTF_Font		*ariel;
	TTF_Font  		*arial;
	TTF_Font 		*arial_path;
} 					t_fonts;

//JEROME

typedef struct				s_mycolor
{
	int						rrr;
	int						ggg;
	int						bbb;
}							t_mycolor;

typedef struct				s_mytriangle
{
	t_myvec					vertice[3];
	struct s_mytriangle		*next;
	char					ft_color;
	float					shade;
}							t_mytriangle;

typedef struct				s_mypolygon
{
	int						obj_indice;
	t_myvec					*vertex_lst;             //liste des vertex
	t_myvec					normal;                  //la normal au polygon
	int						number_of_vertex;        //nombre de vertex
	int						number_of_indices;       //nombre d'indices
	int						*indices;                //la listes des indices apres triangulasisation
	struct s_mypolygon		*next;                   //le prochain noeud dans la liste
}							t_mypolygon;
// FIN JEROME
//
typedef struct		s_rasterizer
{
	int				max;
	void			*tmp;
	t_mytriangle	*tmp2;
	t_mypolygon		*tmp3;
}					t_rasterizer;

typedef struct		s_win
{
	Uint32			flag;
	char			sky;		//flag => 2
	char			difficulty; //flag => 2
	char			interface;
	char			oldinterface;
	t_console		*console;
	t_fonts			*fonts;  //structure poour stocker tous les polices de caracteres
	char			*load;
	int				turn;
	Uint8			*state;
	Uint8			*old;
	t_input			*input;
	SDL_Event		ev;
	SDL_Window		*window;
	SDL_Renderer	*rend;
	t_text			*texture;
	SDL_Texture		*txtnotload;
	SDL_Texture		*loading;
	SDL_Texture		*loadingscreen;
	t_map			*map;
	t_elem			*elem;
	t_joueur		*player;
	t_cloudy		*cloud;
	t_menu			*menu;
	t_mut			*mutex;
	t_poly			*poly;
	t_mypolygon 	*mypoly;
	t_rast			*rast;
	int 			xscreen;
	int 			yscreen;
	int 			full_screen;
	t_color			color;
	int				debugconsole;
	t_written 		editext;
	t_edit 			edit_image;
	t_bres 			bres;
	t_bg_map 		bg_map;
	t_var_edit 		varedit;
	t_rasterizer	*rasterizer;
	void			*serv;
	void			*client;
}					t_win;


/**
 ** JERONEMO.H
 **/

// MODIF
void						ft_launch_rasterization(t_win *wn);
void						turn_rast(t_win *wn);
//



t_mycolor					ft_setcolor(int rrr, int ggg, int bbb);
void						ft_launch_bsp_tree(t_mypolygon *polygon_lst);
float						ft_dot_product(t_myvec v1, t_myvec v2);
t_myvec						ft_cross_product(t_myvec v1, t_myvec v2);
int							ft_abs(int number);
float						ft_atoi_comma(const char *str);

//commun
t_myvec						ft_calculate_normal_of_points(t_myvec vertex1, t_myvec vertex2, t_myvec vertex3);





/**
 ** GAME
 **/

void				ingame(t_win *wn);
void				game_interface(t_win *wn);
void				newgame(t_win *wn);
void				new_game_input(t_win *wn);
void				loadgame(t_win *wn);
void				load_game_input(t_win *wn);
void				menugame(t_win *wn);
void				menu_game_input(t_win *wn);
void				show_game_cursor(t_win *wn);
void				game_interface(t_win *wn);
void				maindrawpoly(t_win *wn);
void				main_cloud(t_win *wn);
void				init_cloud(t_cloudy *cloud);
void				display_skybox(t_win *wn);
void				display_crosshair(t_win *wn);
void				trans(t_win *wn, double **mat);
void				rotatex(double ang, double **mat);
void				rotatey(double ang, double **mat);
void				rotatez(double ang, double **mat);
void				initmatrice(double **matrice);
void				calc_fsu(t_win *wn, t_vec *ver, t_poly *curr);
void				world2view(t_win *wn, t_vec *ver, t_vec *f, t_vec *s, t_vec *u);

/**
 ** MULTI
 **/

void				stop_com(t_win *wn, int user);
void				add_chat(t_win *wn, int user);
int					chat_box(t_win *wn, char *msg);
void				send_msg_from_client(t_win *wn, char *msg);
void				send_msg_from_server(t_win *wn, char *msg, int user);
char				*get_msg_client(t_win *wn);
char				*get_msg_server(t_win *wn, int user);
void				mainhost(t_win *wn);
void				mainclient(t_win *wn);
void				mainmulti(t_win *wn);

/**
 ** EDIT
 **/
void				edit(t_win *wn);
void				inputeditor(t_win *wn);
void				printeditor(t_win *wn);
void				load_color(t_win *wn);
SDL_Color			making_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
void				print_x_y_z(t_win *wn);
void 				create_text_texture(t_win *wn, SDL_Texture *texture, int x, SDL_Color color);
void				init_edit(t_win **wn);
void 				which_cursor(t_win *wn);
void 				print_background_editor(t_win *wn);
void 				print_tools_editor(t_win *wn);
void				print_bgh_editor(t_win *wn);
void				print_tbp_editor(t_win *wn);
void 				change_bloc(t_win *wn);
void 				print_arrow(t_win *wn);
void 				stop_editor(t_win *wn);
void				init_bres(t_win *wn, t_point *alst, t_point *next);
void				bres_x(t_win *wn);
void 				bres_y(t_win *wn);
void				bresenham(t_win *wn, t_point *alst, t_point *next);
t_point 			create_t_point(int x, int y);
void 				showmap(t_win *wn);
int 				mouse_pressed(t_win *wn, Uint32 Mask);
int           		check_point(t_win *wn, t_point *point);
void         		mouse_input_poly(t_win *wn);
void				bg_or_h(t_win *wn);
void 				print_bg(t_win *wn);
void				print_path(t_win *wn, char *s, int posi_x, int posi_y);
void				print_text_with_arial_path(t_win *wn, char *s, SDL_Color color, SDL_Rect position);
SDL_Rect			define_rect(int x, int y, int w, int h);
void				print_text_with_arial_font(t_win *wn, char *s, SDL_Color color, SDL_Rect position);
void				print_text_with_arial_path_full(t_win *wn, char *s, SDL_Color color, SDL_Rect position);
void 				message_bg_editor(t_win *wn, char *message);
void 				load_background(t_win *wn);
// int 				is_path_ok(t_win *wn, char *path);
void   				find_last_poly(t_elem **curr);
void     			find_last_point(t_win *wn, t_point **point);
t_mypolygon		 	*polygon_map(t_win *wn);
t_poly 				*poly_map(t_win *wn);
int 				pop_up_message(t_win *wn, char *msg, SDL_Rect *rect);
void 				print_save_and_reset(t_win *wn);
void 				print_message(t_win *wn, char *msg);



/**
 ** MENU
 **/
void				print_one_line(t_win *wn, char *s, int	posy_x, int posi_y);
void				mainconsole(t_win *wn);
void				inputconsole(t_win *wn);
void				print_text_with_ariel_font(t_win *wn, char *s, SDL_Color color, SDL_Rect position);
void				print_command(t_win *wn, char *s, int posi_x, int posi_y);
char				printable_key_check(t_win *wn, int i);
char				*printable_input(t_win *wn, char *command);

/**
 ** INIT
 **/

void				initttf(t_win **wn);
void				init_ver(t_vec *vec, float x, float y, float z);
t_text				*findpostxt(t_win *wn, char *type,
						char *subtype, char *name);
t_text				*findpos(t_win *wn, char *type,
						char *subtype, char *name);
int					parsearg(int argc, char **argv, t_win **wn);
void				loadminimenu(t_win **wn);
void				showload(t_win **wn, int load);
int					init(t_win **wn, int argc, char **argv);
void				initwn(t_win **wn);
void				initsdl(t_win **wn);
void				init_poly(t_win **wn);
void				init_rast(t_win **wn);
void				init_input(t_win **wn);
void				initskybox(t_win **wn);
void				initplayer(t_win **wn);
int					load_texture(t_win *wn, char *type,
						char *subtype, char *name);
void				*load_intro(void *params);
void				inittexture(t_win **wn);
SDL_Texture			*initload2(t_win **wn, const char *path);
void				showlinkedlist(t_win **wn, char *type, char *subtype);
void				initload(t_win **wn);
SDL_Texture			*findtexture(t_win *wn, char *type,
						char *subtype, char *name);
int					initmutex(t_win **wn);
void				*loadingthread(void *param);
void				loadnothread(t_win **wn);
void				load_fonts(t_win *wn);



/**
 ** OPTION
 **/
void				keyboardoption(t_win *wn);
void				graphismeoption(t_win *wn);
void				controloption(t_win *wn);
void				menuoption(t_win *wn);
void				menu_option_input(t_win *wn);
void				option(t_win *wn);
void				optioninput(t_win *wn);
void				showoption(t_win *wn);

/**
 ** CINE
 **/
char				*changename(char *name, int place);
void				showintro(t_win *wn, t_text *img);
void				showreverseintro(t_win *wn, t_text *img);
void				mainintro(t_win *wn, char *type, char *subtype, int pose);
void				intro(t_win *wn);
void				menu(t_win *wn);
void				menuinput(t_win *wn);
void				showmenu(t_win *wn);

/**
 ** MAIN
 **/

char				*text_box(t_win *wn, char *line);
void				main_input(t_win *wn);
void				turn(t_win *wn);
void				game(t_win *wn);
void				gameinput(t_win *wn);
void				setkeyboard(Uint8 *new, Uint8 *current);
void				stop_exec(char *msg, t_win *wn);
void				full_screen(t_win *wn);
SDL_Rect			*create_rect(int x, int y, int w, int h);
int					hitbox(int x, int y, SDL_Rect *pos);
Uint32				set_bit(Uint32 var, Uint32 mask);
int					mouse_pressed(t_win *wn, Uint32 mask);
int					key_pressed(t_win *wn, int key_value);




/**
 ** jeronemo game engine
 **/

void	ft_game_engine(t_win *wn);
#endif
