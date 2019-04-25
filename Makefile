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

HEADER 			= $(shell find includes -type f) $(shell find libraries/include -type f 2>/dev/null || true)

SRC_PATH		= $(shell find src -type d)

INC_PATH 		= $(shell find includes -type d) $(shell find libft -type d) $(shell find libraries/include -type d 2>/dev/null || true) \

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
	@make image

$(LIBFTA): FORCE
	make -C libft

FORCE:

clean :
	@echo "Cleaning the project ...\c"
	@make clean -C libft
	@rm -rf $(OBJ)
	@echo "DONE"

fclean : clean
	@echo "Fcleaning the project ...\c"
	@make fclean -C libft
	@rm -rf $(NAME)
	@echo "DONE"

re : fclean all

relib:
	make re -C libft

resdl:
	@echo "Deleting ./libraries ...\c"
	@rm -rf ./libraries
	@echo "DONE"
	@make image

image: libraries/lib/libSDL2_mixer.dylib

libraries/lib/libSDL2_mixer.dylib: libraries/lib/libSDL2_ttf.dylib
	@echo "Installing SDL2_mixer ...\c"
	@mkdir -p libraries
	@curl -s https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-2.0.4.tar.gz -o libraries/SDL2_mixer-2.0.4.tar.gz 
	@tar -xf ./libraries/SDL2_mixer-2.0.4.tar.gz -C libraries
	@cd libraries/SDL2_mixer-2.0.4 ; ./configure --prefix=$(shell pwd)/libraries > /dev/null 2>&1
	@make -C ./libraries/SDL2_mixer-2.0.4 >/dev/null 2>&1
	@make -C ./libraries/SDL2_mixer-2.0.4 install >/dev/null 2>&1
	@echo "DONE"

libraries/lib/libSDL2_ttf.dylib: libraries/lib/libfreetype.dylib
	@echo "Installing SDL2_ttf ...\c"
	@mkdir -p libraries
	@curl -s https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.15.tar.gz -o libraries/SDL2_ttf-2.0.15.tar.gz
	@tar -xf ./libraries/SDL2_ttf-2.0.15.tar.gz -C libraries
	@cd libraries/SDL2_ttf-2.0.15 ; ./configure --prefix=$(shell pwd)/libraries > /dev/null
	@make -C ./libraries/SDL2_ttf-2.0.15 >/dev/null 2>&1
	@make -C ./libraries/SDL2_ttf-2.0.15 install >/dev/null 2>&1
	@echo "DONE"

libraries/lib/libfreetype.dylib: libraries/lib/libSDL2.dylib
	@echo "Installing freetype2 ...\c"
	@mkdir -p libraries
	@curl -s https://download.savannah.gnu.org/releases/freetype/freetype-2.4.11.tar.gz -Lo libraries/freetype-2.4.11.tar.gz
	@tar -xf ./libraries/freetype-2.4.11.tar.gz -C libraries
	@cd libraries/freetype-2.4.11 ; ./configure --prefix=$(shell pwd)/libraries > /dev/null
	@make -C ./libraries/freetype-2.4.11 >/dev/null 2>&1
	@make -C ./libraries/freetype-2.4.11 install >/dev/null 2>&1
	@echo "DONE"

libraries/lib/libSDL2.dylib: 
	@echo "Installing SDL2 ...\c"
	@mkdir -p libraries
	@curl -s https://www.libsdl.org/release/SDL2-2.0.8.tar.gz -o libraries/SDL2-2.0.8.tar.gz
	@tar -xf libraries/SDL2-2.0.8.tar.gz -C libraries
	@cd libraries/SDL2-2.0.8 ; ./configure --prefix=$(shell pwd)/libraries > /dev/null
	@make -C ./libraries/SDL2-2.0.8 >/dev/null 2>&1
	@make -C ./libraries/SDL2-2.0.8 install >/dev/null 2>&1
	@echo "DONE"

.PHONY: all clean fclean re image