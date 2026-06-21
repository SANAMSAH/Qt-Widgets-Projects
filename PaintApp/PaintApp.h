#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PaintApp.h"
#include <QPoint>
#include <QMouseEvent>
#include <QPainter>
#include <QColor>
#include "PaintCanvas.h"
#include <QSpinBox>


QT_BEGIN_NAMESPACE
namespace ui {
    class PaintAppClass;
}

class PaintApp : public QMainWindow
{
    Q_OBJECT

public:
    PaintApp(QWidget *parent = nullptr);
    ~PaintApp();

protected:

    void createToolBar_Events();
    void createSignleSlots();
    


private slots:
  
	void on_actionSaveImage_triggered();
	void on_actionNewImage_triggered();
	void on_actionOpen_image_triggered();
    void on_actionColorPicker_triggered();
	void on_actionEraser_triggered();
	void on_actionPen_triggered();
	void on_actionRectangle_triggered();
	void on_actionCIrcle_triggered();


private:
    PaintCanvas* m_canvasWidget;
    QSpinBox* m_penWidthSpinBox;
    Ui::PaintAppClass ui;

    
};

