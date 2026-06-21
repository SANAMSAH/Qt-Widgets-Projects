#include "PaintCanvas.h"

PaintCanvas::PaintCanvas(QWidget* parent)
{
	setAttribute(Qt::WA_StaticContents);
	
	m_canvas = QPixmap(800, 600);

	m_canvas.fill(Qt::white);

}


PaintCanvas::~PaintCanvas()
{
}

void PaintCanvas::clearCanvas()
{
    m_canvas.fill(Qt::white);

    update();
}

void PaintCanvas::setPenColor(const QColor& color)
{
    m_penColor = color;
}

void PaintCanvas::setPenWidth(int width)
{
    m_penWidth = width;
}
bool PaintCanvas::saveImage(const QString& fileName)
{
    return m_canvas.save(fileName);
}
void PaintCanvas::loadImage(const QString& fileName)
{
    QPixmap loadedImage(fileName);

    if (!loadedImage.isNull())
    {
        m_canvas = loadedImage;

        update();
    }
}
void PaintCanvas::setEraserMode(bool enable)
{
    m_eraserMode = enable;
}
void PaintCanvas::paintEvent(QPaintEvent*)
{
	QPainter painter(this);

	painter.drawPixmap(0, 0, m_canvas);

    if (m_drawing && m_currentTool == DrawTool::Rectangle)
    {
        QPen pen(
            m_penColor,
            m_penWidth);

        painter.setPen(pen);

        QRect rect(
            m_startPoint,
            m_endPoint);

        painter.drawRect(
            rect.normalized());
    }
    else if (m_currentTool == DrawTool::Ellipse)
    {
        QPen pen(
            m_penColor,
            m_penWidth);

        painter.setPen(pen);

        QRect rect(
            m_startPoint,
            m_endPoint);

        painter.drawEllipse(
            rect.normalized());
    }
}

void PaintCanvas::mousePressEvent(QMouseEvent* event)
{
    if (event->button() != Qt::LeftButton)
        return;

    m_drawing = true;

    m_startPoint = event->pos();

    m_lastPoint = event->pos();
}
void PaintCanvas::mouseMoveEvent(QMouseEvent* event)
{
    if (!m_drawing)
        return;

    if (m_currentTool == DrawTool::Pen || m_currentTool == DrawTool::Eraser)
    {
        QPainter painter(&m_canvas);

        painter.setRenderHint(
            QPainter::Antialiasing);

        QPen pen(
            m_eraserMode ? Qt::white : m_penColor,
            m_eraserMode ? 20 : m_penWidth,
            Qt::SolidLine,
            Qt::RoundCap,
            Qt::RoundJoin);

        painter.setPen(pen);

        painter.drawLine(
            m_lastPoint,
            event->pos());

        m_lastPoint = event->pos();
    }
    else if (m_currentTool == DrawTool::Rectangle || m_currentTool == DrawTool::Ellipse)
    {
        m_endPoint = event->pos();
    }
   

    update();
}

void PaintCanvas::mouseReleaseEvent(QMouseEvent* event)
{
    if (!m_drawing)
        return;

    if (m_currentTool == DrawTool::Rectangle)
    {
        QPainter painter(&m_canvas);

        QPen pen(
            m_penColor,
            m_penWidth);

        painter.setPen(pen);

        QRect rect(
            m_startPoint,
            event->pos());

        painter.drawRect(
            rect.normalized());
    }
    if (m_currentTool == DrawTool::Ellipse)
    {
        QPainter painter(&m_canvas);

        QPen pen(
            m_penColor,
            m_penWidth);

        painter.setPen(pen);

        QRect rect(
            m_startPoint,
            event->pos());

        painter.drawEllipse(
            rect.normalized());
    }
    m_drawing = false;
}
void PaintCanvas::resizeEvent(QResizeEvent* event)
{
    if (width() > m_canvas.width() ||
        height() > m_canvas.height())
    {
        QPixmap newCanvas(size());

        newCanvas.fill(Qt::white);

        QPainter painter(&newCanvas);

        painter.drawPixmap(0, 0, m_canvas);

        m_canvas = newCanvas;
    }

    QWidget::resizeEvent(event);
}
void PaintCanvas::setTool(DrawTool tool)
{
    m_currentTool = tool;
}