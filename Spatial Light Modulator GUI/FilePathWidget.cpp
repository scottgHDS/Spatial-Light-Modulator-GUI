#include"FilePathWidget.h"



FilePathWidget::FilePathWidget(QWidget* parent) : QWidget(parent)
{
    // Create a line edit for the file path
    path_edit = new QLineEdit();

    // Create a button to emit the signal
    button = new QPushButton("Set Filepath");
    connect(button, &QPushButton::clicked, this, &FilePathWidget::emitSignal);

    // Add the line edit and button to a layout
    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(path_edit);
    layout->addWidget(button);
    setLayout(layout);
}


//defines functionality to use a keypress to trigger the last path given
void FilePathWidget::keyPressEvent(QKeyEvent* event)
{
    // If the "Shift" key is pressed, emit the signal
    if (event->key() == Qt::Key_Shift && !lastFilepath.isEmpty()) {
        emit FilePath(lastFilepath);
    }
    else {
        //If any other key is pressed, disregard it
        QWidget::keyPressEvent(event);
    }
}


//Emits the curret or previous filepath to other widgets
void FilePathWidget::emitSignal()
{

    // Get the file path from the line edit and emit the signal
    QString filePath = path_edit->text();
    
    // Check if the file exists
    if (!QFile::exists(filePath)) {
        // Show an error message if the file path is not valid
        QMessageBox::critical(this, "Error", "Invalid file pat!");
        return;
    }
    
    //save the filepath that was given to the member variable
    lastFilepath = filePath;


    //path_edit->clear();
    emit FilePath(filePath);
}

