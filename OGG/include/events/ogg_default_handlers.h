#ifndef OGG_GRAPHIC_DEFAULT_EVENTS__HEADER_FILE____
#define OGG_GRAPHIC_DEFAULT_EVENTS__HEADER_FILE____

# define ogg_default_handler(EVENT) ogg_default_##EVENT##_handler

static void ogg_default_handler(OGG_PAINT_EVENT)(void)
{
    ogg_send_event(main_window, OGG_PAINT_EVENT);
}

static void ogg_default_handler(OGG_KEYBOARD_EVENT)(unsigned char key, int x, int y)
{
    ogg_send_event(main_window, OGG_KEYBOARD_EVENT, key, x, y);
}

static void ogg_default_handler(OGG_SPECIAL_KEY_EVENT)(int key, int x, int y)
{
    ogg_send_event(main_window, OGG_SPECIAL_KEY_EVENT, key, x, y);
}

static void ogg_default_handler(OGG_MOUSE_EVENT)(int button, int state, int x, int y)
{
    ogg_send_event(main_window, OGG_MOUSE_EVENT, button, state, x, y);
}

static void ogg_default_handler(OGG_MOUSE_DRAG_EVENT)(int x, int y)
{
    ogg_send_event(main_window, OGG_MOUSE_DRAG_EVENT, x, y);
}

static ogg_bool is_top_level;
static ogg_com_ptr focused_component = 0;

static void ogg_default_handler(OGG_MOUSE_MOVE_EVENT)(int x, int y)
{
    is_top_level = ogg_true;
    ogg_send_event(main_window, OGG_MOUSE_MOVE_EVENT, x, y);
}

static void ogg_default_handler(OGG_MOUSE_ENTRY_EVENT)(int state)
{
    ogg_send_event(main_window, OGG_MOUSE_ENTRY_EVENT, state);
}

extern int window_width;
extern int window_height;

static void ogg_default_handler(OGG_RESHAPE_EVENT)(int width, int height)
{
    window_width = width; window_height = height;
    glViewport(0, 0, width, height);
    ogg_send_event(main_window, OGG_RESHAPE_EVENT, width, height);
}

static def_checker(OGG_DESTROY_EVENT)
{
    if (focused_component == this) {
        focused_component = 0;
    }
    return ogg_true;
}

static def_checker(OGG_PAINT_EVENT)
{
    return ogg_true;
}

static def_checker(OGG_KEYBOARD_EVENT)
{
    return ogg_true;
}

static def_checker(OGG_SPECIAL_KEY_EVENT)
{
    return ogg_true;
}

static def_checker(OGG_MOUSE_EVENT)
{
    ogg_anchor anchor;
    get_component_real_coord_anchor(this, &anchor);
    if (x >= anchor.coord.left && x <= anchor.coord.right &&
            y >= anchor.coord.top && y <= anchor.coord.bottom)
    {
        if (is_top_level) {
        is_top_level = ogg_false;
            if (focused_component != this) {
                if (focused_component)
                    ogg_send_event(focused_component, OGG_MOUSE_LEAVE_EVENT);
                focused_component = this;
                ogg_send_event(this, OGG_MOUSE_ENTER_EVENT);
            }
        }
        return ogg_true;
    }
    else return ogg_false;
}

static def_checker(OGG_MOUSE_DRAG_EVENT)
{
    ogg_anchor anchor;
    get_component_real_coord_anchor(this, &anchor);
    if (x >= anchor.coord.left && x <= anchor.coord.right &&
            y >= anchor.coord.top && y <= anchor.coord.bottom)
    {
        if (is_top_level) {
        is_top_level = ogg_false;
            if (focused_component != this) {
                if (focused_component)
                    ogg_send_event(focused_component, OGG_MOUSE_LEAVE_EVENT);
                focused_component = this;
                ogg_send_event(this, OGG_MOUSE_ENTER_EVENT);
            }
        }
        return ogg_true;
    }
    else return ogg_false;
}

static def_checker(OGG_MOUSE_MOVE_EVENT)
{
    ogg_anchor anchor;
    get_component_real_coord_anchor(this, &anchor);
    if (x >= anchor.coord.left && x <= anchor.coord.right &&
            y >= anchor.coord.top && y <= anchor.coord.bottom)
    {
        if (is_top_level) {
        is_top_level = ogg_false;
        if (focused_component != this) {
                if (focused_component)
                    ogg_send_event(focused_component, OGG_MOUSE_LEAVE_EVENT);
                focused_component = this;
                ogg_send_event(this, OGG_MOUSE_ENTER_EVENT);
            }
        }
        return ogg_true;
    }
    return ogg_false;
}

static def_checker(OGG_MOUSE_ENTRY_EVENT)
{
    if (state == GL_LEFT) {
        if (focused_component) {
            ogg_send_event(focused_component, OGG_MOUSE_LEAVE_EVENT);
            focused_component = 0;
        }
    }
    return ogg_true;
}

static def_checker(OGG_RESHAPE_EVENT)
{
    return ogg_true;
}

static def_checker(OGG_MOUSE_LEAVE_EVENT)
{
    return ogg_true;
}

static def_checker(OGG_MOUSE_ENTER_EVENT)
{
    return ogg_true;
}

const ogg_bool (*event_checker[OGG_EVENT_COUNT])(ogg_component*, va_list) = {
    [OGG_DESTROY_EVENT] = ogg_checker(OGG_DESTROY_EVENT),
    [OGG_PAINT_EVENT] = ogg_checker(OGG_PAINT_EVENT),
    [OGG_KEYBOARD_EVENT] = ogg_checker(OGG_KEYBOARD_EVENT),
    [OGG_SPECIAL_KEY_EVENT] = ogg_checker(OGG_SPECIAL_KEY_EVENT),
    [OGG_MOUSE_EVENT] = ogg_checker(OGG_MOUSE_EVENT),
    [OGG_MOUSE_DRAG_EVENT] = ogg_checker(OGG_MOUSE_DRAG_EVENT),
    [OGG_MOUSE_MOVE_EVENT] = ogg_checker(OGG_MOUSE_MOVE_EVENT),
    [OGG_MOUSE_ENTRY_EVENT] = ogg_checker(OGG_MOUSE_ENTRY_EVENT),
    [OGG_RESHAPE_EVENT] = ogg_checker(OGG_RESHAPE_EVENT),
    [OGG_MOUSE_LEAVE_EVENT] = ogg_checker(OGG_MOUSE_LEAVE_EVENT),
    [OGG_MOUSE_ENTER_EVENT] = ogg_checker(OGG_MOUSE_ENTER_EVENT),
};

#endif //OGG_GRAPHIC_DEFAULT_EVENTS__HEADER_FILE____