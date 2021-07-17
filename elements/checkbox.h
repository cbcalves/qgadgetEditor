#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <QCheckBox>
#include <QMetaProperty>

class CheckBox : public QCheckBox
{
    Q_OBJECT

public:
    explicit CheckBox(const QMetaProperty& metaProperty, void* qGadget, QWidget *parent = nullptr);

private:
    QMetaProperty _metaProperty;
    void* _qGadget;

    void setup();

private slots:
    void change(int state);
};

#endif // CHECKBOX_H
