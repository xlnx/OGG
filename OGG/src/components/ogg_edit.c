#include <GL/glut.h>
#include "components/ogg_edit.h"

extern handler(ogg_shape, OGG_PAINT_EVENT);

handler(ogg_edit, OGG_PAINT_EVENT);

handler(ogg_edit, OGG_KEYBOARD_EVENT);

handler(ogg_edit, OGG_SPECIAL_KEY_EVENT);

handler(ogg_edit, OGG_TIMER_EVENT);

handler(ogg_edit, OGG_LOSE_FOCUS_EVENT);

def_vtable(ogg_edit)(
    [OGG_PAINT_EVENT] = ogg_handler(ogg_edit, OGG_PAINT_EVENT),
    [OGG_KEYBOARD_EVENT] = ogg_handler(ogg_edit, OGG_KEYBOARD_EVENT),
    [OGG_SPECIAL_KEY_EVENT] = ogg_handler(ogg_edit, OGG_SPECIAL_KEY_EVENT),
    [OGG_TIMER_EVENT] = ogg_handler(ogg_edit, OGG_TIMER_EVENT),
    [OGG_LOSE_FOCUS_EVENT] = ogg_handler(ogg_edit, OGG_LOSE_FOCUS_EVENT),
);

default_startup_inh(ogg_edit, ogg_rect)(
    .color = OGG_WHITE
)

def_constructor(ogg_edit, args)
{
    memset(&this->text.content, 0, sizeof(this->text.content));
    memcpy(&this->text.color, &args->color, sizeof(ogg_color));
    memcpy(&((ogg_shape*)this)->color, &OGG_WHITE, sizeof(ogg_color));
    this->caret = 0;
    this->caret_visible = ogg_false;
    this->insert_mode = ogg_true;
}

def_destructor(ogg_edit)
{   /* do nothing */
}

extern int window_width;
extern int window_height;

static void paint_caret(ogg_edit* this)
{
    if (this->caret_visible) {
        glColor3f(this->text.color.R, this->text.color.G, this->text.color.B);
    } else {
        glColor3f(OGG_WHITE.R, OGG_WHITE.G, OGG_WHITE.B);
    }
    ogg_pec pec = { -1, 0 };
    ogg_pec pix = pec_add_coord(get_real_pec(this, pec), 
        coord(4 + this->caret * 8, -8));
    float dx = this->insert_mode ? 
        (float)(0.5 * 4 / window_width)
        :
        (float)(4.0 * 4 / window_width),
        dy = (float)(8.0 * 4 / window_height);
    glBegin(GL_QUADS);
    glVertex2f(pix.x, pix.y);
    glVertex2f(pix.x + dx, pix.y);
    glVertex2f(pix.x + dx, pix.y + dy);
    glVertex2f(pix.x, pix.y + dy);
    glEnd();
    if (!this->caret_visible) {
        ogg_paint_char(this->text.content[this->caret], this->text.color, 
            pec_add_coord(pix, coord(0, 4)));
    }
    glFlush();
}

def_handler(ogg_edit, OGG_PAINT_EVENT)
{
    ogg_handler(ogg_shape, OGG_PAINT_EVENT)((ogg_shape*)this, 0, handled);
    coordf pix = { -1, 0 };
    pix = pec_add_coord(get_real_pec(this, pix), coord(4, -4));
    ogg_paint_string(this->text.content, this->text.color, pix);
    paint_caret(this);
}

def_handler(ogg_edit, OGG_KEYBOARD_EVENT)
{
    if (key < 32 && key != '\b' || key > 127) {
        return;
    }
    switch (key) {
    case '\b': if (this->caret != 0){
        int ptr = this->caret--;
        for (; this->text.content[ptr]; ++ptr) {
            this->text.content[ptr - 1] = this->text.content[ptr];
        }
        this->text.content[ptr - 1] = 0;
        ogg_send_event(this, OGG_PAINT_EVENT);
        glFlush();
    } break;
    case 127: {
        int ptr = this->caret;
        for (; this->text.content[ptr]; ++ptr) {
            this->text.content[ptr] = this->text.content[ptr + 1];
        }
        ogg_send_event(this, OGG_PAINT_EVENT);
        glFlush();
    } break;
    default: {
        if (this->insert_mode) {
            int ptr = strlen(this->text.content);
            for (; ptr != this->caret; --ptr) {
                this->text.content[ptr] = this->text.content[ptr - 1];
            }
            this->text.content[this->caret++] = key;
        } else {
            this->text.content[this->caret++] = key;
        }
        ogg_send_event(this, OGG_PAINT_EVENT);
        glFlush();
    } break;
    }
}

def_handler(ogg_edit, OGG_TIMER_EVENT)
{
    this->caret_visible = !this->caret_visible;
    paint_caret(this);
}

def_handler(ogg_edit, OGG_SPECIAL_KEY_EVENT)
{
    switch (key) {
    case GLUT_KEY_LEFT: if (this->caret > 0) {
        --this->caret;
        this->caret_visible = ogg_true;
        ogg_send_event(this, OGG_PAINT_EVENT);
        glFlush();
    } break;
    case GLUT_KEY_RIGHT: if (this->text.content[this->caret]){
        ++this->caret;
        this->caret_visible = ogg_true;
        ogg_send_event(this, OGG_PAINT_EVENT);
        glFlush();
    } break;
    case GLUT_KEY_INSERT: {
        this->insert_mode = !this->insert_mode;
        this->caret_visible = ogg_true;
        ogg_send_event(this, OGG_PAINT_EVENT);
        glFlush();
    }
    }
}

def_handler(ogg_edit, OGG_LOSE_FOCUS_EVENT)
{
    this->caret_visible = ogg_false;
    paint_caret(this);
}

char* ogg_edit_get_text(ogg_edit* edit)
{
    return edit->text.content;
}
