#pragma once

#include <QtWidgets/QMainWindow>
#include <QFileSystemModel>



#include "ui_PhotoManager.h"

class PhotoManager : public QMainWindow
{
    Q_OBJECT

public:
    PhotoManager(QWidget *parent = nullptr);
    ~PhotoManager();

private :
    void loadImages(const QString& folder);
    void updateProperties(const QString& imagePath);

    void updateImageDisplay();
protected:
	void resizeEvent(QResizeEvent* event) override;
private slots:
	void on_actionOpen_Folder_triggered();
    void onThumbnailClicked(QListWidgetItem* item);
    void on_actionZoom_In_triggered();
    void on_actionZoom_out_triggered();
    void on_actionRefresh_triggered();

private:
    Ui::PhotoManagerClass ui;

	QFileSystemModel* m_fileModel = nullptr;

    QPixmap m_currentPixmap;

    double m_zoomFactor = 1.0;

};

