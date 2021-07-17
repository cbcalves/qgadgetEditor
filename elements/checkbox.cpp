#include "checkbox.h"

CheckBox::CheckBox(const QMetaProperty& metaProperty, void* qGadget, QWidget *parent) :
    QCheckBox(parent),
    _metaProperty(metaProperty),
    _qGadget(qGadget)
{
    setup();

    QObject::connect(this, &QCheckBox::stateChanged, this, &CheckBox::change);
}

void CheckBox::setup()
{
    setCheckState(Qt::CheckState::Unchecked);

    QVariant read = _metaProperty.readOnGadget(_qGadget);
    if (read.toBool()) {
        setCheckState(Qt::CheckState::Checked);
    }
}

void CheckBox::change(int state)
{
    _metaProperty.writeOnGadget(_qGadget, state);
}
