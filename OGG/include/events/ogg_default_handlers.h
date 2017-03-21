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

static void ogg_default_handler(OGG_MOUSE_MOVE_EVENT)(int x, int y)
{
    ogg_send_event(main_window, OGG_MOUSE_MOVE_EVENT, x, y);
}

static void ogg_default_handler(OGG_MOUSE_ENTRY_EVENT)(int state)
{
    ogg_send_event(main_window, OGG_MOUSE_ENTRY_EVENT, state);
}

#endif //OGG_GRAPHIC_DEFAULT_EVENTS__HEADER_FILE____