#pragma once
#include <QApplication>
#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include"DragDropWidget.h"
#include"grayFormMitWidget.h"
#include"FTransfromWidget.h"
#include"ImageFPathWidget.h"
#include"FilePathWidget.h"

//This widget will be on each non-initial mode and simply acts to transmit the index chosen to the 
// hidden, controlling mode selection widget
class Mode_Selector_Widget : public QWidget {
	Q_OBJECT

public:
	Mode_Selector_Widget(QWidget* parent);//nulpointer over parent?

public slots:
	void ModeSelection(int index);

signals:
	void ModeNumber(int index);

};