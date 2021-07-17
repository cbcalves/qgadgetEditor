#ifndef QGADGETFACTORY_H
#define QGADGETFACTORY_H

#include <QLabel>

class qGadgetFactory
{
public:

    static QWidget* decompose(const QString& tipo, void *qGadget);

    static QLabel* label(const QString& text);

};

#endif // QGADGETFACTORY_H
