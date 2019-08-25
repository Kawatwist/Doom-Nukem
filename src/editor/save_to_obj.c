    // #include <doom.h>
    // #include <editor.h>

    // static void create_obj(t_win *wn, t_edit *edit, char *name)
    // {
    //     int fd;

    //     fd = 0;
    //     if (!access(name, F_OK)
    //     {
    //         if ((fd = creat(name, O_WRONLY)) != -1)
    //         {
    //             ft_putstrfd("JE CREE CE OBJ", fd);
    //         }
    //         else
    //             ft_putstr("File's creation failed\n");
    //     }
    //     else
    //         ft_putstr("File name already used\n");
    // }

    // void        save_panel(t_win *wn, t_edit *edit)
    // {
    //     static char *map_name = NULL;
    //     SDL_Rect    position;

    //     position = define_rect(6 * wn->xscreen / 8, 0, wn->xscreen / 8, 0.5 * wn->yscreen / 8);
    //     map_name = text_box(wn, map_name);
    //     if (map_name != NULL && hitbox(wn->input->x, wn->input->y, &position) && mouse_pressed(wn, SDL_BUTTON_LEFT))
    //     {
    //         printf("Map save will be called %s\n", map_name);
    //     }
    // }