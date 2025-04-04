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
class FalseModeWidget : public QWidget {
	Q_OBJECT

public:
	FalseModeWidget(QWidget* parent);//nulpointer over parent?

public slots:
	void ModeSelection(int index);

signals:
	void ModeNumber(int index);

};