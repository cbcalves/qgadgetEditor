#ifndef PLAYERBUILDER_H
#define PLAYERBUILDER_H

#include "player.h"

namespace player {

class PlayerBuilder
{
public:
    static Player build(PlayerType playerType, float speed, quint16 ammunition, bool active, quint8 nrCoordinates);

    static void destructor(Player* player);
};

}

#endif // PLAYERBUILDER_H
