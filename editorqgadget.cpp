#include "editorqgadget.h"

#include <QFrame>
#include <QFormLayout>
#include <QLabel>
#include <QMetaType>
#include <QMetaProperty>
#include <QDebug>

#include "elements/combobox.h"

EditorQGadget::EditorQGadget(const QString &tipo, void *qGadget, QWidget *parent) :
    QMainWindow(parent),
    _tipo(tipo),
    _qGadget(qGadget)
{
    setMinimumHeight(600);
    setMinimumWidth(600);
    decompor(_tipo, _qGadget, this);
}

void EditorQGadget::mostrar()
{
    show();
}

void EditorQGadget::decompor(const QString& tipo, void *qGadget, QWidget* parent)
{
    int metaType = QMetaType::type(tipo.toStdString().c_str());
    const QMetaObject *metaObject = QMetaType::metaObjectForType(metaType);

    if (parent == this) {
        setWindowTitle(QStringLiteral("EditorQGadget [%0]").arg(metaObject->className()));
    }

    auto frame = new QFrame(parent);
    auto layout = new QFormLayout(frame);

    frame->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
    frame->setGeometry(QRect(0, 0, 600, 600));
    layout->setSizeConstraint(QLayout::SetNoConstraint);
    layout->setGeometry(frame->geometry());


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
                    qDebug() << metaProperty.name() << read.typeName() << read.toBool();
                    break;
                case QMetaType::Float:
                    qDebug() << metaProperty.name() << read.typeName() << read.toFloat();
                    break;
                case QMetaType::UChar: // quint8
                case QMetaType::UShort: // quint16
                    qDebug() << metaProperty.name() << read.typeName() << read.toUInt();
                    break;
                default: // ponteiro ou struct
                    if (QString(read.typeName()).contains('*')) {
                        QString readTypeName(read.typeName());
                        readTypeName.remove('*');
                        const QMetaType ptrMetaType (QMetaType::type(readTypeName.toStdString().c_str()));
                        void *ptr = *(static_cast<void**>(read.data()));

                        for (int j = 0; j < metaObject->property( i - 1 ).readOnGadget(qGadget).toInt(); j++) {
                            ptr = static_cast<char *>(ptr) + ptrMetaType.sizeOf() * j;
                            decompor(readTypeName,  ptr, frame);
                        }
                    } else {
                        decompor(read.typeName(), read.data(), frame);
                    }
                    break;
                }
            }
        }
    }
}

QLabel *EditorQGadget::label(const QString &text)
{
    auto newLabel = new QLabel();
    newLabel->setText(text);

    return newLabel;
}

