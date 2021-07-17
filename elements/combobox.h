#ifndef COMBOBOX_H
#define COMBOBOX_H

#include <QComboBox>
#include <QMetaProperty>

class ComboBox : public QComboBox
{
    Q_OBJECT

public:
    explicit ComboBox(const QMetaProperty& metaProperty, void* qGadget, QWidget *parent = nullptr);

private:
    QMetaProperty _metaProperty;
    void* _qGadget;

    void setup();

private slots:
    void change(int index);
};

#endif // COMBOBOX_H
