#include "ptrformlayout.h"

#include "elements/spinbox.h"
#include "elements/qgadgetfactory.h"

PtrFormLayout::PtrFormLayout(const QMetaProperty& metaProperty, void* qGadget, QWidget *last, QWidget *parent) :
    QFormLayout(parent),
    _metaProperty(metaProperty),
    _qGadget(qGadget),
    _currentSize(0)
{
    auto lastSpinBox = qobject_cast<SpinBox*>(last);
    lastSpinBox->setMinimum(1);
    _currentSize = lastSpinBox->value();

    setSizeConstraint(QLayout::SetFixedSize);

    setup();

    QObject::connect(lastSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &PtrFormLayout::change);
}

void PtrFormLayout::setup()
{
    QVariant read = _metaProperty.readOnGadget(_qGadget);
    QString readTypeName(read.typeName());
    readTypeName.remove('*');
    const QMetaType ptrMetaType (QMetaType::type(readTypeName.toStdString().c_str()));
    void *ptr = *(static_cast<void**>(read.data()));

    QString name = _metaProperty.name();
    name.remove(name.size() - 1, 1);

    for (int i = 0; i < _currentSize; i++) {
        void* showptr = static_cast<char *>(ptr) + ptrMetaType.sizeOf() * i;
        auto child = qGadgetFactory::decompose(readTypeName, showptr);
        addRow(qGadgetFactory::label(name + QString::number(i + 1)), child);
    }
}

void PtrFormLayout::deleteAll()
{
    while (rowCount()) {
        removeRow(0);
    }
}

void PtrFormLayout::change(int value)
{
    QVariant read = _metaProperty.readOnGadget(_qGadget);
    QString readTypeName(read.typeName());
    readTypeName.remove('*');
    const QMetaType ptrMetaType (QMetaType::type(readTypeName.toStdString().c_str()));

    auto saveData = static_cast<void**>(read.data());
    auto data = *saveData;
    if (_currentSize > 0) {
        data = std::realloc(data,  ptrMetaType.sizeOf() * value);
        for (int i = _currentSize; i < value; i++) {
            auto ptr = static_cast<char*>(data) + (ptrMetaType.sizeOf() * i);
            memset(ptr, 0, ptrMetaType.sizeOf());
        }
    }
    *saveData = data;

    _metaProperty.writeOnGadget(_qGadget, QVariant(read.userType(), saveData));
    _currentSize = value;

    deleteAll();
    setup();
}
