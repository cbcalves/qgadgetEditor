#include "ptrwidget.h"

#include "elements/spinbox.h"
#include "elements/qgadgetfactory.h"

PtrWidget::PtrWidget(const QMetaProperty& metaProperty, void* qGadget, QWidget *last, QWidget *parent) :
    QFormLayout(parent),
    _metaProperty(metaProperty),
    _qGadget(qGadget),
    _currentSize(0)
{
    auto lastSpinBox = qobject_cast<SpinBox*>(last);
    _currentSize = lastSpinBox->value();

    setup();

    QObject::connect(lastSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &PtrWidget::change);
}

void PtrWidget::setup()
{
    QVariant read = _metaProperty.readOnGadget(_qGadget);
    QString readTypeName(read.typeName());
    readTypeName.remove('*');
    const QMetaType ptrMetaType (QMetaType::type(readTypeName.toStdString().c_str()));
    void *ptr = *(static_cast<void**>(read.data()));

    QString name = _metaProperty.name();
    name.remove(name.size() - 1, 1);

    for (int i = 0; i < _currentSize; i++) {
        ptr = static_cast<char *>(ptr) + ptrMetaType.sizeOf() * i;
        auto child = qGadgetFactory::decompose(readTypeName, ptr);
        addRow(qGadgetFactory::label(name + QString::number(i + 1)), child);
    }
}

void PtrWidget::adjustFrames()
{
    QObject *object = this;
    while (object->parent()) {
        object = object->parent();
        auto frame = qobject_cast<QFrame*>(object);
        if (frame) {
            frame->adjustSize();
        }
    }
}

void PtrWidget::deleteAll()
{
    while (rowCount()) {
        removeRow(0);
    }
}

void PtrWidget::change(int value)
{
    _currentSize = value;
    QVariant read = _metaProperty.readOnGadget(_qGadget);
    QString readTypeName(read.typeName());
    readTypeName.remove('*');
    const QMetaType ptrMetaType (QMetaType::type(readTypeName.toStdString().c_str()));

    auto saveData = static_cast<void**>(read.data());
    auto data = *saveData;
    if (_currentSize > 0) {
        data = std::realloc(data,  ptrMetaType.sizeOf() * _currentSize);
    } else {
        ptrMetaType.destroy(read.userType(), data);
        data = nullptr;
    }
    *saveData = data;

    _metaProperty.writeOnGadget(_qGadget, QVariant(read.userType(), saveData));

    deleteAll();
    setup();
    adjustFrames();
}
