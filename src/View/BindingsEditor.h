#pragma once

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
