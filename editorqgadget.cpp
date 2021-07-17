#include "editorqgadget.h"

#include <QFrame>
#include <QEventLoop>
#include <QCloseEvent>

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

void EditorQGadget::edit()
{
    QEventLoop event;
    QObject::connect(this, &EditorQGadget::closeProcess, &event, &QEventLoop::quit);
    show();
    event.exec();
}

void EditorQGadget::closeEvent(QCloseEvent *event)
{
    emit closeProcess();
    event->accept();
}
