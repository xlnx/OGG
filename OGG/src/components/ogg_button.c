#include <GL/glut.h>
#include "components/ogg_button.h"

extern void destroy_shape(ogg_shape* shape);

extern void paint_shape(ogg_shape* shape);

static void button_click(ogg_button* button, va_list args, ogg_handle_flag *handled);

def_vtable(ogg_button) (
    [OGG_DESTROY_EVENT] = destroy_shape,
    [OGG_PAINT_EVENT] = paint_shape,
    [OGG_MOUSE_EVENT] = button_click
);

default_startup_inh(ogg_button, ogg_rect)(
    .callback = 0
)

def_constructor(ogg_button, args)
{
    this->callback = args->callback;
}

static void button_click(ogg_button* button, va_list args, ogg_handle_flag *handled)
{
    ogg_coord coord; coord.x = va_arg(args, int); coord.y = va_arg(args, int);
    if (1) {
        button->callback(button);
        *handled = ogg_true;
    }
}
