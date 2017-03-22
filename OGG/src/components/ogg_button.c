#include <GL/glut.h>
#include "components/ogg_button.h"

handler(ogg_button, OGG_MOUSE_EVENT);
handler(ogg_button, OGG_MOUSE_ENTER_EVENT);
handler(ogg_button, OGG_MOUSE_LEAVE_EVENT);
extern handler(ogg_shape, OGG_PAINT_EVENT);

def_vtable(ogg_button) (
    [OGG_PAINT_EVENT] = ogg_handler(ogg_shape, OGG_PAINT_EVENT),
    [OGG_MOUSE_EVENT] = ogg_handler(ogg_button, OGG_MOUSE_EVENT),
    [OGG_MOUSE_ENTER_EVENT] = ogg_handler(ogg_button, OGG_MOUSE_ENTER_EVENT),
    [OGG_MOUSE_LEAVE_EVENT] = ogg_handler(ogg_button, OGG_MOUSE_LEAVE_EVENT),
);

default_startup_inh(ogg_button, ogg_rect)(
    .focused_color = OGG_GREEN,
    .callback = 0
)

def_constructor(ogg_button, args)
{
    memcpy(&this->focused_color, &args->focused_color, sizeof(ogg_color));
    memcpy(&this->default_color, &((ogg_shape*)this)->color, sizeof(ogg_color));
    this->callback = args->callback;
}

def_destructor(ogg_button)
{   /* do nothing */
}

def_handler(ogg_button, OGG_MOUSE_EVENT)
{
    this->callback(this);
    *handled = ogg_true;
}

def_handler(ogg_button, OGG_MOUSE_ENTER_EVENT)
{
    set_color(this, this->focused_color);
    ogg_send_event(this, OGG_PAINT_EVENT);
    glFlush();
}

def_handler(ogg_button, OGG_MOUSE_LEAVE_EVENT)
{
    set_color(this, this->default_color);
    ogg_send_event(this, OGG_PAINT_EVENT);
    glFlush();
}
