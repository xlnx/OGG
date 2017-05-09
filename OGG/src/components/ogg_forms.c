# include <GL/glut.h>
# include "components/ogg_forms.h"
# include <gl/freeglut.h>
# define OGG_TIME_INTERVAL  (500)/* ms */
# define OGG_TIMER_INDEX    (0)

# define OGG_MAX_FORM_COUNT (65534U)

ogg_application *application;

# define ogg_active_form()                             \
        (glutGetWindow() ? application->forms_lookup[glutGetWindow()] : 0)

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
    [OGG_SPECIAL_KEY_EVENT] = ogg_handler(ogg_form, OGG_SPECIAL_KEY_EVENT)
);

def_constructor(ogg_form, parent != 0)
{
    glutInitWindowPosition(args->info.position.left, args->info.position.top);
    glutInitWindowSize(args->info.position.width, args->info.position.height);
    self->form_id = glutCreateWindow(args->info.title);
    event i = 1;
    for (; i != OGG_EVENT_COUNT; ++i) {
        if (glut_events[i] != 0 && glut_form_event_register[i] != 0) {
            glut_form_event_register[i](glut_events[i]);
        }
    }
    self->color = args->info.color;
    //glut_events[OGG_TIMER_EVENT]
    glutTimerFunc(OGG_TIME_INTERVAL,
        (void(*)(int))glut_events[OGG_TIMER_EVENT], OGG_TIMER_INDEX);
    self->position = args->info.position;
    self->title = args->info.title;
    application->current_component = self;
}

def_destructor(ogg_form)
{   /* do nothing */
}

def_handler(ogg_form, OGG_SPECIAL_KEY_EVENT)
{
    switch (key) {
    case GLUT_KEY_F4: {
        if (glutGetModifiers() == GLUT_ACTIVE_ALT)
            ogg_destroy(self);
    } break;
    }
}

/* ogg_application */
def_vtable(ogg_application) (
);

def_constructor(ogg_application, ogg_true)
{
    self->argc = args->argc;
    self->argv = args->argv;
    self->display_mode = args->display_mode;
    self->forms_lookup = (ogg_form**)malloc(OGG_MAX_FORM_COUNT * sizeof(ogg_form*));
    self->is_top_level = 0;
    self->focused_component = 0;
    self->current_component = 0;
    self->mouse_state = -1;
    self->is_dragging = 0;
    self->last_drag_pc.x = self->last_drag_pc.y = 0;
}

def_destructor(ogg_application)
{
    free(self->forms_lookup);
}

ogg_com_ptr get_current_component()
{
    return application->current_component;
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

ogg_form* ogg_get_active_form()
{
    return ogg_active_form();
}

void set_application(ogg_com_ptr app)
{
    application = app;
}

void ogg_init_application(ogg_application* self)
{
    glutInit(self->argc, self->argv);
    glutInitDisplayMode(self->display_mode);
}

void ogg_terminate_application(ogg_application* self)
{
    ogg_destroy(self);
    exit(0);
}

void ogg_run_application(ogg_application* self)
{
    //current_component = ogg_active_form();
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
    glutMainLoop();
}

void ogg_terminate()
{
    ogg_terminate_application(application);
}
