#include "qgadgetfactory.h"

#include <QFrame>
#include <QFormLayout>
#include <QDebug>

#include "elements/combobox.h"
#include "elements/spinbox.h"
#include "elements/doublespinbox.h"
#include "elements/checkbox.h"
#include "elements/ptrwidget.h"

QWidget *qGadgetFactory::decompose(const QString &tipo, void *qGadget)
{
    int metaType = QMetaType::type(tipo.toStdString().c_str());
    const QMetaObject *metaObject = QMetaType::metaObjectForType(metaType);

    auto frame = new QFrame();
    auto layout = new QFormLayout(frame);

    frame->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
    layout->setSizeConstraint(QLayout::SetNoConstraint);


    qDebug() << "META" << metaType;
    qDebug() << "NAME" << metaObject->className();
    qDebug() << "COUNT" << metaObject->propertyCount();

    QWidget* last(nullptr);
    for (int i=0; i <  metaObject->propertyCount(); i++) {
        QMetaProperty metaProperty = metaObject->property(i);
        QVariant read = metaProperty.readOnGadget(qGadget);
        if (metaProperty.isReadable()) {
            if (metaProperty.isEnumType()) {
                last = new ComboBox(metaProperty, qGadget);
                layout->addRow(label(metaProperty.name()), last);

                qDebug() << metaProperty.name() << read.typeName() <<
                            metaProperty.enumerator().valueToKey( metaProperty.readOnGadget(qGadget).toInt() );
            } else {
                switch(static_cast<QMetaType::Type>(read.type())) {
                case QMetaType::Bool:
                    last = new CheckBox(metaProperty, qGadget);
                    layout->addRow(label(metaProperty.name()), last);
                    qDebug() << metaProperty.name() << read.typeName() << read.toBool();
                    break;
                case QMetaType::Float:
                    last = new DoubleSpinBox(metaProperty, qGadget);
                    layout->addRow(label(metaProperty.name()), last);
                    qDebug() << metaProperty.name() << read.typeName() << read.toFloat();
                    break;
                case QMetaType::UChar: // quint8
                case QMetaType::UShort: // quint16
                    last = new SpinBox(metaProperty, qGadget);
                    layout->addRow(label(metaProperty.name()), last);
                    qDebug() << metaProperty.name() << read.typeName() << read.toUInt();
                    break;
                default: // ponteiro ou struct
                    if (QString(read.typeName()).contains('*')) {
                        layout->addRow(label(metaProperty.name()), new PtrWidget(metaProperty, qGadget, last));
                    } else {
                        layout->addRow(label(read.typeName()), decompose(read.typeName(), read.data()));
                    }
                    break;
                }
            }
        }
    }
    frame->adjustSize();
    return frame;
}

QLabel *qGadgetFactory::label(const QString &text)
{
    auto newLabel = new QLabel();
    newLabel->setText(text);

    return newLabel;
}
