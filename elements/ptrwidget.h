#ifndef PTRWIDGET_H
#define PTRWIDGET_H

#include <QWidget>
#include <QFrame>
#include <QFormLayout>
#include <QMetaProperty>

class PtrWidget : public QFormLayout
{
    Q_OBJECT

public:
    explicit PtrWidget(const QMetaProperty& metaProperty, void* qGadget, QWidget *last, QWidget *parent = nullptr);

private:
    QMetaProperty _metaProperty;
    void* _qGadget;
    int _currentSize;

    void setup();
    void adjustFrames();
    void deleteAll();

private slots:
    void change(int value);
};

#endif // PTRWIDGET_H
