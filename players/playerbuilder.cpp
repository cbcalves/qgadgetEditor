#include "playerbuilder.h"

using namespace player;

Player PlayerBuilder::build(PlayerType playerType, float speed, quint16 ammunition, bool active, quint8 nrCoordinates)
{
    Player player;
    player.m_playerType = playerType;
    player.m_speed = speed;
    player.m_ammunition = ammunition;
    player.m_active = active;
    player.m_numberOfCoordinates = nrCoordinates;
    player.m_coordinates = nullptr;

    if (nrCoordinates) {
        player.m_coordinates = static_cast<player::P2D*>(std::realloc(player.m_coordinates, sizeof(player::P2D) * player.m_numberOfCoordinates));
        memset(player.m_coordinates, 0, sizeof(player::P2D) * player.m_numberOfCoordinates);
    }

    return player;
}

void PlayerBuilder::destructor(Player *player)
{
    std::free(player->m_coordinates);
}

