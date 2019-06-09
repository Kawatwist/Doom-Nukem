/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:14:06 by lomasse           #+#    #+#             */
/*   Updated: 2019/06/08 17:01:22 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include <stdlib.h>
# include <math.h>
# include <pthread.h>
# include "libft.h"
# include "game.h"
# include "rasterisation.h"
# include "skybox.h"
# include "SDL.h"
# include "SDL_ttf.h"

# include <SDL2/SDL.h>
# include <SDL_image.h>

//# define XSCREEN 1500
//# define YSCREEN 1200
# define XSCREEN 1920
# define YSCREEN 1080
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
	GAME,
	MGAME,
	NGAME,
	LGAME,
	RGAME,
	EDITEUR,
	MEDITEUR,
	LEDITEUR,
	NEDITEUR,
	REDITEUR,
	OPTION,
	BOPTION,
	KEYOPTION,
	LOADING,
	PAUSE,
}					t_interface;

typedef struct		s_myvec
{
	float			x;
	float			y;
	float			z;
	int				obj_indice;
	struct s_myvec	*next;
}					t_myvec;

typedef struct		s_point
{
	int				x;
	int				y;
	struct s_point	*next;
}					t_point;

typedef struct		s_elem
{
	t_point			*point;
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
}					t_thread;

typedef struct		s_menu
{
	int				choice;
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

typedef struct 		s_console
{
	char			**history;
	int				index;
}					t_console;

typedef struct  	s_fonts
{
	TTF_Font		*ariel;
} 					t_fonts;

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
	t_rast			*rast;
	int 			xscreen;
	int 			yscreen;
}					t_win;

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
 ** EDIT
 **/
void				edit(t_win *wn);
void				inputeditor(t_win *wn);
void				printeditor(t_win *wn);

void				mainconsole(t_win *wn);
void				inputconsole(t_win *wn);
void				print_text_with_ariel_font(t_win *wn, char *s, SDL_Color color, SDL_Rect position);
void				print_command(t_win *wn, char *s, int posi_x, int posi_y);


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
void				main_input(t_win *wn);
void				turn(t_win *wn);
void				game(t_win *wn);
void				gameinput(t_win *wn);
void				setkeyboard(Uint8 *new, Uint8 *current);
void				stop_exec(char *msg, t_win *wn);
void				full_screen(t_win *wn);
Uint32				set_bit(Uint32 var, Uint32 mask);
int					key_pressed(t_win *wn, int key_value);




/**
 ** jeronemo game engine
 **/

void	ft_game_engine(t_win *wn);
#endif
