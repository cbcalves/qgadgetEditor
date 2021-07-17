#include "editorqgadget.h"

#include <QFrame>

#include "elements/qgadgetfactory.h"

EditorQGadget::EditorQGadget(const QString &tipo, void *qGadget, QWidget *parent) :
    QMainWindow(parent),
    _tipo(tipo),
    _qGadget(qGadget)
{
    setWindowTitle(QStringLiteral("EditorQGadget [%0]").arg(_tipo));
    setMinimumHeight(600);
    setMinimumWidth(600);
    auto child = qGadgetFactory::decompose(_tipo, _qGadget);
    child->setParent(this);
}

void EditorQGadget::mostrar()
{
    show();
}
