#pragma once

#include <QDialog>

class InputEditor : public QDialog
{
    Q_OBJECT
public:
    explicit InputEditor(QWidget *parent = nullptr);

signals:

private slots:
    void cancelButtonClicked();
    void acceptButtonClicked();
};
