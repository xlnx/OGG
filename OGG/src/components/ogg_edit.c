#include <GL/glut.h>
#include "components/ogg_edit.h"

extern handler(ogg_shape, OGG_PAINT_EVENT);

handler(ogg_edit, OGG_PAINT_EVENT);

handler(ogg_edit, OGG_KEYBOARD_EVENT);

handler(ogg_edit, OGG_SPECIAL_KEY_EVENT);

handler(ogg_edit, OGG_TIMER_EVENT);

handler(ogg_edit, OGG_LOSE_FOCUS_EVENT);

handler(ogg_edit, OGG_RESHAPE_EVENT);

def_vtable(ogg_edit)(
    [OGG_PAINT_EVENT] = ogg_handler(ogg_edit, OGG_PAINT_EVENT),
    [OGG_KEYBOARD_EVENT] = ogg_handler(ogg_edit, OGG_KEYBOARD_EVENT),
    [OGG_SPECIAL_KEY_EVENT] = ogg_handler(ogg_edit, OGG_SPECIAL_KEY_EVENT),
    [OGG_TIMER_EVENT] = ogg_handler(ogg_edit, OGG_TIMER_EVENT),
    [OGG_LOSE_FOCUS_EVENT] = ogg_handler(ogg_edit, OGG_LOSE_FOCUS_EVENT),
    [OGG_RESHAPE_EVENT] = ogg_handler(ogg_edit, OGG_RESHAPE_EVENT),
);

default_startup_inh(ogg_edit, ogg_rect)(
    .color = OGG_WHITE
)

def_constructor(ogg_edit, args)
{
    memset(&this->text.content, 0, sizeof(this->text.content));
    this->text.color = args->color;
    ((ogg_shape*)this)->color = OGG_WHITE;
    this->caret = this->offset = 0;
    this->caret_visible = ogg_false;
    this->insert_mode = ogg_true;
}

def_destructor(ogg_edit)
{   /* do nothing */
}

extern int window_width;
extern int window_height;

static int get_edit_width(ogg_edit* this)
{
    ogg_anchor anchor;
    get_component_real_coord_anchor(this, &anchor);
    return (anchor.coord.right - anchor.coord.left) / 8 - 1;
}

static void adjust_offset(ogg_edit* this)
{
    const int width = get_edit_width(this),
            length = strlen(this->text.content);
    if (this->caret >= width + this->offset) {
        this->offset = this->caret - width + 1;
    } else if (this->caret < this->offset) {
        this->offset = this->caret;
    } else if (length < this->offset + width - 1) {
        this->offset = max(0, length - width + 1);
    }
}

static void paint_caret(ogg_edit* this)
{
    if (this->caret_visible) {
        glColor3f(this->text.color.R, this->text.color.G, this->text.color.B);
    } else {
        glColor3f(OGG_WHITE.R, OGG_WHITE.G, OGG_WHITE.B);
    }
    ogg_pec pec = { -1, 0 };
    int cur_pos = this->caret - this->offset;
    ogg_pec pix = pec_add_coord(get_real_pec(this, pec), 
        coord(4 + cur_pos * 8, -8));
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
    ogg_flush_screen();
}

def_handler(ogg_edit, OGG_PAINT_EVENT)
{
    ogg_handler(ogg_shape, OGG_PAINT_EVENT)((ogg_shape*)this, 0, handled);
    coordf pix = { -1, 0 };
    pix = pec_add_coord(get_real_pec(this, pix), coord(4, -4));
    int width = get_edit_width(this);
    ogg_paint_string_len(this->text.content + this->offset, width, this->text.color, pix);
    paint_caret(this);
}

def_handler(ogg_edit, OGG_KEYBOARD_EVENT)
{
    if (key < 32 && key != '\b' || key > 127) {
        return;
    }
    switch (key) {
    case '\b': if (this->caret != 0){
        int ptr = this->caret--, length = strlen(this->text.content);
        for (; ptr != length + 1; ++ptr) {
            this->text.content[ptr - 1] = this->text.content[ptr];
        }
    } break;
    case 127: {
        if ((glutGetModifiers() & GLUT_ACTIVE_CTRL) && this->caret != 0) {
            int ptr = this->caret, det = 1, length = strlen(this->text.content);
            for (; det != this->caret; ++det) {
                if (this->text.content[this->caret - det] == ' ')
                    break;
            }
            this->caret -= det;
            for (; ptr != length + det; ++ptr) {
                this->text.content[ptr - det] = this->text.content[ptr];
            }
        } else {
            int ptr = this->caret;
            for (; this->text.content[ptr]; ++ptr) {
                this->text.content[ptr] = this->text.content[ptr + 1];
            }
        }
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
    } break;
    }
    *handled = ogg_true;
    adjust_offset(this);
    ogg_send_event(this, OGG_PAINT_EVENT);
    ogg_flush_screen();
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
    } break;
    case GLUT_KEY_RIGHT: if (this->text.content[this->caret]){
        ++this->caret;
    } break;
    case GLUT_KEY_INSERT: {
        this->insert_mode = !this->insert_mode;
    } break;
    case GLUT_KEY_HOME: {
        this->caret = 0;
    } break;
    case GLUT_KEY_END: {
        this->caret = strlen(this->text.content);
    } break;
    default: return;
    }
    *handled = ogg_true;
    this->caret_visible = ogg_true;
    adjust_offset(this);
    ogg_send_event(this, OGG_PAINT_EVENT);
    ogg_flush_screen();
}

def_handler(ogg_edit, OGG_LOSE_FOCUS_EVENT)
{
    this->caret_visible = ogg_false;
    paint_caret(this);
}

def_handler(ogg_edit, OGG_RESHAPE_EVENT)
{
    adjust_offset(this);
    ogg_send_event(this, OGG_PAINT_EVENT, 0);
    ogg_flush_screen();
}

char* ogg_edit_get_text(ogg_edit* edit)
{
    return edit->text.content;
}
