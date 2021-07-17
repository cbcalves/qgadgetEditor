#ifndef EDITORQGADGET_H
#define EDITORQGADGET_H

#include <QMainWindow>
#include <QLabel>

class EditorQGadget : public QMainWindow
{

    Q_OBJECT

public:
    EditorQGadget(const QString& tipo, void *qGadget, QWidget* parent = nullptr);

    void mostrar();

private:
    QString _tipo;
    void *_qGadget;

    void decompor(const QString& tipo, void *qGadget, QWidget* parent);

    QLabel* label(const QString& text);

};

#endif // EDITORQGADGET_H
