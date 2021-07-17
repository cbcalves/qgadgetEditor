#ifndef PLAYERTYPE_H
#define PLAYERTYPE_H

#include <QObject>

namespace player {

Q_NAMESPACE

enum class PlayerType {
    NO_TYPE = 0,
    TANK,
    CHARACTER,
    SHIP
};

Q_ENUM_NS(PlayerType)

}

#endif // PLAYERTYPE_H
