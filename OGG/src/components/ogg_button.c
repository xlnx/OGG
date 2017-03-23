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

default_startup_inh(ogg_button, ogg_rect)(
    .focused_color = OGG_GREEN,
    .down_color = OGG_RED,
    .text = {
        .content = "Button",
        .color = OGG_RED
    },
    .callback = 0
)

def_constructor(ogg_button, args)
{
    memcpy(&this->down_color, &args->down_color, sizeof(ogg_color));
    memcpy(&this->focused_color, &args->focused_color, sizeof(ogg_color));
    memcpy(&this->default_color, &((ogg_shape*)this)->color, sizeof(ogg_color));
    memcpy(&this->text, &args->text, sizeof(ogg_text));
    this->callback = args->callback;
}

def_destructor(ogg_button)
{   /* do nothing */
}

def_handler(ogg_button, OGG_PAINT_EVENT)
{
    ogg_handler(ogg_shape, OGG_PAINT_EVENT)((ogg_shape*)this, 0, handled);
    coordf pix = { 0, 0 };
    pix = pec_sub_coord(get_real_pec(this, pix), 
        coord(strlen(this->text.content) * 4, 4));
    ogg_paint_text(&this->text, pix);
}

def_handler(ogg_button, OGG_MOUSE_EVENT)
{
    if (this->callback != 0)
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

def_handler(ogg_button, OGG_MOUSE_DOWN_EVENT)
{
    set_color(this, this->down_color);
    ogg_send_event(this, OGG_PAINT_EVENT);
    glFlush();
}

def_handler(ogg_button, OGG_MOUSE_UP_EVENT)
{
    set_color(this, this->focused_color);
    ogg_send_event(this, OGG_PAINT_EVENT);
    glFlush();
}

void ogg_paint_text(ogg_text* text, coordf pix)
{
    glColor3f(text->color.R, text->color.G, text->color.B);
    glRasterPos2f(pix.x, pix.y);
    const char* p = text->content;
    for (; *p != 0; ++p)
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *p);
}

ogg_color ogg_make_color(int R, int G, int B)
{
    ogg_color color = { (float)R / 255, (float)G / 255, (float)B / 255 };
    return color;
}
