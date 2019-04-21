# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lomasse <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/06 19:24:01 by lomasse           #+#    #+#              #
#    Updated: 2019/04/21 10:53:38 by lomasse          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= doom

BASE_SRC		= main.c										\
				  turn.c

INIT_SRC		= init.c										\
				  parse.c										\
				  initwn.c										\
				  sdl.c											\
				  load.c										\
				  load2.c										\
				  load_intro.c									\
				  texture.c										\
				  skybox.c										\
				  player.c										\
				  init_input.c

GAME_SRC		= input.c										\
				  maingame.c									\
				  show.c

MENU_SRC		= mainmenu.c									\
				  menuinput.c									\
				  show.c										\
				  console.c

EDITOR_SRC		= mainedit.c									\
				  printscreen.c 								\
				  input.c

OPTION_SRC		= mainoption.c									\
				  optioninput.c									\
				  showoption.c									\

TGA_SRC			= data.c										\
				  filldata.c									\
				  createpxl.c									\
				  uncompress.c									\
				  rot.c											\
				  tga_main.c

CINE_SRC		= intro.c										\
				  mainintro.c

BASE_PATH		= ./src/

GAME_PATH		= ./src/game/

EDITOR_PATH		= ./src/editor/

INIT_PATH		= ./src/init/

MENU_PATH		= ./src/menu/

OPTION_PATH		= ./src/option/

TGA_PATH		= ./src/tga/

CINE_PATH		= ./src/cinematique/

OBJ_PATH		= ./OBJ

SRCS			=	$(addprefix $(BASE_PATH), $(BASE_SRC))			\
					$(addprefix $(GAME_PATH), $(GAME_SRC))			\
					$(addprefix $(INIT_PATH), $(INIT_SRC))			\
					$(addprefix $(MENU_PATH), $(MENU_SRC))			\
					$(addprefix $(OPTION_PATH), $(OPTION_SRC))		\
					$(addprefix $(EDITOR_PATH), $(EDITOR_SRC))		\
					$(addprefix $(TGA_PATH), $(TGA_SRC))			\
					$(addprefix $(CINE_PATH), $(CINE_SRC))			\

INC				= -I ./includes

LIB				= -L ./libft/

GCC				= gcc

FLAGS			= -Wall -Wextra -Werror

DEBUG			= -g -fsanitize=address

OBJS			= $(addprefix $(OBJ), $(SRCS:.c=.o))

MAKELIB			= make re -C libft/

LIBFT			= -Llibft/ -lft
LIB_FT			= libft/libft.a

LIBSDL			= -L ./libui -lSDL2 -lSDL2_mixer -lpthread

SDL_DIR			= SDL2-2.0.9
SDL_LIB			= $(SDL_DIR)/build/.libs/libSDL2.a
SDL_INC			= -I ./$(SDL_DIR)/include/

FRAME			= -framework OpenGL -framework AppKit


%.o: %.c ./includes/doom.h ./includes/tga_reader.h ./includes/skybox.h ./includes/player.h
	@$(GCC) $(INC) $(SDL_INC) -o $@ -c $< $(FLAGS)

$(NAME): $(SDL_DIR) $(LIB_FT) $(OBJS)
	@$(GCC) -o $@ `sdl2-config --cflags --libs` $(OBJS) $(LIB) $(LIBFT) $(SDL_INC) $(FRAME) $(FLAGS) $(DEBUG)

$(LIB_FT):
	make -C libft

$(SDL_DIR):
	$(shell tar -xzf ./libui/$(SDL_DIR).tar.gz)
	cd $(SDL_DIR) && ./configure
	cd $(SDL_DIR) && make

all : $(NAME)

clean :
	@rm -rf $(OBJS) ; echo "Obj Cleaned"

fclean : clean
	@rm -rf $(NAME) ; echo "Exec Cleaned"

re : fclean all

.PHONY : all clean fclean re
