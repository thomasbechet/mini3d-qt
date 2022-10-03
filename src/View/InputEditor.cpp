#include "InputEditor.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QLabel>

InputEditor::InputEditor(QWidget *parent)
    : QDialog{parent}
{
    // Configure layouts
    setWindowTitle("Bindings");

    // Configure layouts
    QVBoxLayout *mainLayout = new QVBoxLayout();

    // Create bindings table
    QTableWidget *table = new QTableWidget(0, 1);
    for (int i = 0; i < 10; i++) {
        table->insertRow(i);
        QTableWidgetItem *item = new QTableWidgetItem("Test");
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        table->setItem(i, 0, item);
    }
    mainLayout->addWidget(table);

    // Bottom layout
    QPushButton *cancelButton = new QPushButton("Cancel");
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonClicked()));
    QPushButton *acceptButton = new QPushButton("Accept");
    acceptButton->setDefault(true);
    connect(acceptButton, SIGNAL(clicked()), this, SLOT(acceptButtonClicked()));

    QHBoxLayout *bottomLayout = new QHBoxLayout();
    bottomLayout->setAlignment(Qt::AlignmentFlag::AlignRight);
    bottomLayout->addWidget(cancelButton, 0, Qt::AlignBottom);
    bottomLayout->addWidget(acceptButton, 0, Qt::AlignBottom);
    mainLayout->addLayout(bottomLayout);

    setLayout(mainLayout);
}

void InputEditor::cancelButtonClicked()
{
    reject();
}
void InputEditor::acceptButtonClicked()
{
    accept();
}
