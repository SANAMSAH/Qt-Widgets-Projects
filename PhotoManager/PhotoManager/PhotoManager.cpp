#include "PhotoManager.h"
#include <QFileDialog>

#include <QFileInfo>
#include <QImageReader>

PhotoManager::PhotoManager(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    ui.treeFolders->setColumnWidth(0, 250);

    ui.treeFolders->hideColumn(1); // Size
    ui.treeFolders->hideColumn(2); // Type
    ui.treeFolders->hideColumn(3); // Date
    m_fileModel = new QFileSystemModel(this);
    m_fileModel->setRootPath("");
    ui.treeFolders->setModel(m_fileModel);

    ui.listThumbnails->setViewMode(QListView::IconMode);

    ui.listThumbnails->setIconSize(QSize(128, 128));

    ui.listThumbnails->setResizeMode(QListView::Adjust);

    ui.listThumbnails->setMovement(QListView::Static);
   
    connect(
        ui.listThumbnails,
        &QListWidget::itemClicked,
        this,
        &PhotoManager::onThumbnailClicked);



    ui.tableProperties->setColumnCount(2);

    ui.tableProperties->setHorizontalHeaderLabels(
        {
            "Property",
            "Value"
        });

    ui.tableProperties->horizontalHeader()
        ->setStretchLastSection(true);




	statusBar()->showMessage("Ready");
}

PhotoManager::~PhotoManager()
{
}
void PhotoManager::on_actionOpen_Folder_triggered()
{
    QString folder =
        QFileDialog::getExistingDirectory(
            this,
            "Select Folder",
            QDir::homePath());

    if (folder.isEmpty())
        return;

    

    QModelIndex index =
        m_fileModel->index(folder);

    ui.treeFolders->setRootIndex(index);

    statusBar()->showMessage(folder);

    loadImages(folder);
}

void PhotoManager::loadImages(const QString& folder)
{
    ui.listThumbnails->clear();

    QDir dir(folder);

    QStringList filters;

    filters << "*.png"
        << "*.jpg"
        << "*.jpeg"
        << "*.bmp";

    QFileInfoList files =
        dir.entryInfoList(
            filters,
            QDir::Files);

    for (const QFileInfo& file : files)
    {
        QPixmap pix(file.absoluteFilePath());

        QListWidgetItem* item =
            new QListWidgetItem(
                QIcon(
                    pix.scaled(
                        128,
                        128,
                        Qt::KeepAspectRatio,
                        Qt::SmoothTransformation)),
                file.fileName());

        item->setData(
            Qt::UserRole,
            file.absoluteFilePath());

        ui.listThumbnails->addItem(item);
    }



    statusBar()->showMessage(
        QString("Images: %1")
        .arg(files.count()));
}

void PhotoManager::updateProperties(const QString& imagePath)
{
    QFileInfo info(imagePath);

    QImageReader reader(imagePath);

    QSize size = reader.size();

    ui.tableProperties->setRowCount(5);

    ui.tableProperties->setItem(0, 0, new QTableWidgetItem("File Name"));
    ui.tableProperties->setItem(0, 1, new QTableWidgetItem(info.fileName()));

    ui.tableProperties->setItem(1, 0, new QTableWidgetItem("Width"));
    ui.tableProperties->setItem(1, 1, new QTableWidgetItem(QString::number(size.width())));

    ui.tableProperties->setItem(2, 0, new QTableWidgetItem("Height"));
    ui.tableProperties->setItem(2, 1, new QTableWidgetItem(QString::number(size.height())));

    ui.tableProperties->setItem(3, 0, new QTableWidgetItem("Size"));
    ui.tableProperties->setItem(3, 1, new QTableWidgetItem(
        QString::number(info.size() / 1024.0, 'f', 2) + " KB"));

    ui.tableProperties->setItem(4, 0, new QTableWidgetItem("Format"));
    ui.tableProperties->setItem(4, 1, new QTableWidgetItem(info.suffix().toUpper()));
}

void PhotoManager::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);

    if (m_currentPixmap.isNull())
        return;

    ui.imageLabel->resize(
        ui.scrollArea->viewport()->size());

    ui.imageLabel->setPixmap(
        m_currentPixmap.scaled(
            ui.imageLabel->size(),
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation));
}

void PhotoManager::onThumbnailClicked(QListWidgetItem* item)
{
    QString imagePath =
        item->data(Qt::UserRole).toString();

    m_currentPixmap.load(imagePath);

    if (m_currentPixmap.isNull())
        return;

    m_zoomFactor = 0.5;

    updateImageDisplay();

    updateProperties(imagePath);
}

void PhotoManager::on_actionZoom_In_triggered()
{
    if (m_currentPixmap.isNull())
        return;

    m_zoomFactor *= 1.25;

    updateImageDisplay();
}

void PhotoManager::on_actionZoom_out_triggered()
{
    if (m_currentPixmap.isNull())
        return;

    m_zoomFactor *= 0.8;

    updateImageDisplay();
}

void PhotoManager::on_actionRefresh_triggered()
{
    if (m_currentPixmap.isNull())
        return;

    QSize viewSize =
        ui.scrollArea->viewport()->size();

    double sx =
        (double)viewSize.width() /
        m_currentPixmap.width();

    double sy =
        (double)viewSize.height() /
        m_currentPixmap.height();

    m_zoomFactor = qMin(sx, sy);

    updateImageDisplay();
}

void PhotoManager::updateImageDisplay()
{
    if (m_currentPixmap.isNull())
        return;

    QSize scaledSize =
        m_currentPixmap.size() * m_zoomFactor;

    ui.imageLabel->setPixmap(
        m_currentPixmap.scaled(
            scaledSize,
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation));
}
