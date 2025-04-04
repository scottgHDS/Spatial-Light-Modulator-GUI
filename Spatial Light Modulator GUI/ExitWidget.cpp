#include "ExitWidget.h"

//Pressing this button safely quits the program, allowing proper cleanup
ExitWidget::ExitWidget(QWidget* parent = nullptr) : QPushButton(parent) {
	
	//Text on the button
	setText("Safe Exit");

	//connects the signal from the button being pressed,
	//to the socket of the current instance of the QApplication
	connect(this, &QPushButton::clicked, qApp, &QApplication::quit);
}
