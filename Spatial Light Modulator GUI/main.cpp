#include "AERSP424_QT_Course_Project.h"
#include <QtWidgets/QApplication>
#include"DragDropWidget.h"
#include"ModeSelectorWidget.h"
#include"Setup_SLM.h"
#include"ExitWidget.h"
#include<utility>


int main(int argc, char* argv[]) { 
	
	// creates QApplication, so that we can use the GUI
	QApplication a(argc, argv); 

	//Initialize the SLM transmission window
	SLM_Setup::SDK_Creation();
	//Load appropriate LUT file to the hardware
	SLM_Setup::Lut_Choose(Get_Height(), Get_Depth());

	//Create an initial Menu that will allow user to navigate to all modes
	QWidget* Menu = new QWidget;
	QHBoxLayout* layout = new QHBoxLayout(Menu);

	//Create the Combo box for navigation and Exit button for safe exit
	ModeSelectorWidget* M_Select = new ModeSelectorWidget(Menu);
	ExitWidget* ExitW = new ExitWidget(Menu);

	//Add Mode selection and exit widgets to Menu's horitzontal layout
	layout->addWidget(M_Select);
	layout->addWidget(ExitW);

	//Show inital Menu
	Menu->show();

	//run the QTwidgets event loop
	return a.exec();
	}

