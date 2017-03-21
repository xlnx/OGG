#include <GL/glut.h>
#include "components/ogg_button.h"

handler(ogg_button, OGG_MOUSE_EVENT);
extern handler(ogg_shape, OGG_PAINT_EVENT);

def_vtable(ogg_button) (
    [OGG_PAINT_EVENT] = ogg_handler(ogg_shape, OGG_PAINT_EVENT),
    [OGG_MOUSE_EVENT] = ogg_handler(ogg_button, OGG_MOUSE_EVENT)
);

default_startup_inh(ogg_button, ogg_rect)(
    .callback = 0
)

def_constructor(ogg_button, args)
{
    this->callback = args->callback;
}

def_destructor(ogg_button)
{   /* do nothing */
}

def_handler(ogg_button, OGG_MOUSE_EVENT)
{
    if (1) {
        this->callback(this);
        *handled = ogg_true;
    }
}
