#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

#include "playertype.h"
#include "p2d.h"

namespace player {

struct Player {

    Q_GADGET
    Q_PROPERTY(player::PlayerType playerType MEMBER m_playerType);
    Q_PROPERTY(float speed MEMBER m_speed);
    Q_PROPERTY(quint16 ammunition MEMBER m_ammunition);
    Q_PROPERTY(bool active MEMBER m_active);
    Q_PROPERTY(quint8 numberOfCoordinates MEMBER m_numberOfCoordinates);
    Q_PROPERTY(player::P2D* coordinates MEMBER m_coordinates);

public:
    PlayerType m_playerType;
    float m_speed;
    quint16 m_ammunition;
    bool m_active;
    quint8 m_numberOfCoordinates;
    P2D *m_coordinates;

};

}

Q_DECLARE_METATYPE(player::Player);

#endif // PLAYER_H
