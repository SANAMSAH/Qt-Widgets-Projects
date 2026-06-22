#pragma once

#include <QtWidgets/QMainWindow>
#include <QPixmap>
#include "ui_ImageVIewer.h"

class ImageVIewer : public QMainWindow
{
    Q_OBJECT

public:
    ImageVIewer(QWidget *parent = nullptr);
    ~ImageVIewer();

public:
	void updateStatusBar();

protected:
    void resizeEvent(QResizeEvent *event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void paintEvent(QPaintEvent* event) override;


private slots:
    void on_actionNew_triggered();
    void on_actionOPen_triggered();
	void on_actionZoom_In_triggered();
	void on_actionZoomOut_triggered();
	void on_actionFit_triggered();
	void on_actionExit_triggered();

private:
    void updateImage();        // rescale m_pixmap to fit the label

    QPixmap m_pixmap;          // original, full-resolution image
    Ui::ImageVIewerClass ui;
	QString m_currentFile;
    double m_scaleFactor = 1.0;
};
