#pragma once
#include <QApplication>
#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include"DragDropWidget.h"
#include"GrayFormMitWidget.h"
#include"FTransfromWidget.h"
#include"ImageFPathWidget.h"
#include"FilePathWidget.h"
#include"FalseModeWidget.h"
#include"ExitWidget.h"
#include"SobelEdgeWidget.h"
#include"RgbMitWidget.h"

#define MSWidgetW 250
#define MSWidgetH 50

//This widget both acts as the 0th mode with no other widget and controlls the mode
// creation/destruction during the other modes while it is in a hidden state
class Mode_Selector : public QWidget { 
	Q_OBJECT

public:
	Mode_Selector(QWidget* parent = nullptr);

public slots:
	void openModeWindow(int index);

private:
	template<typename Container>
	void safeDeleteAllWidgets(Container& container);

	void Mode1_DragDrop(QWidget* parentWidget, QVBoxLayout* layout);
	void Mode2_PathKey(QWidget* mainParentWidget, QVBoxLayout* layout);
	void Mode3_SobelEdge(QWidget* mainParentWidget, QVBoxLayout* layout);

	QWidget* parent;
};