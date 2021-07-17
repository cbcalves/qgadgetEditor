#include "qgadgetfactory.h"

#include <QFrame>
#include <QFormLayout>
#include <QDebug>

#include "elements/combobox.h"
#include "elements/spinbox.h"
#include "elements/doublespinbox.h"
#include "elements/checkbox.h"

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
                        QString readTypeName(read.typeName());
                        readTypeName.remove('*');
                        const QMetaType ptrMetaType (QMetaType::type(readTypeName.toStdString().c_str()));
                        void *ptr = *(static_cast<void**>(read.data()));

                        auto ptrLayout = new QFormLayout();

                        QString name = metaProperty.name();
                        layout->addRow(label(name), ptrLayout);
                        name.remove(name.size() - 1, 1);

                        for (int j = 0; j < qobject_cast<SpinBox*>(last)->value(); j++) {
                            ptr = static_cast<char *>(ptr) + ptrMetaType.sizeOf() * j;
                            auto child = decompose(readTypeName, ptr);
                            ptrLayout->addRow(label(name + QString::number(j + 1)), child);
                        }
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
