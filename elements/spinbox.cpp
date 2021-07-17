#include "spinbox.h"

#include <QMetaType>

SpinBox::SpinBox(const QMetaProperty& metaProperty, void* qGadget, QWidget *parent) :
    QSpinBox(parent),
    _metaProperty(metaProperty),
    _qGadget(qGadget)
{
    setup();

    QObject::connect(this, QOverload<int>::of(&QSpinBox::valueChanged), this, &SpinBox::change);
}

void SpinBox::setup()
{

    QVariant read = _metaProperty.readOnGadget(_qGadget);
    setValue(read.toInt());

    int max = USHRT_MAX;
    if (static_cast<QMetaType::Type>(read.type()) == QMetaType::UChar) {
        max = UCHAR_MAX;
    }
    setRange(0, max);

}

void SpinBox::change(int value)
{
    _metaProperty.writeOnGadget(_qGadget, value);
}
