#pragma once
#include<qpushbutton.h>
#include<qapplication.h>
#include<qwidget.h>


//This widget creates a button which safely shuts down the program
class ExitWidget : public QPushButton {
	Q_OBJECT;

public:
	ExitWidget(QWidget* parent);
};