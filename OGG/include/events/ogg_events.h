#ifndef OGG_GRPHIC_EVENTS__HEADER_FILE____
#define OGG_GRPHIC_EVENTS__HEADER_FILE____
# include <stdarg.h>
# include <stdlib.h>
typedef unsigned event;

/* call event by
    object->vptr[event_name](
        ogg_com_ptr self,
        va_list args,
        ogg_handle_flag *handled
    );
*/

# define handler(T, event_name)                                         \
    void T##_##event_name##___handler__(                                \
            T* self, va_list args, ogg_handle_flag* handled)

# define ogg_handler(T, event_name)                                     \
    T##_##event_name##___handler__

# define def_handler(T, event_name)                                     \
    void T##_##event_name##___handler__(                                \
            T* self, va_list args, ogg_handle_flag* handled)            \
    {                                                                   \
        void T##_##event_name##_helper__(                               \
            T* self, event_name##_ARGS ogg_handle_flag* handled);       \
        event_name##_EXTRACT_ARGS                                       \
        T##_##event_name##_helper__(self,                               \
            event_name##_PASS_ARGS handled);                            \
    }                                                                   \
    void T##_##event_name##_helper__(                                   \
            T* self, event_name##_ARGS ogg_handle_flag* handled)

# define inherited(T, event_name)                                       \
    (T##_parent_vtable[event_name] ?                                    \
        T##_parent_vtable[event_name]((void*)self,                      \
            event_name##_PASS_ARGS handled): 0)                         \


#  define ogg_checker(event_name)                                       \
    event_checker__##event_name##___

#  define def_checker(event_name)                                       \
    ogg_bool event_checker__##event_name##___(                          \
        ogg_component* self, va_list args) {                            \
        ogg_bool event_checker_##event_name##__(event_name##_ARGS       \
            ogg_component* self);                                       \
        event_name##_EXTRACT_ARGS                                       \
        return event_checker_##event_name##__(                          \
                event_name##_PASS_ARGS self);                           \
    }                                                                   \
    ogg_bool event_checker_##event_name##__(event_name##_ARGS           \
        ogg_component* self)

/* event count */
# define OGG_EVENT_COUNT                                                (22)



/* list of valid event name */
/* destroy */
# define OGG_DESTROY_EVENT                  /* destroy itself */        (0)
        /* actually not a event */
# define OGG_DESTROY_EVENT_ARGS                                         \
        /* no args */
# define OGG_DESTROY_EVENT_EXTRACT_ARGS                                 \
        /* do nothing */
# define OGG_DESTROY_EVENT_PASS_ARGS                                    \
        /* no args */



/* void glutDisplayFunc(
     void (*func)(void)
   ) */
# define OGG_PAINT_EVENT                    /* paint itself */          (1)
# define OGG_PAINT_EVENT_ARGS                                           \
        /* no args */
# define OGG_PAINT_EVENT_EXTRACT_ARGS                                   \
        /* do nothing */
# define OGG_PAINT_EVENT_PASS_ARGS                                      \
        /* no args */



/* void glutKeyboardFunc(
     void(*func)(unsigned char key, int x, int y)
   ) */
# define OGG_KEYBOARD_EVENT                 /* key event */             (2)
# define OGG_KEYBOARD_EVENT_ARGS                                        \
        unsigned char key, int x, int y,
# define OGG_KEYBOARD_EVENT_EXTRACT_ARGS                                \
        unsigned char key = va_arg(args, unsigned int);                 \
        int x = va_arg(args, int);                                      \
        int y = va_arg(args, int);
# define OGG_KEYBOARD_EVENT_PASS_ARGS                                   \
        key, x, y,



/* void glutSpecialFunc(
     void (*func)(int key, int x, int y)
   ) */
# define OGG_SPECIAL_KEY_EVENT              /* special key event */     (3)
# define OGG_SPECIAL_KEY_EVENT_ARGS                                     \
        int key, int x, int y,
# define OGG_SPECIAL_KEY_EVENT_EXTRACT_ARGS                             \
        int key = va_arg(args, int);                                    \
        int x = va_arg(args, int);                                      \
        int y = va_arg(args, int);
# define OGG_SPECIAL_KEY_EVENT_PASS_ARGS                                \
        key, x, y,



/* void glutMouseFunc(
     void(*func)(int button, int state, int x, int y)
   )*/
# define OGG_MOUSE_EVENT                    /* mouse event */           (4)
# define OGG_MOUSE_EVENT_ARGS                                           \
        int button, int state, int x, int y,
# define OGG_MOUSE_EVENT_EXTRACT_ARGS                                   \
        int button = va_arg(args, int);                                 \
        int state = va_arg(args, int);                                  \
        int x = va_arg(args, int);                                      \
        int y = va_arg(args, int);
# define OGG_MOUSE_EVENT_PASS_ARGS                                      \
        button, state, x, y,



/* void glutMotionFunc(
     void(*func)(int x, int y)
   ) */
# define OGG_MOUSE_DRAG_EVENT               /* mouse drag event */      (5)
# define OGG_MOUSE_DRAG_EVENT_ARGS                                      \
        int dx, int dy,
# define OGG_MOUSE_DRAG_EVENT_EXTRACT_ARGS                              \
        int dx = va_arg(args, int);                                     \
        int dy = va_arg(args, int);
# define OGG_MOUSE_DRAG_EVENT_PASS_ARGS                                 \
        dx, dy,



/* void glutPassiveMotionFunc(
     void (*func)(int x, int y)
   ) */
# define OGG_MOUSE_MOVE_EVENT               /* mouse move event */      (6)
# define OGG_MOUSE_MOVE_EVENT_ARGS                                      \
        int x, int y,
# define OGG_MOUSE_MOVE_EVENT_EXTRACT_ARGS                              \
        int x = va_arg(args, int);                                      \
        int y = va_arg(args, int);
# define OGG_MOUSE_MOVE_EVENT_PASS_ARGS                                 \
        x, y,



/* void glutEntryFunc(
     void(*func)(int state)
   ) */
# define OGG_MOUSE_ENTRY_EVENT              /* mouse in/mouse leave*/   (7)
# define OGG_MOUSE_ENTRY_EVENT_ARGS                                     \
        int state,
# define OGG_MOUSE_ENTRY_EVENT_EXTRACT_ARGS                             \
        int state = va_arg(args, int);
# define OGG_MOUSE_ENTRY_EVENT_PASS_ARGS                                \
        state,



/* void glutReshapeFunc(
     void(*func)(int width, int height)
   ) */
#  define OGG_RESHAPE_EVENT                 /* window reshape */        (8)
#  define OGG_RESHAPE_EVENT_ARGS                                        \
        int width, int height,
#  define OGG_RESHAPE_EVENT_EXTRACT_ARGS                                \
        int width = va_arg(args, int);                                  \
        int height = va_arg(args, int);
#  define OGG_RESHAPE_EVENT_PASS_ARGS                                   \
        width, height,



#  define OGG_MOUSE_LEAVE_EVENT             /* mouse leave component */ (9)
#  define OGG_MOUSE_LEAVE_EVENT_ARGS                                    \
        /* no args */
#  define OGG_MOUSE_LEAVE_EVENT_EXTRACT_ARGS                            \
        /* no args */
#  define OGG_MOUSE_LEAVE_EVENT_PASS_ARGS                               \
        /* no args */



#  define OGG_MOUSE_ENTER_EVENT             /* mouse leave component */ (10)
#  define OGG_MOUSE_ENTER_EVENT_ARGS                                    \
        /* no args */
#  define OGG_MOUSE_ENTER_EVENT_EXTRACT_ARGS                            \
        /* no args */
#  define OGG_MOUSE_ENTER_EVENT_PASS_ARGS                               \
        /* no args */



#  define OGG_MOUSE_DOWN_EVENT              /* mouse down event */      (11)
#  define OGG_MOUSE_DOWN_EVENT_ARGS                                     \
        int button, int x, int y,
#  define OGG_MOUSE_DOWN_EVENT_EXTRACT_ARGS                             \
        int button = va_arg(args, int);                                 \
        int x = va_arg(args, int);                                      \
        int y = va_arg(args, int);
#  define OGG_MOUSE_DOWN_EVENT_PASS_ARGS                                \
        button, x, y,



#  define OGG_MOUSE_UP_EVENT                /* mouse down event */      (12)
#  define OGG_MOUSE_UP_EVENT_ARGS                                       \
        int button, int x, int y,
#  define OGG_MOUSE_UP_EVENT_EXTRACT_ARGS                               \
        int button = va_arg(args, int);                                 \
        int x = va_arg(args, int);                                      \
        int y = va_arg(args, int);
#  define OGG_MOUSE_UP_EVENT_PASS_ARGS                                  \
        button, x, y,



# define OGG_MOUSE_DRAG_BEGIN_EVENT         /* mouse drag begin event */(13)
# define OGG_MOUSE_DRAG_BEGIN_EVENT_ARGS                                \
        int x, int y,
# define OGG_MOUSE_DRAG_BEGIN_EVENT_EXTRACT_ARGS                        \
        int x = va_arg(args, int);                                      \
        int y = va_arg(args, int);
# define OGG_MOUSE_DRAG_BEGIN_EVENT_PASS_ARGS                           \
        x, y,



# define OGG_MOUSE_DRAG_END_EVENT           /* mouse drag end event */  (14)
# define OGG_MOUSE_DRAG_END_EVENT_ARGS                                  \
        int x, int y,
# define OGG_MOUSE_DRAG_END_EVENT_EXTRACT_ARGS                          \
        int x = va_arg(args, int);                                      \
        int y = va_arg(args, int);
# define OGG_MOUSE_DRAG_END_EVENT_PASS_ARGS                             \
        x, y,



# define OGG_FOCUS_EVENT                    /* get focus */             (15)
# define OGG_FOCUS_EVENT_ARGS                                           \
        /* no args */
# define OGG_FOCUS_EVENT_EXTRACT_ARGS                                   \
        /* no args */
# define OGG_FOCUS_EVENT_PASS_ARGS                                      \
        /* no args */



/* glutTimerFunc(
     unsigned int millis,
     void (*func)(int value),
     int value
   ) */
# define OGG_TIMER_EVENT                    /* on timer */              (16)
# define OGG_TIMER_EVENT_ARGS                                           \
        /* no args */
# define OGG_TIMER_EVENT_EXTRACT_ARGS                                   \
        /* no args */
# define OGG_TIMER_EVENT_PASS_ARGS                                      \
        /* no args */



# define OGG_LOSE_FOCUS_EVENT               /* get focus */             (17)
# define OGG_LOSE_FOCUS_EVENT_ARGS                                      \
        /* no args */
# define OGG_LOSE_FOCUS_EVENT_EXTRACT_ARGS                              \
        /* no args */
# define OGG_LOSE_FOCUS_EVENT_PASS_ARGS                                 \
        /* no args */



# define OGG_CREATE_SUB_COMPONENT_EVENT     /* create sub component */  (18)
# define OGG_CREATE_SUB_COMPONENT_EVENT_ARGS                            \
        ogg_component* sub,
# define OGG_CREATE_SUB_COMPONENT_EVENT_EXTRACT_ARGS                    \
        ogg_com_ptr sub = va_arg(args, ogg_com_ptr);
# define OGG_CREATE_SUB_COMPONENT_EVENT_PASS_ARGS                       \
        (ogg_component*)sub,



# define OGG_DESTROY_SUB_COMPONENT_EVENT    /* destroy sub component */ (19)
# define OGG_DESTROY_SUB_COMPONENT_EVENT_ARGS                           \
        ogg_component* sub,
# define OGG_DESTROY_SUB_COMPONENT_EVENT_EXTRACT_ARGS                   \
        ogg_com_ptr sub = va_arg(args, ogg_com_ptr);
# define OGG_DESTROY_SUB_COMPONENT_EVENT_PASS_ARGS                      \
        (ogg_component*)sub,



# define OGG_ACCESS_EVENT                   /* try to access */         (20)
# define OGG_ACCESS_EVENT_ARGS                                          \
        ogg_bool* access,
# define OGG_ACCESS_EVENT_EXTRACT_ARGS                                  \
        ogg_bool* access = va_arg(args, ogg_bool*);
# define OGG_ACCESS_EVENT_PASS_ARGS                                     \
        access,



# define OGG_CAN_ADD_CHILD                  /* if can add child */      (21)
# define OGG_CAN_ADD_CHILD_ARGS                                         \
        void* vptr, ogg_bool* accept,
# define OGG_CAN_ADD_CHILD_EXTRACT_ARGS                                 \
        void* vptr = va_arg(args, void*);                               \
        ogg_bool* accept = va_arg(args, ogg_bool*);
# define OGG_CAN_ADD_CHILD_PASS_ARGS                                    \
        vptr, accept,



/* event type */
# define OGG_CHILD_HANDLE_EVENT                                         (0)
# define OGG_PARENT_HANDLE_EVENT                                        (1)
# define OGG_SELF_HANDLE_EVENT                                          (2)

/* register event type */
extern const event ogg_event_type[];

#endif //OGG_GRPHIC_EVENTS__HEADER_FILE____
