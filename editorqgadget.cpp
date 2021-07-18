#include "editorqgadget.h"

#include <QFrame>
#include <QVBoxLayout>
#include <QEventLoop>
#include <QCloseEvent>

#include "elements/qgadgetfactory.h"

EditorQGadget::EditorQGadget(const QString &tipo, void *qGadget, QWidget *parent) :
    QWidget(parent)
{
    setWindowTitle(QStringLiteral("EditorQGadget [%0]").arg(tipo));

    auto boxlayout = new QVBoxLayout;
    setLayout(boxlayout);
    boxlayout->setSizeConstraint(QLayout::SetFixedSize);

    auto child = qGadgetFactory::decompose(tipo, qGadget);
    boxlayout->addWidget(child);
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
