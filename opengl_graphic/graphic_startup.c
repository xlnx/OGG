#define OGG_GRAPHIC_STARTUP__INST____
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
    destroy_window,                  /* OGG_DESTROY_EVENT */
    paint_window,                    /* OGG_PAINT_EVENT */
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

static const glut_register glut_event_register[OGG_EVENT_COUNT] = {
    0,
    (glut_register)glutDisplayFunc,
    (glut_register)glutKeyboardFunc,
    (glut_register)glutSpecialFunc,
    (glut_register)glutMouseFunc,
    (glut_register)glutMotionFunc,
    (glut_register)glutPassiveMotionFunc,
    (glut_register)glutEntryFunc,
};

# include "graphic_default_events.h"
static glut_callback glut_events[OGG_EVENT_COUNT] = {
    0,
    ogg_handler(OGG_PAINT_EVENT),
    ogg_handler(OGG_KEYBOARD_EVENT),
    ogg_handler(OGG_SPECIAL_KEY_EVENT),
    ogg_handler(OGG_MOUSE_EVENT),
    ogg_handler(OGG_MOUSE_DRAG_EVENT),
    ogg_handler(OGG_MOUSE_MOVE_EVENT),
    ogg_handler(OGG_MOUSE_ENTRY_EVENT),
};

# ifdef ogg_handler
#  undef ogg_handler
# endif

void ogg_register_event(event event_name, glut_callback callback)
{
    glut_events[event_name] = callback;
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
    event i = 1;
    for (; i != OGG_EVENT_COUNT; ++i) {
        if (glut_events[i] != 0) {
            glut_event_register[i](glut_events[i]);
        }
    }
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
    glutMainLoop();

    ogg_destroy(main_window);
    return ogg_exit_status();
}

# endif