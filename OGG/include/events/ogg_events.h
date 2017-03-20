#ifndef OGG_GRPHIC_EVENTS__HEADER_FILE____
#define OGG_GRPHIC_EVENTS__HEADER_FILE____

typedef unsigned event;

/* call event by 
    object->vptr[event_name](
        ogg_com_ptr this, 
        va_list args, 
        ogg_handle_flag *handled
    );
*/

/* event count */
# define OGG_EVENT_COUNT         (8)

/* list of valid event name */
/* destroy */
# define OGG_DESTROY_EVENT       (0)            /* destroy itself */
/* void glutDisplayFunc(
     void (*func)(void)
   ) */
# define OGG_PAINT_EVENT         (1)            /* paint itself */

/* void glutKeyboardFunc(
     void(*func)(unsigned char key,int x,int y)
   ) */
# define OGG_KEYBOARD_EVENT      (2)            /* key event */
/* void glutSpecialFunc(
     void (*func)(int key,int x,int y)
   ) */
# define OGG_SPECIAL_KEY_EVENT   (3)            /* special key event */

/* void glutMouseFunc(
     void(*func)(int button,int state,int x,int y)
   )*/
# define OGG_MOUSE_EVENT         (4)            /* mouse event */
/* void glutMotionFunc(
     void(*func)(int x,int y)
   ) */
# define OGG_MOUSE_DRAG_EVENT    (5)            /* mouse drag event */
/* void glutPassiveMotionFunc(
     void (*func)(int x,int y)
   ) */
# define OGG_MOUSE_MOVE_EVENT    (6)            /* mouse move event */
/* void glutEntryFunc(
     void(*func)(int state)
   ) */
# define OGG_MOUSE_ENTRY_EVENT   (7)            /* mouse in/mouse leave*/

/* event type */
# define OGG_CHILD_HANDLE_EVENT  (0)
# define OGG_PARENT_HANDLE_EVENT (1)

/* register event type */
static const event ogg_event_type[OGG_EVENT_COUNT] = {
    OGG_CHILD_HANDLE_EVENT,                     /* OGG_DESTROY_EVENT */
    OGG_PARENT_HANDLE_EVENT,                    /* OGG_PAINT_EVENT */
    OGG_CHILD_HANDLE_EVENT,                     /* OGG_KEYBOARD_EVENT */
    OGG_CHILD_HANDLE_EVENT,                     /* OGG_SPECIAL_KEY_EVENT */
    OGG_CHILD_HANDLE_EVENT,                     /* OGG_MOUSE_EVENT */
    OGG_CHILD_HANDLE_EVENT,                     /* OGG_MOUSE_DRAG_EVENT */
    OGG_CHILD_HANDLE_EVENT,                     /* OGG_MOUSE_MOVE_EVENT */
    OGG_CHILD_HANDLE_EVENT,                     /* OGG_MOUSE_ENTRY_EVENT */
};

#endif //OGG_GRPHIC_EVENTS__HEADER_FILE____