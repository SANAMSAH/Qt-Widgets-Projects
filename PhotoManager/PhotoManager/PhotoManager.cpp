#include "PhotoManager.h"

PhotoManager::PhotoManager(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	statusBar()->showMessage("Ready");
}

PhotoManager::~PhotoManager()
{
}

