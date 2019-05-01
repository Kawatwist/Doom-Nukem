/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:14:06 by lomasse           #+#    #+#             */
/*   Updated: 2019/04/24 19:11:30 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include <stdlib.h>
# include <math.h>
# include <pthread.h>
# include "libft.h"
# include "game.h"
# include "skybox.h"
# include "SDL.h"
# include "SDL_ttf.h"


# define XSCREEN 1500
# define YSCREEN 1200

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

typedef struct		s_elem
{
	char			*name;
	int				x1;
	int				x2;
	int				y1;
	int				y2;
	int				*pos;
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

typedef struct		s_thread
{
	pthread_t		thd;
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
	int				x;
	int				y;
}					t_input;

typedef struct		s_win
{
	char			difficulty;
	char			quality;
	char			debug;
	char			interface;
	char			oldinterface;
	char			*tmp[4];
	char			*command;
	char			**history;
	int				load;
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
	t_cloud			*cloud;
	t_menu			*menu;

	int				debugconsole;

}					t_win;

/**
 ** GAME
 **/
void				display_skybox(t_win *wn);

/**
 ** EDIT
 **/
void				edit(t_win *wn);
void				inputeditor(t_win *wn);
void				printeditor(t_win *wn);

void				mainconsole(t_win *wn);

/**
 ** INIT
 **/
t_text				*findpostxt(t_win *wn, char *type,
						char *subtype, char *name);
t_text				*findpos(t_win *wn, char *type,
						char *subtype, char *name);
int					parsearg(int argc, char **argv, t_win **wn);
void				showload(t_win **wn, int load);
int					init(t_win **wn, int argc, char **argv);
void				initwn(t_win **wn);
void				initsdl(t_win **wn);
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
void				turn(t_win *wn);
void				game(t_win *wn);
void				gameinput(t_win *wn);
void				setkeyboard(Uint8 *new, Uint8 *current);
void				stop_exec(char *msg, t_win *wn);

#endif
