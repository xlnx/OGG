#include <GL/glut.h>
#define OGG_GRAPHIC_STARTUP__INST____
#include "utils/ogg_startup.h"

# ifndef OGG_CUSTOM_STARTUP
# include <gl/freeglut.h>
# define OGG_TIME_INTERVAL  (500)/* ms */
# define OGG_TIMER_INDEX    (0)

def_startup(ogg_window)(
);

def_component(ogg_window) (
);

handler(ogg_window, OGG_SPECIAL_KEY_EVENT);

def_vtable(ogg_window) (
    [OGG_SPECIAL_KEY_EVENT] = ogg_handler(ogg_window, OGG_SPECIAL_KEY_EVENT),
);

static def_constructor(ogg_window, args)
{   /* do nothing */
}

static def_destructor(ogg_window)
{   /* do nothing */
}

static void leave_loop(ogg_window* this)
{
    ogg_destroy(this);
    exit(ogg_exit_status());
}

def_handler(ogg_window, OGG_SPECIAL_KEY_EVENT)
{
    switch (key) {
    case GLUT_KEY_F4: {
        if (glutGetModifiers() == GLUT_ACTIVE_ALT)
            leave_loop(this);
    } break;
    }
}

static ogg_window* main_window;

ogg_component_info ogg_fill_window(void)
{
    return ogg_default_info_ogg_component___(main_window);
}

static const glut_register glut_event_register[OGG_EVENT_COUNT] = {
    [OGG_DESTROY_EVENT] = 0,
    [OGG_PAINT_EVENT] = (glut_register)glutDisplayFunc,
    [OGG_KEYBOARD_EVENT] = (glut_register)glutKeyboardFunc,
    [OGG_SPECIAL_KEY_EVENT] =(glut_register)glutSpecialFunc,
    [OGG_MOUSE_EVENT] = (glut_register)glutMouseFunc,
    [OGG_MOUSE_DRAG_EVENT] = (glut_register)glutMotionFunc,
    [OGG_MOUSE_MOVE_EVENT] = (glut_register)glutPassiveMotionFunc,
    [OGG_MOUSE_ENTRY_EVENT] = (glut_register)glutEntryFunc,
    [OGG_RESHAPE_EVENT] = (glut_register)glutReshapeFunc,
    [OGG_MOUSE_LEAVE_EVENT] = 0,
    [OGG_MOUSE_ENTER_EVENT] = 0,
    [OGG_MOUSE_DOWN_EVENT] = 0,
    [OGG_MOUSE_UP_EVENT] = 0,
    [OGG_MOUSE_DRAG_BEGIN_EVENT] = 0,
    [OGG_MOUSE_DRAG_END_EVENT] = 0,
    [OGG_FOCUS_EVENT] = 0,
    [OGG_TIMER_EVENT] = 0,
    [OGG_LOSE_FOCUS_EVENT] = 0,
};

# include "events/ogg_default_handlers.h"
static glut_callback glut_events[OGG_EVENT_COUNT] = {
    [OGG_DESTROY_EVENT] = 0,
    [OGG_PAINT_EVENT] = ogg_default_handler(OGG_PAINT_EVENT),
    [OGG_KEYBOARD_EVENT] = ogg_default_handler(OGG_KEYBOARD_EVENT),
    [OGG_SPECIAL_KEY_EVENT] = ogg_default_handler(OGG_SPECIAL_KEY_EVENT),
    [OGG_MOUSE_EVENT] = ogg_default_handler(OGG_MOUSE_EVENT),
    [OGG_MOUSE_DRAG_EVENT] = ogg_default_handler(OGG_MOUSE_DRAG_EVENT),
    [OGG_MOUSE_MOVE_EVENT] = ogg_default_handler(OGG_MOUSE_MOVE_EVENT),
    [OGG_MOUSE_ENTRY_EVENT] = ogg_default_handler(OGG_MOUSE_ENTRY_EVENT),
    [OGG_RESHAPE_EVENT] = ogg_default_handler(OGG_RESHAPE_EVENT),
    [OGG_MOUSE_LEAVE_EVENT] = 0,
    [OGG_MOUSE_ENTER_EVENT] = 0,
    [OGG_MOUSE_DOWN_EVENT] = 0,
    [OGG_MOUSE_UP_EVENT] = 0,
    [OGG_MOUSE_DRAG_BEGIN_EVENT] = 0,
    [OGG_MOUSE_DRAG_END_EVENT] = 0,
    [OGG_FOCUS_EVENT] = 0,
    [OGG_TIMER_EVENT] = ogg_default_handler(OGG_TIMER_EVENT),
    [OGG_LOSE_FOCUS_EVENT] = 0,
};

# ifdef ogg_default_handler
#  undef ogg_default_handler
# endif

const ogg_com_ptr ogg_main_window(void)
{
    return main_window;
}

extern int window_width;
extern int window_height;

int ogg_window_width(void)
{
    return window_width;
}

int ogg_window_height(void)
{
    return window_height;
}

void ogg_register_event(event event_name, glut_callback callback)
{
    glut_events[event_name] = callback;
}

int main(int argc, char *argv[])
{
    ogg_create(ogg_window)(
        .ogg_component = {
            .anchor = {
                .type = ogg_anchor_pec,
                .pec = {
                    .top_left = { 0, 0 },
                    .bottom_right = { 100, 100 }
                }
            },
            .parent = 0
        }
    )(main_window);
    current_component = main_window;

    ogg_startup_info st = {
        .argc = argc,
        .argv = argv,
        .display_mode = GLUT_RGB | GLUT_SINGLE,
        .window.position = { 100, 100 },
        .window.size = { 400, 400 },
        .window.title = "OGG Form"
    };

    ogg_main(&st);

    glutInit(&st.argc, st.argv);
    glutInitDisplayMode(st.display_mode);
    glutInitWindowPosition(st.window.position.x, st.window.position.y);
    glutInitWindowSize(st.window.size.width, st.window.size.height);
    glutCreateWindow(st.window.title);

    ogg_delegate();
    event i = 1;
    for (; i != OGG_EVENT_COUNT; ++i) {
        if (glut_events[i] != 0 && glut_event_register[i] != 0) {
            glut_event_register[i](glut_events[i]);
        }
    }
    glut_events[OGG_TIMER_EVENT](OGG_TIME_INTERVAL, 
            glut_events[OGG_TIMER_EVENT], OGG_TIMER_INDEX);
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
    glutMainLoop();

    ogg_destroy(main_window);
    return ogg_exit_status();
}

# endif