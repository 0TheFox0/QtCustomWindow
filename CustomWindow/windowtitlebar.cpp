
#include "windowtitlebar.h"

WindowTitleBar::WindowTitleBar(QWidget *parent) 
	: QWidget(parent) , 
	m_Title(this) ,
	m_Minimize(WindowButton::BUTTON_MINIMIZE,this),
	m_Maximize(WindowButton::BUTTON_MAXIMIZE,this),
	m_Close(WindowButton::BUTTON_CLOSE,this)
{
	connect(&m_Minimize, SIGNAL(clicked  ()),
		this      , SLOT  (Minimized()));

	connect(&m_Maximize, SIGNAL(clicked  ()),
		this,       SLOT  (Maximized()));

	connect(&m_Close   , SIGNAL(clicked  ()),
		this      , SLOT  (Quit     ()));

	
	setFixedHeight(33);
	m_Cache = NULL;

	m_Title.setStyleSheet("color: white; font-family: Sans; font-weight: bold; font-size: 14px");
	UpdateWindowTitle();
}

WindowTitleBar::~WindowTitleBar()
{

}

void WindowTitleBar::resizeEvent(QResizeEvent *event)
{
	Q_UNUSED(event);

	delete m_Cache; // Remove old cache

	m_Cache = new QPixmap(size());  // Create a cache with same size as the widget

	m_Cache->fill(Qt::transparent);  // Create a the transparent background

	QPainter painter(m_Cache); // Start painting the cache

	QColor lightBlue    (177, 177, 203, 255);
	QColor gradientStart(  0,   0,   0,   0);
	QColor gradientEnd  (  0,   0,   0, 220);

	QLinearGradient linearGrad(QPointF(0, 0), QPointF(0, height()));
	linearGrad.setColorAt(0, gradientStart);
	linearGrad.setColorAt(1, gradientEnd);

	/********** Title bar's frame **********/
	QPolygon frame;

	frame << QPoint(         20,  4)
		<< QPoint(width() - 4,  4)
		<< QPoint(width() - 4, 32)
		<< QPoint(          4, 32)
		<< QPoint(          4, 20);

	painter.setPen  (QPen  (lightBlue ));
	painter.setBrush(QBrush(linearGrad));

	painter.drawPolygon(frame);
	/***************************************/

	/********** Title bar's buttons area **********/
	QPolygon buttons;

	buttons << QPoint(width() - 80,  4)
		<< QPoint(width() -  4,  4)
		<< QPoint(width() -  4, 32)
		<< QPoint(width() - 88, 32)
		<< QPoint(width() - 88, 12);

	painter.setPen  (QPen  (lightBlue));
	painter.setBrush(QBrush(lightBlue));

	painter.drawPolygon(buttons);
	/**********************************************/

	m_Title.move  (           28,  4);
	m_Title.resize(width() - 116, 29);

	m_Minimize.move(width() - 84 , 9);
	m_Maximize.move(width() - 56 , 9);
	m_Close.move(width()-28 , 9);
}

void WindowTitleBar::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);

	if(m_Cache != NULL)
	{
		QPainter painter(this);

		painter.drawPixmap(0, 0, *m_Cache);
	}
}

void WindowTitleBar::UpdateWindowTitle()
{
	m_Title.setText(window()->windowTitle());
}

void WindowTitleBar::Minimized()
{
	window()->showMinimized();
}

void WindowTitleBar::Maximized()
{
	if(window()->windowState() == Qt::WindowMaximized)
	{
		window()->showNormal();
	}
	else
	{
		window()->showMaximized();
	}
}

void WindowTitleBar::Quit()
{
	qApp->quit();
}

void WindowTitleBar::mousePressEvent(QMouseEvent *event)
{
	m_Diff = event->pos();

	setCursor(QCursor(Qt::SizeAllCursor));
}

void WindowTitleBar::mouseReleaseEvent(QMouseEvent *event)
{
	Q_UNUSED(event);

	setCursor(QCursor(Qt::ArrowCursor));
}

void WindowTitleBar::mouseMoveEvent(QMouseEvent *event)
{
	QPoint p = event->globalPos();

	window()->move(p - m_Diff);
}

