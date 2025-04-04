#pragma once
#include <QApplication>
#include<qcoreapplication.h>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QFileDialog>
#include <QLabel>
#include <QMimeData>
#include <QMouseEvent>
#include <QPainter>
#include <QVBoxLayout>
#include <QWidget>
#include<qdir.h>
#include<QDebug>
#include<qmessagebox.h>
#include"ShowImgWidget.h"

//Widget Size
#define DDwidgetH 200
#define DDwidgetW 190


//This Widget creates a square which images
//  from your computer can be dragged to
class DragDropWidget : public QWidget {
	Q_OBJECT

public:
	DragDropWidget(QWidget* parent = nullptr);

signals:
	void ImageDroppedName(QString imageName);

private:
	void dropEvent(QDropEvent* event) override;
	void dragEnterEvent(QDragEnterEvent* event) override;
	int checkImageType(const QMimeData* mimeData);
	QLabel* dragBoxLabel;
};
