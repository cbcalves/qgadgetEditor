#ifndef P2D_H
#define P2D_H

#include <QObject>

namespace  player {

struct P2D {

    Q_GADGET
    Q_PROPERTY(float x MEMBER m_x);
    Q_PROPERTY(float y MEMBER m_y);

public:
    float m_x;
    float m_y;

};

}

Q_DECLARE_METATYPE(player::P2D)
Q_DECLARE_OPAQUE_POINTER(player::P2D*)

#endif // P2D_H
