#include "events/ogg_events.h"

const event ogg_event_type[OGG_EVENT_COUNT] = {
    [OGG_DESTROY_EVENT] = OGG_CHILD_HANDLE_EVENT,
    [OGG_PAINT_EVENT] = OGG_PARENT_HANDLE_EVENT,
    [OGG_KEYBOARD_EVENT] = OGG_CHILD_HANDLE_EVENT,
    [OGG_SPECIAL_KEY_EVENT] = OGG_CHILD_HANDLE_EVENT,
    [OGG_MOUSE_EVENT] = OGG_CHILD_HANDLE_EVENT,
    [OGG_MOUSE_DRAG_EVENT] = OGG_CHILD_HANDLE_EVENT,
    [OGG_MOUSE_MOVE_EVENT] = OGG_CHILD_HANDLE_EVENT,
    [OGG_MOUSE_ENTRY_EVENT] = OGG_CHILD_HANDLE_EVENT,
    [OGG_RESHAPE_EVENT] = OGG_PARENT_HANDLE_EVENT,
    [OGG_MOUSE_LEAVE_EVENT] = OGG_SELF_HANDLE_EVENT,
    [OGG_MOUSE_ENTER_EVENT] = OGG_SELF_HANDLE_EVENT,
    [OGG_MOUSE_DOWN_EVENT] = OGG_SELF_HANDLE_EVENT,
    [OGG_MOUSE_UP_EVENT] = OGG_SELF_HANDLE_EVENT,
    [OGG_MOUSE_DRAG_BEGIN_EVENT] = OGG_CHILD_HANDLE_EVENT,
    [OGG_MOUSE_DRAG_END_EVENT] = OGG_CHILD_HANDLE_EVENT,
    [OGG_FOCUS_EVENT] = OGG_SELF_HANDLE_EVENT,
    [OGG_TIMER_EVENT] = OGG_PARENT_HANDLE_EVENT,
    [OGG_LOSE_FOCUS_EVENT] = OGG_SELF_HANDLE_EVENT,
    [OGG_CREATE_SUB_COMPONENT_EVENT] = OGG_SELF_HANDLE_EVENT,
    [OGG_DESTROY_SUB_COMPONENT_EVENT] = OGG_SELF_HANDLE_EVENT,
    [OGG_ACCESS_EVENT] = OGG_SELF_HANDLE_EVENT,
    [OGG_CAN_ADD_CHILD] = OGG_SELF_HANDLE_EVENT,
};