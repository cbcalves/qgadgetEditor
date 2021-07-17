#ifndef SPINBOX_H
#define SPINBOX_H

#include <QSpinBox>
#include <QMetaProperty>

class SpinBox : public QSpinBox
{
    Q_OBJECT

public:
    explicit SpinBox(const QMetaProperty& metaProperty, void* qGadget, QWidget *parent = nullptr);

private:
    QMetaProperty _metaProperty;
    void* _qGadget;

    void setup();

private slots:
    void change(int value);
};

#endif // SPINBOX_H
