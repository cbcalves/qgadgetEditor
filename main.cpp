#include <QApplication>
#include <QDebug>
#include <QMetaMethod>
#include <QMetaProperty>

#include "players/playerbuilder.h"
#include "editorqgadget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qRegisterMetaType<player::P2D>("player::P2D");
    qRegisterMetaType<player::Player>("player::Player");
    qRegisterMetaType<player::P2D*>("player::P2D*");

    player::Player player = player::PlayerBuilder::build(player::PlayerType::TANK, 25.3, 2, true, 2);

    player.m_coordinates[1].m_x = 2.2;
    player.m_coordinates[1].m_y = 3.1;

    player.m_coordinates[0].m_x = 12.1;
    player.m_coordinates[0].m_y = 13.2;

    QVariant test;
    test.setValue(player.m_coordinates);

    EditorQGadget editor("player::Player", &player);
    editor.edit();

    std::free(player.m_coordinates);

    return EXIT_SUCCESS;
}
