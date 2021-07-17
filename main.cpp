#include <QApplication>
#include <QDebug>
#include <QMetaMethod>
#include <QMetaProperty>

#include "player.h"
#include "editorqgadget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qRegisterMetaType<player::P2D>("player::P2D");
    qRegisterMetaType<player::Player>("player::Player");
    qRegisterMetaType<player::P2D*>("player::P2D*");

    player::Player player;

    player.m_playerType = player::PlayerType::TANK;
    player.m_speed = 25.3;
    player.m_ammunition = 2;
    player.m_active = true;
    player.m_numberOfCoordinates = 2;
    player.m_coordinates = nullptr;
    player.m_coordinates = static_cast<player::P2D*>(std::realloc(player.m_coordinates, sizeof(player::P2D) * player.m_numberOfCoordinates));

    player.m_coordinates[1].m_x = 2.2;
    player.m_coordinates[1].m_y = 3.1;

    player.m_coordinates[0].m_x = 12.1;
    player.m_coordinates[0].m_y = 13.2;

    QVariant test;
    test.setValue(player.m_coordinates);

    EditorQGadget editor("player::Player", &player);
    editor.mostrar();

    return a.exec();
}
