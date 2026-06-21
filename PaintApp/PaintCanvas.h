#pragma once
#include <QWidget>
#include <QPixmap>
#include <QPoint>
#include <QPainter>
#include <QMouseEvent>


enum class DrawTool
{
	Pen,
	Eraser,
	Rectangle,
	Ellipse,
};

class PaintCanvas :   public QWidget
{
	Q_OBJECT

public:
	QColor m_penColor = Qt::black;
	explicit PaintCanvas(QWidget *parent = nullptr);
	~PaintCanvas();

	void clearCanvas();

	void setPenColor(const QColor& color);

	void setPenWidth(int width);

	bool saveImage(const QString& fileName);
	void loadImage(const QString& fileName);
	void setEraserMode(bool enable);

	void setTool(DrawTool tool);

protected:
	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void resizeEvent(QResizeEvent* event) override;

private:
	QPixmap m_canvas;
	QPoint m_lastPoint;
	bool m_drawing = false;
	bool m_eraserMode = false;

	QPoint m_startPoint;
	QPoint m_endPoint;

	DrawTool m_currentTool = DrawTool::Pen;

	int m_penWidth = 3;
};

