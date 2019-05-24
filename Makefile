# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lomasse <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/06 19:24:01 by lomasse           #+#    #+#              #
#    Updated: 2019/05/22 14:24:59 by lomasse          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
rose=\033[1;31m
violetfonce=\033[0;35m
violetclair=\033[1;35m
neutre=\033[0m
cyanfonce=\033[0;36m
cyanclair=\033[1;36m
vertfonce=\033[0;32m
vertclair=\033[1;32m
rouge=\033[31m

NAME			= doom

HEADER 			= $(shell find includes -type f) $(shell find libraries/include -type f 2>/dev/null || true)

SRC_PATH		= $(shell find src -type d)

INC_PATH 		= $(shell find includes -type d) $(shell find libft -type d) $(shell find libraries/include -type d 2>/dev/null || true) \

OBJ_PATH		= OBJ

SRC				= main.c										\
				  turn.c 										\
				  inputturn.c									\
				  window.c										\
				  init.c										\
				  poly.c										\
				  drawpoly.c									\
				  matrice.c										\
				  parse.c										\
				  initwn.c										\
				  nothread.c									\
				  thread.c										\
				  load_menu.c									\
				  sdl.c											\
				  load.c										\
				  load2.c										\
				  load_intro.c									\
				  texture.c										\
				  maingame.c 									\
				  mainmenu.c									\
				  menuinput.c									\
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
				  hud.c											\
				  sky.c											\
				  newcloud.c									\
				  init_input.c 									\
				  player.c 										\
				  console.c 									\
				  console_input_and_read.c 						\
				  print_ariel_text.c 							\
				  menu_show.c 									\
				  load_fonts.c 									\
				  tool.c 									\
				  world2view.c								\
				  world2view_mat.c

OBJ 			= $(addprefix $(OBJ_PATH)/, $(SRC:%.c=%.o))

LIBS 			= SDL2 SDL2_mixer SDL2_ttf freetype ft

LIB_PATH 		= ./libft \
				  ./libraries/lib \

FRAMEWORK 		= OpenGL AppKit

CC 				= gcc -g -std=c99

vpath %.c $(foreach dir, $(SRC_PATH), $(dir):)

IFLAG			= $(foreach dir, $(INC_PATH), -I$(dir) )

CFLAG 			= -Wall -Wextra -Werror

LFLAG 			= $(foreach dir, $(LIB_PATH), -L $(dir) ) $(foreach lib, $(LIBS), -l$(lib) ) $(foreach fmw, $(FRAMEWORK), -framework $(fmw) ) \

LIBFTA			= ./libft \

IMAGE 			= ./libraries \

DEBUG			= -g -fsanitize=address

all: $(NAME)

$(NAME): $(IMAGE) $(OBJ)
	@echo "${vertfonce}Compiling $@ ...${neutre}\c"
	@$(CC) $(CFLAG) -o $(NAME) $(OBJ) $(LFLAG) $(DEBUG)
	@echo "${vertclair}DONE${neutre}"

$(OBJ_PATH)/%.o: %.c $(HEADER) $(LIBFTA)
	@mkdir -p $(OBJ_PATH)
	@echo "${violetfonce}Creating $@ ...${neutre}\c"
	@$(CC) $(CFLAG) -o $@ -c $< $(IFLAG)
	@echo "${rose}DONE${neutre}"

$(IMAGE): FORCE
	@if [ -d "./libraries" ]; then \
		echo "${vertfonce}SDL2 is installed.${neutre}"; \
	else \
		make image; \
	fi

$(LIBFTA): FORCE
	@make -C libft >> /tmp/doom_log2 2>&1

FORCE:

clean :
	@echo "${rouge}Cleaning the project ...${neutre}\c"
	@make clean -C libft
	@rm -rf $(OBJ_PATH)
	@echo "${rose}DONE${neutre}"

fclean : clean
	@echo "${rouge}Fcleaning the project ...${neutre}\c"
	@make fclean -C libft
	@rm -rf $(NAME)
	@echo "${rose}DONE${neutre}"

re : fclean all

relib:
	@make re -C libft

resdl:
	@echo "${cyanfonce}Deleting ./libraries ...${neutre}\c"
	@rm -rf ./libraries
	@echo "${cyanclair}DONE${neutre}"
	@make image

image: libraries/lib/libSDL2_mixer.dylib

libraries/lib/libSDL2_mixer.dylib: libraries/lib/libSDL2_ttf.dylib
	@echo "${cyanfonce}Installing SDL2_mixer ...${neutre}\c"
	@mkdir -p libraries
	@curl -s https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-2.0.4.tar.gz -o libraries/SDL2_mixer-2.0.4.tar.gz >>/tmp/doom_lib_log 2>&1
	@tar -xf ./libraries/SDL2_mixer-2.0.4.tar.gz -C libraries >>/tmp/doom_lib_log 2>&1
	@cd libraries/SDL2_mixer-2.0.4 ; ./configure --prefix=$(shell pwd)/libraries >>/tmp/doom_lib_log 2>&1
	@make -C ./libraries/SDL2_mixer-2.0.4 >>/tmp/doom_lib_log 2>&1
	@make -C ./libraries/SDL2_mixer-2.0.4 install >>/tmp/doom_lib_log 2>&1
	@echo "${cyanclair}DONE${neutre}"

libraries/lib/libSDL2_ttf.dylib: libraries/lib/libfreetype.dylib
	@echo "${cyanfonce}Installing SDL2_ttf ...${neutre}\c"
	@mkdir -p libraries
	@curl -s https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.15.tar.gz -o libraries/SDL2_ttf-2.0.15.tar.gz >>/tmp/doom_lib_log 2>&1
	@tar -xf ./libraries/SDL2_ttf-2.0.15.tar.gz -C libraries >>/tmp/doom_lib_log 2>&1
	@cd libraries/SDL2_ttf-2.0.15 ; FT2_CONFIG=$(shell pwd)/libraries/bin/freetype-config ./configure --prefix=$(shell pwd)/libraries >>/tmp/doom_lib_log
	@make -C ./libraries/SDL2_ttf-2.0.15 >>/tmp/doom_lib_log 2>&1
	@make -C ./libraries/SDL2_ttf-2.0.15 install >>/tmp/doom_lib_log 2>&1
	@echo "${cyanclair}DONE${neutre}"

libraries/lib/libfreetype.dylib: libraries/lib/libSDL2.dylib
	@echo "${cyanfonce}Installing freetype2 ...${neutre}\c"
	@mkdir -p libraries
	@curl -s https://download.savannah.gnu.org/releases/freetype/freetype-2.4.11.tar.gz -Lo libraries/freetype-2.4.11.tar.gz >>/tmp/doom_lib_log 2>&1
	@tar -xf ./libraries/freetype-2.4.11.tar.gz -C libraries >>/tmp/doom_lib_log 2>&1
	@cd libraries/freetype-2.4.11 ; ./configure --prefix=$(shell pwd)/libraries >>/tmp/doom_lib_log
	@make -C ./libraries/freetype-2.4.11 >>/tmp/doom_lib_log 2>&1
	@make -C ./libraries/freetype-2.4.11 install >>/tmp/doom_lib_log 2>&1
	@echo "${cyanclair}DONE${neutre}"


libraries/lib/libSDL2.dylib:
	@echo "${cyanfonce}Installing SDL2 ...${neutre}\c"
	@mkdir -p libraries
	@curl -s https://www.libsdl.org/release/SDL2-2.0.8.tar.gz -o libraries/SDL2-2.0.8.tar.gz >>/tmp/doom_lib_log 2>&1
	@tar -xf libraries/SDL2-2.0.8.tar.gz -C libraries >>/tmp/doom_lib_log 2>&1
	@cd libraries/SDL2-2.0.8 ; ./configure --prefix=$(shell pwd)/libraries >>/tmp/doom_lib_log 2>&1
	@make -C ./libraries/SDL2-2.0.8 >>/tmp/doom_lib_log 2>&1
	@make -C ./libraries/SDL2-2.0.8 install >>/tmp/doom_lib_log 2>&1
	@echo "${cyanclair}DONE${neutre}"

.PHONY: all clean fclean re image
