#include "qgadgetfactory.h"

#include <QFrame>
#include <QFormLayout>

#include "elements/combobox.h"
#include "elements/spinbox.h"
#include "elements/doublespinbox.h"
#include "elements/checkbox.h"
#include "elements/ptrformlayout.h"

QWidget *qGadgetFactory::decompose(const QString &tipo, void *qGadget)
{
    int metaType = QMetaType::type(tipo.toStdString().c_str());
    const QMetaObject *metaObject = QMetaType::metaObjectForType(metaType);

    auto frame = new QFrame();
    auto layout = new QFormLayout(frame);

    layout->setSizeConstraint(QLayout::SetFixedSize);

    QWidget* last(nullptr);
    for (int i=0; i <  metaObject->propertyCount(); i++) {
        QMetaProperty metaProperty = metaObject->property(i);
        QVariant read = metaProperty.readOnGadget(qGadget);
        if (metaProperty.isReadable()) {
            if (metaProperty.isEnumType()) {
                last = new ComboBox(metaProperty, qGadget);
                layout->addRow(label(metaProperty.name()), last);
            } else {
                switch(static_cast<QMetaType::Type>(read.type())) {
                case QMetaType::Bool:
                    last = new CheckBox(metaProperty, qGadget);
                    layout->addRow(label(metaProperty.name()), last);
                    break;
                case QMetaType::Float:
                    last = new DoubleSpinBox(metaProperty, qGadget);
                    layout->addRow(label(metaProperty.name()), last);
                    break;
                case QMetaType::UChar: // quint8
                case QMetaType::UShort: // quint16
                    last = new SpinBox(metaProperty, qGadget);
                    layout->addRow(label(metaProperty.name()), last);
                    break;
                default: // ponteiro ou struct
                    if (QString(read.typeName()).contains('*')) {
                        layout->addRow(label(metaProperty.name()), new PtrFormLayout(metaProperty, qGadget, last));
                        last = nullptr;
                    } else {
                        last = decompose(read.typeName(), read.data());
                        layout->addRow(label(read.typeName()), last);
                    }
                    break;
                }
            }
        }
    }
    return frame;
}

QLabel *qGadgetFactory::label(const QString &text)
{
    auto newLabel = new QLabel();
    newLabel->setText(text);

    return newLabel;
}
