# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lomasse <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/06 19:24:01 by lomasse           #+#    #+#              #
#    Updated: 2019/08/08 13:14:45 by lomasse          ###   ########.fr        #
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

NAME			= doom

HEADER 			= $(shell find includes -type f) $(shell find libraries/include -type f 2>/dev/null || true)

SRC_PATH		= $(shell find src -type d)

INC_PATH 		= $(shell find includes -type d) $(shell find libft -type d) $(shell find libraries/include -type d 2>/dev/null || true) \

OBJ_PATH		= OBJ

SDL_IMAGE_DOWNLOAD = https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.3.tar.gz

SRC				= main.c										\
				  turn.c 										\
				  text.c										\
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
				  stop.c										\
				  get.c											\
				  send.c										\
				  msn.c											\
				  mainmulti.c									\
				  mainhost.c									\
				  mainclient.c									\
				  maingame.c 									\
				  mainmenu.c									\
				  menuinput.c									\
				  mainedit.c									\
				  printscreen.c 								\
				  mainoption.c									\
				  option_input_interface.c						\
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
				  menugame.c									\
				  game_input.c 									\
				  game_input_interface.c						\
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
				  tool.c 										\
				  elem2.c 										\
				  bgh_display.c 								\
				  tools_editor.c 								\
				  init_edit.c 									\
				  cursor_editor.c								\
				  cursor_tool.c									\
				  mouse_editor.c 								\
				  display_map.c 								\
				  display_blocs.c 								\
				  edit_poly.c 									\
				  file_list.c									\
				  bresenham.c 									\
				  bresenhamburger.c								\
				  color.c										\
				  file_newclip.c								\
				  file_downside.c								\
				  basicshape.c									\
				  world2view.c									\
				  world2view_mat.c 								\
				  tool2.c 										\
				  save.c 										\
				  print_tab.c 									\
				  popup.c 										\
				  ft_ftoa.c 									\
				  save_object.c									\
				  bar_info.c 									\
				  find_map.c 									\
				  tab_coor.c 									\


#GAME ENGINE
SRC += file_game_engine.c
SRC += file_user_input.c
SRC += file_rasterization.c
SRC += file_get_triangles.c
SRC += file_itoa_coma.c
SRC += file_matrix_tool.c
SRC += file_vector_tool.c
SRC += file_fill_triangle.c
SRC += file_clipping.c
SRC += file_apply_calcul.c
SRC += file_lst.c
SRC += file_order_z_buffer.c
SRC += file_draw_triangle.c
SRC += file_window.c
SRC += file_calcul_world_view.c

#BSP
SRC += file_bsp.c
#SRC += file_main_bsp.c
#SRC += file_mouse_handle.c
SRC += file_parser_polygons.c
SRC += file_process_polygon.c
SRC += file_test_function.c
SRC += file_maths.c
SRC += file_build_bsp_tree.c
SRC += file_select_spliter.c
SRC += file_classify_polygon.c 
SRC += file_affichage_bsp.c

#BRESENHAM
SRC += fille_bresename.c

#MAP EDITOR
#SRC += file_map_editor.c
#SRC += file_map_editor_util.c
#SRC += file_map_editor_ihc.c
#SRC += file_map_editor_display_right_pan.c
#SRC += file_map_editor_update_show_cross.c

######################################################################


OBJ 			= $(addprefix $(OBJ_PATH)/, $(SRC:%.c=%.o))

LIBS 			= SDL2 SDL2_mixer SDL2_ttf freetype ft

LIB_PATH 		= ./libft \
				  ./libraries/lib \

FRAMEWORK 		= OpenGL AppKit

CC 				= gcc -g -std=c99 -fsanitize=address

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
	@if [ -f "/tmp/doom_log2" ]; then \
		echo "${vertfonce}doom_log2 exists.${neutre}"; \
	else \
		touch /tmp/doom_log2; \
		chmod 777 /tmp/doom_log2; \
	fi
	@make -C libft #>> /tmp/doom_log2 2>&1

FORCE:

clean :
	@echo "${rouge}Cleaning the project ...${neutre}\c"
	@make clean -C libft
	@rm -rf $(OBJ_PATH)
	@echo "${rose}DONE${neutre}"

fclean : clean
	@echo "${rouge}Fcleaning the project ...${neutre}\c"
	@make fclean -C libft
	@if [ -f "/tmp/doom_log2" ]; then \
		rm /tmp/doom_log2;
	fi
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

sdl_image:
	if [ -d "./sdl_image/" ]; then \
		echo "SDL (image) ==> Nothing to be done"; \
		else \
		mkdir sdl_image && \
		echo "SDL (image) ==> Downloading SDL image" && \
		cd ./sdl_image && \
		curl -s $(SDL_IMAGE_DOWNLOAD) -O && \
		echo "SDL (image) ==> Compilation SDL image" && \
		tar xzf SDL2_image-2.0.3.tar.gz && \
		cd SDL2_image-2.0.3 && \
		./configure --prefix=$(shell pwd)/sdl_image/SDL2_image-2.0.3 --with-sdl-prefix=$(shell pwd)/libraries/  > /dev/null 2>&1 && \
		$(MAKE)  > /dev/null 2>&1  &&  \
		$(MAKE) install > /dev/null 2>&1  && \
		echo "SDL (image) ==> DONE"; \
		fi





.PHONY: all clean fclean re image
