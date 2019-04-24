# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lomasse <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/06 19:24:01 by lomasse           #+#    #+#              #
#    Updated: 2019/04/09 17:52:24 by lomasse          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= doom

HEADER 			= $(shell find includes -type f) $(shell find libraries/include -type f)

SRC_PATH		= $(shell find src -type d)

INC_PATH 		= $(shell find includes -type d) $(shell find libft -type d) $(shell find libraries/include -type d) \

OBJ_PATH		= OBJ

SRC				= main.c										\
				  turn.c 										\
				  init.c										\
				  parse.c										\
				  initwn.c										\
				  sdl.c											\
				  load.c										\
				  load2.c										\
				  load_intro.c									\
				  texture.c										\
				  maingame.c 									\
				  mainmenu.c									\
				  menuinput.c									\
				  game_show.c 									\
				  mainedit.c									\
				  printscreen.c 								\
				  mainoption.c									\
				  optioninput.c									\
				  showoption.c									\
				  data.c										\
				  filldata.c									\
				  createpxl.c									\
				  uncompress.c									\
				  rot.c											\
				  tga_main.c 									\
				  intro.c										\
				  mainintro.c 									\
				  editor_input.c 								\
				  game_input.c 									\
				  skybox.c 										\
				  init_input.c 									\
				  player.c 										\
				  console.c 									\
				  menu_show.c 									\

OBJ 			= $(addprefix $(OBJ_PATH)/, $(SRC:%.c=%.o))

LIBS 			= SDL2 SDL2_mixer SDL2_ttf freetype ft

LIB_PATH 		= ./libft \
				  ./libraries/lib \

FRAMEWORK 		= OpenGL AppKit

CC 				= gcc

vpath %.c $(foreach dir, $(SRC_PATH), $(dir):)

IFLAG			= $(foreach dir, $(INC_PATH), -I$(dir) )

CFLAG 			= -Wall -Wextra -Werror

LFLAG 			= $(foreach dir, $(LIB_PATH), -L $(dir) ) $(foreach lib, $(LIBS), -l$(lib) ) $(foreach fmw, $(FRAMEWORK), -framework $(fmw) ) \

LIBFTA			= ./libft \

IMAGE 			= ./libraries \

DEBUG			= -g -fsanitize=address

all: $(NAME)

$(NAME): $(IMAGE) $(OBJ)
	$(CC) $(CFLAG) -o $(NAME) $(OBJ) $(LFLAG)

$(OBJ_PATH)/%.o: %.c $(HEADER) $(LIBFTA)
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAG) -o $@ -c $< $(IFLAG)

$(IMAGE): FORCE
	make image

$(LIBFTA): FORCE
	make -C libft

FORCE:

clean :
	@rm -rf $(OBJ)

fclean : clean
	@rm -rf $(NAME)

re : fclean all

relib:
	make re -C libft

resdl:
	rm -rf ./libraries
	make image

image: libraries/lib/libSDL2_mixer.dylib

libraries/lib/libSDL2_mixer.dylib: libraries/lib/libSDL2_ttf.dylib
	mkdir -p libraries
	cd libraries && curl https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-2.0.4.tar.gz -O
	tar -xf ./libraries/SDL2_mixer-2.0.4.tar.gz -C libraries
	cd libraries/SDL2_mixer-2.0.4 ; ./configure --prefix=$(shell pwd)/libraries
	make -C ./libraries/SDL2_mixer-2.0.4
	make -C ./libraries/SDL2_mixer-2.0.4 install

libraries/lib/libSDL2_ttf.dylib: libraries/lib/libfreetype.dylib
	mkdir -p libraries
	cd libraries && curl https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.15.tar.gz -O
	tar -xf ./libraries/SDL2_ttf-2.0.15.tar.gz -C libraries
	cd libraries/SDL2_ttf-2.0.15 ; FT2_CONFIG=$(shell pwd)/libraries/dist/bin/freetype-config ./configure --prefix=$(shell pwd)/libraries
	make -C ./libraries/SDL2_ttf-2.0.15
	make -C ./libraries/SDL2_ttf-2.0.15 install

libraries/lib/libfreetype.dylib: libraries/lib/libSDL2.dylib
	mkdir -p libraries
	cd libraries && curl https://download.savannah.gnu.org/releases/freetype/freetype-2.4.11.tar.gz -LO
	tar -xf ./libraries/freetype-2.4.11.tar.gz -C libraries
	cd libraries/freetype-2.4.11 ; ./configure --prefix=$(shell pwd)/libraries
	make -C ./libraries/freetype-2.4.11
	make -C ./libraries/freetype-2.4.11 install

libraries/lib/libSDL2.dylib: 
	mkdir -p libraries
	cd libraries && curl https://www.libsdl.org/release/SDL2-2.0.8.tar.gz -O
	tar -xf libraries/SDL2-2.0.8.tar.gz -C libraries
	cd libraries/SDL2-2.0.8 ; ./configure --prefix=$(shell pwd)/libraries
	make -C ./libraries/SDL2-2.0.8
	make -C ./libraries/SDL2-2.0.8 install










































.PHONY : all clean fclean re debug image
