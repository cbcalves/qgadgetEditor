#include "editorqgadget.h"

#include <QFrame>
#include <QFormLayout>
#include <QLabel>
#include <QMetaType>
#include <QMetaProperty>
#include <QDebug>

#include "elements/combobox.h"
#include "elements/spinbox.h"
#include "elements/doublespinbox.h"
#include "elements/checkbox.h"

EditorQGadget::EditorQGadget(const QString &tipo, void *qGadget, QWidget *parent) :
    QMainWindow(parent),
    _tipo(tipo),
    _qGadget(qGadget)
{
    setWindowTitle(QStringLiteral("EditorQGadget [%0]").arg(_tipo));
    setMinimumHeight(600);
    setMinimumWidth(600);
    auto child = decompor(_tipo, _qGadget);
    child->setParent(this);
}

void EditorQGadget::mostrar()
{
    show();
}

QWidget* EditorQGadget::decompor(const QString& tipo, void *qGadget)
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

    for (int i=0; i <  metaObject->propertyCount(); i++) {
        QMetaProperty metaProperty = metaObject->property(i);
        QVariant read = metaProperty.readOnGadget(qGadget);
        if (metaProperty.isReadable()) {
            if (metaProperty.isEnumType()) {
                layout->addRow(label(metaProperty.name()), new ComboBox(metaProperty, qGadget));

                qDebug() << metaProperty.name() << read.typeName() <<
                            metaProperty.enumerator().valueToKey( metaProperty.readOnGadget(qGadget).toInt() );
            } else {
                switch(static_cast<QMetaType::Type>(read.type())) {
                case QMetaType::Bool:
                    layout->addRow(label(metaProperty.name()), new CheckBox(metaProperty, qGadget));
                    qDebug() << metaProperty.name() << read.typeName() << read.toBool();
                    break;
                case QMetaType::Float:
                    layout->addRow(label(metaProperty.name()), new DoubleSpinBox(metaProperty, qGadget));
                    qDebug() << metaProperty.name() << read.typeName() << read.toFloat();
                    break;
                case QMetaType::UChar: // quint8
                case QMetaType::UShort: // quint16
                    layout->addRow(label(metaProperty.name()), new SpinBox(metaProperty, qGadget));
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

                        for (int j = 0; j < metaObject->property( i - 1 ).readOnGadget(qGadget).toInt(); j++) {
                            ptr = static_cast<char *>(ptr) + ptrMetaType.sizeOf() * j;
                            auto child = decompor(readTypeName, ptr);
                            ptrLayout->addRow(label(name + QString::number(j + 1)), child);
                        }
                    } else {
                        layout->addRow(label(read.typeName()), decompor(read.typeName(), read.data()));
                    }
                    break;
                }
            }
        }
    }
    frame->adjustSize();
    return frame;
}

QLabel *EditorQGadget::label(const QString &text)
{
    auto newLabel = new QLabel();
    newLabel->setText(text);

    return newLabel;
}

