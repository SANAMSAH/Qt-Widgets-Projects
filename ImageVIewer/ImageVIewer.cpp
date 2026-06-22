#include "ImageVIewer.h"
#include <QFileDialog>
#include <QResizeEvent>

ImageVIewer::ImageVIewer(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    ui.mainToolBar->setIconSize(QSize(24, 24));

    // Center the picture, and let the label shrink/grow freely with the window
    // so the fitted image can be recomputed on every resize.
    ui.label->setAlignment(Qt::AlignCenter);
    ui.label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui.label->setMinimumSize(1, 1);

    statusBar()->showMessage("Ready : ❤️😁");
}

ImageVIewer::~ImageVIewer()
{}

void ImageVIewer::updateImage()
{
    if (m_pixmap.isNull())
        return;

    // KeepAspectRatio = no distortion; SmoothTransformation = nicer quality.
    ui.label->setPixmap(m_pixmap.scaled(ui.label->size(),
                                        Qt::KeepAspectRatio,
                                        Qt::SmoothTransformation));
}

void ImageVIewer::updateStatusBar()
{
    if (m_pixmap.isNull())
        return;

    QString msg = QString(
        "File : %1    Size : %2 x %3    Zoom : %4%")
        .arg(QFileInfo(m_currentFile).fileName())
        .arg(m_pixmap.width())
        .arg(m_pixmap.height())
        .arg(int(m_scaleFactor * 100));

    statusBar()->showMessage(msg);
}

void ImageVIewer::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    updateImage(); 
}

void ImageVIewer::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        
	}
    else if(event->button() == Qt::RightButton)
    {
        
	}
}

void ImageVIewer::mouseMoveEvent(QMouseEvent* event)
{
}

void ImageVIewer::mouseReleaseEvent(QMouseEvent* event)
{
}

void ImageVIewer::paintEvent(QPaintEvent* event)
{
}

void ImageVIewer::on_actionNew_triggered()
{
    const QString file = QFileDialog::getOpenFileName(
        this, tr("Open Image"), "",
        tr("Image Files (*.png *.jpg *.bmp)"));

    if (file.isEmpty())
        return;   // user pressed Cancel

    QPixmap pix(file);
    if (pix.isNull())
    {
        qDebug() << "Failed to load image";
        return;
    }

    m_pixmap = pix;   // keep the original so we can rescale on resize
	m_currentFile = file;
    updateImage();

    updateStatusBar();
}

void ImageVIewer::on_actionOPen_triggered()
{
    const QString file = QFileDialog::getOpenFileName(
        this, tr("Open Image"), "",
        tr("Image Files (*.png *.jpg *.bmp)"));

    if (file.isEmpty())
        return;   // user pressed Cancel

    QPixmap pix(file);
    if (pix.isNull())
    {
        qDebug() << "Failed to load image";
        return;
    }

    m_pixmap = pix;   // keep the original so we can rescale on resize
    m_currentFile = file;
    updateImage();

    updateStatusBar();
}
void ImageVIewer::on_actionZoom_In_triggered()
{
    if (m_pixmap.isNull())
        return;

    double zoomFactor = 1.2;

    
    int newWidth = m_pixmap.width() * zoomFactor;
    int newHeight = m_pixmap.height() * zoomFactor;

    m_pixmap = m_pixmap.scaled(newWidth,
        newHeight,
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation);

	ui.label->setPixmap(m_pixmap);

}
void ImageVIewer::on_actionZoomOut_triggered()
{
    if (m_pixmap.isNull())
        return;
    m_pixmap = m_pixmap.scaled(m_pixmap.size() * 0.8, Qt::KeepAspectRatio, Qt::SmoothTransformation);
   
    ui.label->setPixmap(m_pixmap);
}
void ImageVIewer::on_actionFit_triggered()
{
    if (m_pixmap.isNull())
        return;
    updateImage();
}

void ImageVIewer::on_actionExit_triggered()
{
    QApplication::quit();
}
