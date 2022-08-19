#ifndef BINDINGSWINDOW_H
#define BINDINGSWINDOW_H

#include <QDialog>

class BindingsEditor : public QDialog
{
    Q_OBJECT
public:
    explicit BindingsEditor(QWidget *parent = nullptr);

signals:

private slots:
    void cancelButtonClicked();
    void acceptButtonClicked();
};

#endif // BINDINGSWINDOW_H
