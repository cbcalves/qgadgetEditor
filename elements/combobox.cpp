#include "combobox.h"

ComboBox::ComboBox(const QMetaProperty& metaProperty, void* qGadget, QWidget *parent) :
    QComboBox(parent),
    _metaProperty(metaProperty),
    _qGadget(qGadget)
{
    setup();

    QObject::connect(this, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ComboBox::change);
}

void ComboBox::setup()
{
    setEnabled(true);
    setUpdatesEnabled(true);

    QStringList items;

    int keys = _metaProperty.enumerator().keyCount();
    for (int i = 0; i < keys; i++) {
        items.append(_metaProperty.enumerator().key(i));
    }

    addItems(items);

    int selectedKey = _metaProperty.readOnGadget(_qGadget).toInt();
    selectedKey = findText(_metaProperty.enumerator().key(selectedKey));
    setCurrentIndex(selectedKey);
}

void ComboBox::change(int index)
{
    QString selected = itemText(index);
    int currentKey = _metaProperty.enumerator().keysToValue(selected.toStdString().c_str());

    _metaProperty.writeOnGadget(_qGadget, currentKey);
}
