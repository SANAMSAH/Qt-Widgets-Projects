#include "PaintApp.h"
#include <QColorDialog>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>

using namespace Qt;
PaintApp::PaintApp(QWidget *parent)
    : QMainWindow(parent)
{
   ui.setupUi(this);

   m_canvasWidget =   new PaintCanvas(this);
   setCentralWidget(m_canvasWidget);
	
   m_canvasWidget->setTool(DrawTool::Pen);
   createToolBar_Events();
   createSignleSlots();  

   statusBar()->showMessage("QT PaintApp By : Sanam Sah ");
	
}

PaintApp::~PaintApp()
{}

void PaintApp::on_actionColorPicker_triggered()
{
    QColor color =
        QColorDialog::getColor(
            m_canvasWidget->m_penColor,
            this);

    if (color.isValid())
    {
        m_canvasWidget->setPenColor(
            color);
    }
}

void PaintApp::on_actionEraser_triggered()
{
    m_canvasWidget->setEraserMode(ui.actionEraser->isChecked());
    m_canvasWidget->setTool(DrawTool::Eraser);
    ui.actionRectangle->setChecked(false);
    ui.actionPen->setChecked(false);
    ui.actionCIrcle->setChecked(false);
}

void PaintApp::on_actionPen_triggered()
{
	m_canvasWidget->setTool( DrawTool::Pen);
	ui.actionRectangle->setChecked(false);
	ui.actionEraser->setChecked(false);
    ui.actionCIrcle->setChecked(false);
    m_canvasWidget->setEraserMode(ui.actionEraser->isChecked());
}

void PaintApp::on_actionRectangle_triggered()
{
    m_canvasWidget->setTool(DrawTool::Rectangle);
	ui.actionPen->setChecked(false);
    ui.actionEraser->setChecked(false);
	ui.actionCIrcle->setChecked(false);
    m_canvasWidget->setEraserMode(ui.actionEraser->isChecked());

}

void PaintApp::on_actionCIrcle_triggered()
{
    m_canvasWidget->setTool(DrawTool::Ellipse);
    ui.actionPen->setChecked(false);
    ui.actionEraser->setChecked(false);
    ui.actionRectangle->setChecked(false);
    m_canvasWidget->setEraserMode(ui.actionEraser->isChecked());

}

void PaintApp::createToolBar_Events()
{
    m_penWidthSpinBox = new QSpinBox(this);

    m_penWidthSpinBox->setRange(1, 50);
    m_penWidthSpinBox->setValue(3);


    ui.mainToolBar->addSeparator();
    ui.mainToolBar->addWidget(new QLabel("Width:", this));


    ui.mainToolBar->addWidget(m_penWidthSpinBox);

    ui.actionEraser->setCheckable(true);
	ui.actionPen->setCheckable(true);
	ui.actionRectangle->setCheckable(true);
    ui.actionPen->setChecked(true);
    ui.actionCIrcle->setCheckable(true);
}

void PaintApp::createSignleSlots()
{

    connect(m_penWidthSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), m_canvasWidget, &PaintCanvas::setPenWidth);
}


void PaintApp::on_actionSaveImage_triggered()
{
    QString fileName =
        QFileDialog::getSaveFileName(
            this,
            "Save Image",
            "",
            "PNG Files (*.png);;JPEG Files (*.jpg);;Bitmap Files (*.bmp)");

    if (fileName.isEmpty())
        return;

    if (m_canvasWidget->saveImage(fileName))
    {
        QMessageBox::information(
            this,
            "Success",
            "Image saved successfully.");
    }
    else
    {
        QMessageBox::critical(
            this,
            "Error",
            "Failed to save image.");
    }
}

void PaintApp::on_actionNewImage_triggered()
{
    m_canvasWidget->clearCanvas();
}

void PaintApp::on_actionOpen_image_triggered()
{
    QString fileName =
        QFileDialog::getOpenFileName(
            this,
            "Open Image",
            "",
            "Images (*.png *.jpg *.bmp)");

    if (fileName.isEmpty())
        return;

    m_canvasWidget->loadImage(fileName);
}
