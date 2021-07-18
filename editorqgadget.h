#ifndef EDITORQGADGET_H
#define EDITORQGADGET_H

#include <QWidget>

class EditorQGadget : public QWidget
{

    Q_OBJECT

public:
    EditorQGadget(const QString& tipo, void *qGadget, QWidget* parent = nullptr);

    void edit();

signals:
    void closeProcess();

protected:
    void closeEvent(QCloseEvent *event) override;

};

#endif // EDITORQGADGET_H
