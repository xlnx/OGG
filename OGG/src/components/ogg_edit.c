#include <GL/glut.h>
#include "components/ogg_edit.h"

extern handler(ogg_shape, OGG_PAINT_EVENT);

handler(ogg_edit, OGG_PAINT_EVENT);

handler(ogg_edit, OGG_KEYBOARD_EVENT);

def_vtable(ogg_edit)(
    [OGG_PAINT_EVENT] = ogg_handler(ogg_edit, OGG_PAINT_EVENT),
    [OGG_KEYBOARD_EVENT] = ogg_handler(ogg_edit, OGG_KEYBOARD_EVENT)
);

default_startup_inh(ogg_edit, ogg_rect)(
    .color = OGG_WHITE
)

def_constructor(ogg_edit, args)
{
    memset(&this->text.content, 0, sizeof(this->text.content));
    memcpy(&this->text.color, &args->color, sizeof(ogg_color));
    memcpy(&((ogg_shape*)this)->color, &OGG_WHITE, sizeof(ogg_color));
}

def_destructor(ogg_edit)
{   /* do nothing */
}

def_handler(ogg_edit, OGG_PAINT_EVENT)
{
    ogg_handler(ogg_shape, OGG_PAINT_EVENT)((ogg_shape*)this, 0, handled);
    coordf pix = { -1, 0 };
    pix = pec_add_coord(get_real_pec(this, pix), coord(4, 4));
    ogg_paint_string(this->text.content, this->text.color, pix);
}

char* ogg_edit_get_text(ogg_edit* edit)
{
    return edit->text.content;
}
