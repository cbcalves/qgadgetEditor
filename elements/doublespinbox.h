#ifndef DOUBLESPINBOX_H
#define DOUBLESPINBOX_H

#include <QDoubleSpinBox>
#include <QMetaProperty>

class DoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT

public:
    explicit DoubleSpinBox(const QMetaProperty& metaProperty, void* qGadget, QWidget *parent = nullptr);

private:
    QMetaProperty _metaProperty;
    void* _qGadget;

    void setup();

private slots:
    void change(double value);
};

#endif // DOUBLESPINBOX_H
