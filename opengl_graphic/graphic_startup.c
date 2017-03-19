#include "graphic_startup.h"

# ifndef OGG_CUSTOM_STARTUP
# include <gl/freeglut.h>

static ogg_window* main_window;

static void destroy_window(void)
{
}

static void paint_window(void)
{
}

static ogg_event_handler ogg_window_vtable[OGG_EVENT_COUNT] = {
    destroy_window,  // OGG_DESTROY_EVENT
    paint_window     // OGG_PAINT_EVENT
};

static ogg_window* create_window(void)
{
    ogg_window *window = (ogg_window*)malloc(sizeof(ogg_window));
# ifdef DEBUG
    alloc_memory++;
# endif
    static ogg_anchor anchor = {
        .type = ogg_anchor_pec,
        .pec = {
            .top_left = {0, 0},
            .bottom_right = {100, 100}
        }
    };
    ogg_component_info info = {
        .anchor = &anchor,
        .parent = 0,
        .vptr = ogg_window_vtable
    };
    create_component(window, &info);
    return window;
}

ogg_com_startup make_global_startup(void)
{
    return make_startup(main_window);
}

int main(int argc, char *argv[])
{
    main_window = create_window();

    ogg_startup_info st = {
        .argc = argc,
        .argv = argv,
        .display_mode = GLUT_RGB | GLUT_SINGLE,
        .window.position = { 100, 100 },
        .window.size = { 400, 400 },
        .window.title = "OGG Form"
    };
    ogg_startup(&st);
    glutInit(&st.argc, st.argv);
    glutInitDisplayMode(st.display_mode);
    glutInitWindowPosition(st.window.position.x, st.window.position.y);
    glutInitWindowSize(st.window.size.width, st.window.size.height);
    glutCreateWindow(st.window.title);

    ogg_delegate();
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
    glutMainLoop();

    ogg_destroy(main_window);
    return ogg_exit_status();
}

# endif