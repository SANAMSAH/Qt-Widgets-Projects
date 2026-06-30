#pragma once

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui
{
	class ImageInfoDialog;
}
QT_END_NAMESPACE

class ImageInfoDialog  : public QDialog
{

    Q_OBJECT
public:
    explicit ImageInfoDialog(QWidget* parent = nullptr);
    ~ImageInfoDialog();

private:
    Ui::ImageInfoDialog* ui;

};

