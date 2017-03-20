#ifndef OGG_GEOMETRY__HEADER_FILE___
#define OGG_GEOMETRY__HEADER_FILE___
#include <math.h>

#define register_geometry_system(T, id) /* register a geometry system by given type */\
typedef struct {\
    T x, y;\
} point##id;\
\
typedef point##id coord##id;\
typedef struct {\
    T x, y;\
} vector##id;\
\
typedef struct {\
    point##id u, v;\
} segment##id;\
\
typedef struct {\
    union {\
        struct {\
            point##id top_left, bottom_right;\
        };\
        struct {\
            T left, top, right, bottom;\
        };\
    };\
} rect##id;

#define inst_geometry_system(T, id) /* inst a geometry system */\
vector##id make_vector##id(point##id s, point##id t) {\
    vector##id vec; vec.x = t.x - s.x, vec.y = t.y - s.y;\
    return vec;\
}\
vector##id add_vector##id(vector##id lhs, vector##id rhs) {\
    lhs.x += rhs.x; lhs.y += rhs.y;\
    return lhs;\
}\
vector##id sub_vector##id(vector##id lhs, vector##id rhs) {\
    lhs.x -= rhs.x; lhs.y -= rhs.y;\
    return lhs;\
}\
double norm##id(vector##id v){\
    return sqrt(v.x * v.x + v.y * v.y);\
}\
T inner_product##id(vector##id lhs, vector##id rhs) {\
    return lhs.x * rhs.x + lhs.y * rhs.y;\
}\
T outer_product##id(vector##id lhs, vector##id rhs) {\
    return lhs.x * rhs.y - rhs.x * lhs.y;\
}\
double angle##id(vector##id lhs, vector##id rhs) {\
    return acos((double)inner_product##id(lhs, rhs)/(norm##id(lhs)*norm##id(rhs)));\
}

#endif //OGG_GEOMETRY__HEADER_FILE___