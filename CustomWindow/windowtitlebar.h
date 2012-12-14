
#ifndef WINDOWTITLEBAR_H
#define WINDOWTITLEBAR_H

#include <QtGui>
#include "windowbutton.h"

class WindowTitleBar : public QWidget
{
	Q_OBJECT

public:
	WindowTitleBar(QWidget *parent = 0);
	~WindowTitleBar();
public slots:
	void UpdateWindowTitle();
	void Minimized();
	void Maximized();
	void Quit     ();
protected:
	void resizeEvent(QResizeEvent *event);
	void paintEvent (QPaintEvent  *event);
	void mousePressEvent  (QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent   (QMouseEvent *event);
private:
	QPixmap *m_Cache;
	QLabel m_Title;
	WindowButton m_Minimize;
	WindowButton m_Maximize;
	WindowButton m_Close;
	QPoint m_Diff;
};

#endif

