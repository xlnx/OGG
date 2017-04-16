#include <GL/glut.h>
#include "components/ogg_button.h"

handler(ogg_button, OGG_MOUSE_EVENT);
handler(ogg_button, OGG_PAINT_EVENT);
handler(ogg_button, OGG_MOUSE_ENTER_EVENT);
handler(ogg_button, OGG_MOUSE_LEAVE_EVENT);
handler(ogg_button, OGG_MOUSE_DOWN_EVENT);
handler(ogg_button, OGG_MOUSE_UP_EVENT);
extern handler(ogg_shape, OGG_PAINT_EVENT);

def_vtable(ogg_button) (
    [OGG_PAINT_EVENT] = ogg_handler(ogg_button, OGG_PAINT_EVENT),
    [OGG_MOUSE_EVENT] = ogg_handler(ogg_button, OGG_MOUSE_EVENT),
    [OGG_MOUSE_ENTER_EVENT] = ogg_handler(ogg_button, OGG_MOUSE_ENTER_EVENT),
    [OGG_MOUSE_LEAVE_EVENT] = ogg_handler(ogg_button, OGG_MOUSE_LEAVE_EVENT),
    [OGG_MOUSE_DOWN_EVENT] = ogg_handler(ogg_button, OGG_MOUSE_DOWN_EVENT),
    [OGG_MOUSE_UP_EVENT] = ogg_handler(ogg_button, OGG_MOUSE_UP_EVENT)
);

//default_startup_inh(ogg_button, ogg_rect)(
//    .focused_color = OGG_GREEN,
//    .down_color = OGG_RED,
//    .text = {
//        .content = "Button",
//        .color = OGG_RED
//    },
//    .callback = 0
//)

def_constructor(ogg_button, parent != 0)
{
    self->down_color = args->down_color;
    self->focused_color = args->focused_color;
    self->default_color = ((ogg_shape*)self)->color;
    self->text = args->text;
    self->callback = args->callback;
}

def_destructor(ogg_button)
{   /* do nothing */
}

def_handler(ogg_button, OGG_PAINT_EVENT)
{
    inherited(ogg_button, OGG_PAINT_EVENT);
    coordf pix = { 0, 0 };
    pix = pec_sub_coord(get_real_pec(self, pix),
        coord(strlen(self->text.content) * 4, 4));
    ogg_paint_string(self->text.content, self->text.color, pix);
}

def_handler(ogg_button, OGG_MOUSE_EVENT)
{
    if (self->callback != 0)
        self->callback(self);
    *handled = ogg_true;
}

def_handler(ogg_button, OGG_MOUSE_ENTER_EVENT)
{
    set_shape_color(self, self->focused_color);
    ogg_send_event(self, OGG_PAINT_EVENT);
    ogg_flush_screen();
}

def_handler(ogg_button, OGG_MOUSE_LEAVE_EVENT)
{
    set_shape_color(self, self->default_color);
    ogg_send_event(self, OGG_PAINT_EVENT);
    ogg_flush_screen();
}

def_handler(ogg_button, OGG_MOUSE_DOWN_EVENT)
{
    set_shape_color(self, self->down_color);
    ogg_send_event(self, OGG_PAINT_EVENT);
    ogg_flush_screen();
}

def_handler(ogg_button, OGG_MOUSE_UP_EVENT)
{
    set_shape_color(self, self->focused_color);
    ogg_send_event(self, OGG_PAINT_EVENT);
    ogg_flush_screen();
}

