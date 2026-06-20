#include "TextEditor.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QRegularExpression>

TextEditor::TextEditor(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	this->setWindowTitle("Text Editor");

    connect(ui.actionNew, &QAction::triggered, this, &TextEditor::newFile);
	connect(ui.actionOpen, &QAction::triggered, this, &TextEditor::openFile);
	connect(ui.actionSave, &QAction::triggered, this, &TextEditor::saveFile);
	connect(ui.actionExit, &QAction::triggered, this, &TextEditor::exitApp);
	
	connect(ui.textEdit,&QTextEdit::textChanged,this,&TextEditor::UpdateStatusBar);
	
	//connect(ui.actionExit, &QAction::triggered, this, &QWidget::close);
	//connect(ui.actionNew, &QAction::triggered, ui.textEdit, &QTextEdit::clear);

}

TextEditor::~TextEditor()
{}

void TextEditor::newFile()
{
	ui.textEdit->clear();

}
void TextEditor::openFile()
{
	QString fileName =
		QFileDialog::getOpenFileName(
			this,
			"Open File",
			"",
			"Text Files (*.txt);;All Files (*.*)");

	if (fileName.isEmpty())
		return;

	QFile file(fileName);

	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QTextStream in(&file);
		ui.textEdit->setPlainText(in.readAll());
		file.close();
	}
}
void TextEditor::saveFile()
{
	QString fileName =
		QFileDialog::getSaveFileName(
			this,
			"Save File",
			"",
			"Text Files (*.txt);;All Files (*.*)");

	if (fileName.isEmpty())
		return;

	QFile file(fileName);

	if (file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QTextStream out(&file);
		out << ui.textEdit->toPlainText();
		file.close();
	}



}
void TextEditor::exitApp()
{
	int ret = QMessageBox::question(this, "Exit", "Save Your Work ", QMessageBox::Yes | QMessageBox::No);
	if (ret == QMessageBox::Yes)
	{
		saveFile();
	}
    close();
}

void TextEditor::UpdateStatusBar()
{
	QString text = ui.textEdit->toPlainText();

	int chars = text.length();

	int words = text.split(
		QRegularExpression("\\s+"),
		Qt::SkipEmptyParts).count();

	statusBar()->showMessage(
		QString("Words: %1   Chars: %2")
		.arg(words)
		.arg(chars));
}
