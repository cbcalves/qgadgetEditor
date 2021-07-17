#ifndef PTRFORMLAYOUT_H
#define PTRFORMLAYOUT_H

#include <QFormLayout>
#include <QMetaProperty>

class PtrFormLayout : public QFormLayout
{
    Q_OBJECT

public:
    explicit PtrFormLayout(const QMetaProperty& metaProperty, void* qGadget, QWidget *last, QWidget *parent = nullptr);

private:
    QMetaProperty _metaProperty;
    void* _qGadget;
    int _currentSize;

    void setup();
    void deleteAll();

private slots:
    void change(int value);
};

#endif // PTRFORMLAYOUT_H
