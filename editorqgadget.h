#ifndef EDITORQGADGET_H
#define EDITORQGADGET_H

#include <QMainWindow>

class EditorQGadget : public QMainWindow
{

    Q_OBJECT

public:
    EditorQGadget(const QString& tipo, void *qGadget, QWidget* parent = nullptr);

    void mostrar();

private:
    QString _tipo;
    void *_qGadget;
};

#endif // EDITORQGADGET_H
