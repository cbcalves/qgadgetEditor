#include "doublespinbox.h"

DoubleSpinBox::DoubleSpinBox(const QMetaProperty& metaProperty, void* qGadget, QWidget *parent) :
    QDoubleSpinBox(parent),
    _metaProperty(metaProperty),
    _qGadget(qGadget)
{
    setup();

    QObject::connect(this, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &DoubleSpinBox::change);
}

void DoubleSpinBox::setup()
{
    QVariant read = _metaProperty.readOnGadget(_qGadget);
    setValue(read.toFloat());

    setSingleStep(0.01);
}

void DoubleSpinBox::change(double value)
{
    _metaProperty.writeOnGadget(_qGadget, value);
}
