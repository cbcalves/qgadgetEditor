#include "ptrformlayout.h"

#include <QtGlobal>

#include "elements/spinbox.h"
#include "elements/qgadgetfactory.h"

PtrFormLayout::PtrFormLayout(const QMetaProperty& metaProperty, void* qGadget, QWidget *last, QWidget *parent) :
    QFormLayout(parent),
    _metaProperty(metaProperty),
    _qGadget(qGadget),
    _currentSize(0)
{
    auto lastSpinBox = qobject_cast<SpinBox*>(last);
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

#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
    const QMetaType ptrMetaType(QMetaType::fromName(readTypeName.toUtf8()));
#else
    const QMetaType ptrMetaType(QMetaType::type(readTypeName.toUtf8()));
#endif

    void *ptrData = *(static_cast<void**>(read.data()));

    QString labelText = _metaProperty.name();
    labelText.remove(labelText.size() - 1, 1);

    for (int i = 0; i < _currentSize; ++i) {
        void* currentPtr = static_cast<char *>(ptrData) + ptrMetaType.sizeOf() * i;
        auto child = qGadgetFactory::decompose(readTypeName, currentPtr);
        addRow(qGadgetFactory::label(labelText + QString::number(i + 1)), child);
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

#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
    const QMetaType ptrMetaType(QMetaType::fromName(readTypeName.toUtf8()));
#else
    const QMetaType ptrMetaType(QMetaType::type(readTypeName.toUtf8()));
#endif

    auto saveData = static_cast<void**>(read.data());
    auto data = *saveData;
    if (value > 0 && ptrMetaType.sizeOf()) {
        data = std::realloc(data,  ptrMetaType.sizeOf() * value);
        for (int i = _currentSize; i < value; ++i) {
            auto ptr = static_cast<char*>(data) + (ptrMetaType.sizeOf() * i);
            memset(ptr, 0, ptrMetaType.sizeOf());
        }
    } else {
       std::free(data);
       data = nullptr;
    }
    *saveData = data;

    _metaProperty.writeOnGadget(_qGadget, read);
    _currentSize = value;

    deleteAll();
    setup();
}
