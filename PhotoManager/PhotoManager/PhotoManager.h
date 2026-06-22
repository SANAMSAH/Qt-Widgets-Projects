#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PhotoManager.h"

class PhotoManager : public QMainWindow
{
    Q_OBJECT

public:
    PhotoManager(QWidget *parent = nullptr);
    ~PhotoManager();

private:
    Ui::PhotoManagerClass ui;
};

