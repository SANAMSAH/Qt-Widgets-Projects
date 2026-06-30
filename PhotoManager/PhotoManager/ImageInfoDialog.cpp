#include "ImageInfoDialog.h"
#include "ui_ImageInfoDialog.h"

#include <QHeaderView>
#include <QAbstractItemView>
#include <QPushButton>

ImageInfoDialog::ImageInfoDialog(QWidget* parent)
    : QDialog(parent),
      ui(new Ui::ImageInfoDialog)
{
    ui->setupUi(this);

    // Table setup
    ui->tableProperties->setColumnCount(2);

    QStringList headers;
    headers << "Property" << "Value";

    ui->tableProperties->setHorizontalHeaderLabels(headers);

    ui->tableProperties->horizontalHeader()->setStretchLastSection(true);

    ui->tableProperties->verticalHeader()->hide();

    ui->tableProperties->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableProperties->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableProperties->setAlternatingRowColors(true);

    // Close button
    connect(ui->btnClose,
        &QPushButton::clicked,
        this,
        &QDialog::accept);
}

ImageInfoDialog::~ImageInfoDialog()
{
    delete ui;
}

