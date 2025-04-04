/*
#include "Mode_select.h"


//this is where changing the mode will call functions from other classes to run the different modes
void Mode_Selector_Widget::openModeWindow(int index) {
    qDebug() << "Selected option " << index;

    static int previous_selection = 0;
    static QWidget* parentWidget = new QWidget;



    if (index == previous_selection)
    {
        parentWidget->show();
        return;
    }

    previous_selection = index;
    qDeleteAll(parentWidget->children());
    parentWidget->close();

    //Layout for all modes
    QVBoxLayout* layout = new QVBoxLayout(parentWidget);


    if (index == 1) Mode1_DragDrop(parentWidget, layout);

    else if (index == 2)
    {



        QHBoxLayout* hLayout = new QHBoxLayout();
        QVBoxLayout* vLayout = new QVBoxLayout();

        FilePathWidget* filePathWidget = new FilePathWidget(parentWidget);
        FTransformWidget* ftransformWidget = new FTransformWidget(parentWidget);
        grayFormMitWidget* showImgWidget = new grayFormMitWidget(parentWidget);
        ImageFPathWidget* imageFPathWidget = new ImageFPathWidget(parentWidget);


        QObject::connect(showImgWidget, &grayFormMitWidget::imageFinished, ftransformWidget, &FTransformWidget::ImageDropped);
        //QObject::connect(imageDropWidget1, &ImageDropWidget::ImageDropped, showImgWidget1, &grayFormMitWidget::ImageDropped2);

        hLayout->addWidget(imageFPathWidget);
        hLayout->addWidget(showImgWidget);

        vLayout->addWidget(filePathWidget);
        vLayout->addLayout(hLayout);
        vLayout->addWidget(ftransformWidget);


        layout->addLayout(vLayout);
        parentWidget->show();

    }

}

Mode_Selector_Widget::Mode_Selector_Widget(QWidget* parent) :QWidget(parent)
{
    setMinimumSize(250, 50);
    //QWidget* window = new QWidget;
    QHBoxLayout* layout = new QHBoxLayout(this);
    QLabel* label = new QLabel("Select a mode:", this);
    layout->addWidget(label);

    parentWidget = new QWidget(this);
    QHBoxLayout* parentLayout = new QHBoxLayout(parentWidget);
    parentWidget->setLayout(parentLayout);
    parentWidget->hide();

    QComboBox* comboBox = new QComboBox(this);
    comboBox->addItem("--------");
    comboBox->addItem("Drag and Drop Gray");
    comboBox->addItem("File Path Key Press \".\"");
    comboBox->addItem("Option 3");
    layout->addWidget(comboBox);

    //connects the signal from the combo box (which will be the index of the mode chosen) to the current object(this)'s function
    QObject::connect(comboBox, QOverload<int>::of(&QComboBox::activated), this, &Mode_Selector_Widget::openModeWindow);
    //the &function 
}


void Mode_Selector_Widget::Mode1_DragDrop(QWidget* parentWidget, QVBoxLayout* layout) {
    QHBoxLayout* hLayout = new QHBoxLayout();
    QVBoxLayout* vLayout = new QVBoxLayout();

    DragDropWidget* dragDropWidget = new DragDropWidget(parentWidget);
    grayFormMitWidget* grayWidget = new grayFormMitWidget(parentWidget);
    FTransformWidget* ftransformWidget = new FTransformWidget(parentWidget);

    //coult these be simultaneous? they are both being sent the same url string
    QObject::connect(dragDropWidget, &DragDropWidget::ImageDroppedName, grayWidget, &grayFormMitWidget::recieveDroppedImg);
    QObject::connect(grayWidget, &grayFormMitWidget::imageFinished, ftransformWidget, &FTransformWidget::ImageDropped);



    hLayout->addWidget(dragDropWidget);
    hLayout->addWidget(grayWidget);

    vLayout->addLayout(hLayout);
    vLayout->addWidget(ftransformWidget);

    layout->addLayout(vLayout);
    parentWidget->show();
}
*/

/*int main(int argc, char* argv[]) { //passes in argument count and argument vector

    QApplication a(argc, argv); // creates QApplication

    SLM_Setup current_instance;
    
	//This widget is the combined version of mode select and exit button
    QWidget* Menu = new QWidget;
    QHBoxLayout* layout = new QHBoxLayout(Menu);


    Mode_Selector_Widget* M_Select = new Mode_Selector_Widget(Menu);
    ExitWidget* ExitW = new ExitWidget(Menu);


    layout->addWidget(M_Select);
    layout->addWidget(ExitW);

    Menu->show();*/