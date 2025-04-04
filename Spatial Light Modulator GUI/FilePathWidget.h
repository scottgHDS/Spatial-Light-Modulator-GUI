#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include<qevent.h>
#include <qmessagebox.h>
#include <Qfile>

//This widget can take a typed or previously typed filepath and emit it to other functions
//It can be activated by pressing the Enter button or pressing shift once a previous path
//has been given to it
class FilePathWidget : public QWidget
{
    Q_OBJECT

public:
    FilePathWidget(QWidget* parent = nullptr);

signals:
    void FilePath( QString& filePath);

private:
    void keyPressEvent(QKeyEvent* event) override;
    void emitSignal();
    QString lastFilepath;
    QLineEdit* path_edit;
    QPushButton* button;
};
