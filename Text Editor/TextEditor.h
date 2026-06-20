#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TextEditor.h"

class TextEditor : public QMainWindow
{
    Q_OBJECT

public:
    TextEditor(QWidget *parent = nullptr);
    ~TextEditor();

private:
    Ui::TextEditorClass ui;

private slots:
    void newFile();
    void openFile();
    void saveFile();
	void exitApp();
    void UpdateStatusBar();


};

