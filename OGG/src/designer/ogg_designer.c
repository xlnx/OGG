//#include <GL/glew.h>
#include <GL/glut.h>
#define OGG_GRAPHIC_STARTUP__INST____
#include "utils/ogg_startup.h"

# ifndef OGG_CUSTOM_STARTUP
# include <gl/freeglut.h>
# define OGG_TIME_INTERVAL  (500)/* ms */
# define OGG_TIMER_INDEX    (0)

#  define OGG_MAX_FORM_COUNT (65534U)
def_startup(ogg_application)(
    int *argc;
    char **argv;
    ogg_display_mode display_mode;
);

def_component(ogg_application)(
    int *argc;
    char **argv;
    ogg_display_mode display_mode;
    ogg_form **forms_lookup;
);

static ogg_application *application;

# define ogg_active_form()                             \
        (application->forms_lookup[glutGetWindow()])

/* ogg_form */
static const glut_register glut_form_event_register[OGG_EVENT_COUNT] = {
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

handler(ogg_form, OGG_SPECIAL_KEY_EVENT);

def_vtable(ogg_form)(
    [OGG_SPECIAL_KEY_EVENT] = ogg_handler(ogg_form, OGG_SPECIAL_KEY_EVENT),
);

def_constructor(ogg_form, args)
{
    glutInitWindowPosition(args->info.position.left, args->info.position.top);
    glutInitWindowSize(args->info.position.width, args->info.position.height);
    this->form_id = glutCreateWindow(args->info.title);
    event i = 1;
    for (; i != OGG_EVENT_COUNT; ++i) {
        if (glut_events[i] != 0 && glut_form_event_register[i] != 0) {
            glut_form_event_register[i](glut_events[i]);
        }
    }
    //glut_events[OGG_TIMER_EVENT]
    glutTimerFunc(OGG_TIME_INTERVAL, 
        (void(*)(int))glut_events[OGG_TIMER_EVENT], OGG_TIMER_INDEX);
    this->position = args->info.position;
    this->title = args->info.title;
}

def_destructor(ogg_form)
{   /* do nothing */
}

def_handler(ogg_form, OGG_SPECIAL_KEY_EVENT)
{
    switch (key) {
    case GLUT_KEY_F4: {
        if (glutGetModifiers() == GLUT_ACTIVE_ALT)
            ogg_destroy(this);
    } break;
    }
}

/* ogg_application */
def_vtable(ogg_application) (
);

static def_constructor(ogg_application, args)
{
    this->argc = args->argc;
    this->argv = args->argv;
    this->display_mode = args->display_mode;
    this->forms_lookup = (ogg_form**)malloc(OGG_MAX_FORM_COUNT * sizeof(ogg_form*));
}

static def_destructor(ogg_application)
{
    free(this->forms_lookup);
}

static void ogg_init_application(ogg_application* this)
{
    glutInit(this->argc, this->argv);
    glutInitDisplayMode(this->display_mode);
}

static void ogg_terminate_application(ogg_application* this)
{
    ogg_destroy(this);
    exit(ogg_exit_status());
}

static void ogg_run_application(ogg_application* this)
{
    current_component = ogg_active_form();
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
    glutMainLoop();
    ogg_terminate(this);
}

/* startup */
void ogg_terminate()
{
    ogg_terminate_application(application);
}

ogg_form* ogg_create_form(form_info info)
{
    ogg_form* frm;
    ogg_create(ogg_form)(
        .ogg_component = {
            .parent = (ogg_component*)application,
            .anchor = {
                .type = ogg_anchor_pec,
                .pec = {
                    .top_left = { 0, 0 },
                    .bottom_right = { 100, 100 }
                }
            }
        },
        .info = info,
    )(frm);
    application->forms_lookup[frm->form_id] = frm;
    return frm;
}

//void ogg_destroy_form(ogg_form* this)
//{
//    ogg_destroy(this);
//}

ogg_form* ogg_get_active_form()
{
    return ogg_active_form();
}

int main(int argc, char *argv[])
{
    ogg_create(ogg_application)(
        .ogg_component = {
            .parent = 0,
            .anchor = {
                .type = ogg_anchor_pec,
                .pec = {
                    .top_left = { 0, 0 },
                    .bottom_right = { 100, 100 }
                }
            }
        },
        .argc = &argc,
        .argv = argv,
        .display_mode = GLUT_RGB | GLUT_SINGLE,
    )(application);
    ogg_init_application(application);
    ogg_init_application_forms();
    ogg_run_application(application);
}

# endif