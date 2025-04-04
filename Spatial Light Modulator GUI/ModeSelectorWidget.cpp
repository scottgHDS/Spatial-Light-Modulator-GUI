#include "ModeSelectorWidget.h"

//Constructor makes a mode select combo box and connects it's value to which mode the object will generate
ModeSelectorWidget::ModeSelectorWidget(QWidget* parent) :QWidget(parent), parent(parent)
{   
    //Setting minimum size so mode slector combo box and safe exit can be full seen
    setMinimumSize(MSWidgetW, MSWidgetH);
    
    //Creates a horizontal layout to hold to the combo box and its label
    QHBoxLayout* initialLayout = new QHBoxLayout(this);

    //title label is created and added to the layout
    QLabel* title = new QLabel("Select a mode:", this);
    initialLayout->addWidget(title);

    //Create comoBox with all its different modes and adds it to the layout
    QComboBox* comboBox = new QComboBox(this);
    comboBox->addItem("--------");
    comboBox->addItem("Drag and Drop Gray");
    comboBox->addItem("File Path Key Press Shift");
    comboBox->addItem("Edge Detection Hologram");
    initialLayout->addWidget(comboBox);

    //connects the signal from the combo box (which will be the index of the mode chosen) to the current object(this)'s function
    QObject::connect(comboBox, QOverload<int>::of(&QComboBox::activated), this, &ModeSelectorWidget::openModeWindow);
}


//This function opens or closes-and-reopens the menu with the appropriate widgets depending on the users's selection
void ModeSelectorWidget::openModeWindow(int index) {

    static int onInitialMenu = true;
    static int previous_selection = 0;
    static QWidget* modeMenuWidget = new QWidget;

    //If the user opens the menu by accident, they can reselect the mode they are using to not
    //loose their current image or pattern
    if (index == previous_selection) return;

    //if the user is on the initial menu and they choose another mode, hide the initial menu
    if (onInitialMenu == true && index != 0)
    {
        this->parent->hide();
        onInitialMenu = false;
    }

    //if the user select the initial menu, show it 
    else if (index == 0)
    {
        this->parent->show();
        onInitialMenu = true;
    }

    //Get a list of all widgets within the current mode
    QWidgetList WidgetsofModeMenu  = modeMenuWidget->findChildren<QWidget*>(QString(), Qt::FindDirectChildrenOnly);

    //delete all instances of the widgets in each mode UI, and schedule 
    // for their memory to be delete at application close
    safeDeleteAllWidgets(WidgetsofModeMenu);

    //Layout for all modes
    static QVBoxLayout* layout = new QVBoxLayout(modeMenuWidget);

    switch (index) {

        //opens original menu to solely select another menu
        case 0:
            previous_selection = 0;

            //close any mode that was previously openned
            modeMenuWidget->close();

            //Show the initial menu
            this->parent->show();
            return;
        
        //opens the drag and rop pattern mode
        case 1:
            Mode1_DragDrop(modeMenuWidget, layout);
            break;

        //opens the mode which allows for image paths to be typed and Shift to trigger reread
        case 2:
            Mode2_PathKey(modeMenuWidget, layout);
            break;

        //opens the hologram drag and drop mode
        case 3:
            Mode3_SobelEdge(modeMenuWidget, layout);
            break;
    }

    //adjusts the static variable of the previous_selection to the most recent selection
    previous_selection = index;

    //closes and reopens the mode widget so that the size of the widget resets
    modeMenuWidget->close();
    modeMenuWidget->show();
}

//This is a template function because the container could be either a horizontal or vertical box layout
//  Safely delets each widget using QT widgets perferred way of deleting widgets "deleteLater"
//  this removes the widget functionally and scheduales the memory to be deleted later
template <typename Container>
void ModeSelectorWidget::safeDeleteAllWidgets(Container& container)
{   
    //iterates through all member of the QBoxlayout
    for (auto it = container.begin(); it != container.end(); ) {
        
        //create a pointer to a QBox 
        auto ptr = *it;

        //delete the current QBox layout
        it = container.erase(it);

        //if the pointer has a widget in it, delete the widget
        if (ptr != nullptr) {
            
            //create a pointer to the widget within the Boxlayout
            auto widget = qobject_cast<QWidget*>(ptr);

            //if the widget pointer is valid deletethe widget
            if (widget != nullptr) {

                //delete the widget later and set the pointer ot a null pointer
                widget->deleteLater();
                widget = nullptr;
            }
        }
    }
}

//This function creates and orgnaizes all the widgets for Mode 1, the drag and drop pattern mode
void ModeSelectorWidget::Mode1_DragDrop(QWidget* mainParentWidget, QVBoxLayout* layout) {

    //The entire mode will one vertical layout with three elements (two rows and one subwidget)
    QVBoxLayout* modeLayout = new QVBoxLayout();

    //The top row of widgets will be the menu select and exit widgets next to eachother
    QHBoxLayout* menuExitLayout = new QHBoxLayout();

    //The middle layer will be the dragDrop widget next to the transmitted image widget
    QHBoxLayout* dragTransLayout = new QHBoxLayout();

    //Create widgets for the top row of the Mode
    FalseModeWidget* falseModeWidget = new FalseModeWidget(mainParentWidget);
    ExitWidget* exitWidget = new ExitWidget(mainParentWidget);

    //Create widgets for the middle row of the Mode
    DragDropWidget* dragDropWidget = new DragDropWidget(mainParentWidget);
    GrayFormMitWidget* grayFormMitWidget = new GrayFormMitWidget(mainParentWidget);

    //The third row is a single widge widget for the Fourier transform
    FTransformWidget* ftransformWidget = new FTransformWidget(mainParentWidget);

    //Connecting the signal from the DragDropWidget which will output the file path of the dragged image
    //  to the grayscale transmission widget and fourier transform widget
    QObject::connect(dragDropWidget, &DragDropWidget::ImageDroppedName, grayFormMitWidget, &GrayFormMitWidget::recieveDroppedImg);
    QObject:connect(dragDropWidget, &DragDropWidget::ImageDroppedName, ftransformWidget, &FTransformWidget::ImageDropped);

    //connect the mode selector in the mode to transmit the mode chosen to this class object to change the mode
    QObject::connect(falseModeWidget, &FalseModeWidget::ModeNumber, this, &ModeSelectorWidget::openModeWindow);

    //top row Widgets are added to their layout
    menuExitLayout->addWidget(falseModeWidget);
    menuExitLayout->addWidget(exitWidget);

    //middle row Widgets are added to their layout
    dragTransLayout->addWidget(dragDropWidget);
    dragTransLayout->addWidget(grayFormMitWidget);

    //adding layouts and widgets from top to bottom to the mode layout
    modeLayout->addLayout(menuExitLayout);
    modeLayout->addLayout(dragTransLayout);
    modeLayout->addWidget(ftransformWidget);

    //Mode1 layout is set to the layout that holds all modes and show it
    layout->addLayout(modeLayout);
    mainParentWidget->show();
}

//This function creates and organizes all the widgets for Mode, the filepath/keypress widget mode
//
//Note: for a more detailed example on how these modes are creates in QTwidgets see Mode1
//      which is more heavy commented
void ModeSelectorWidget::Mode2_PathKey(QWidget* mainParentWidget, QVBoxLayout* layout)
{
    //The entire mode will be one vertical layout with four elements (two rows and two widgets)
    QVBoxLayout* modeLayout = new QVBoxLayout();
    //makes sure that each minimum size constraint is followed
    modeLayout->setSizeConstraint(QLayout::SetMinimumSize);

    //The top row of widgets is the menu select and exit widgets next to eachother
    QHBoxLayout* menuExitLayout = new QHBoxLayout();
    FalseModeWidget* falseModeWidget = new FalseModeWidget(mainParentWidget);
    ExitWidget* exitWidget = new ExitWidget(mainParentWidget);
    menuExitLayout->addWidget(falseModeWidget);
    menuExitLayout->addWidget(exitWidget);
    modeLayout->addLayout(menuExitLayout);

    //Second highest layer is the filePath input widget
    FilePathWidget* filePathWidget = new FilePathWidget(mainParentWidget);
    modeLayout->addWidget(filePathWidget);

    //The fourth highest layer is the the imagefromfilepath and transmitted image widgets
    QHBoxLayout* pathImageTransLayout = new QHBoxLayout();
    ImageFPathWidget* imageFPathWidget = new ImageFPathWidget(mainParentWidget);
    GrayFormMitWidget* grayFormMitWidget = new GrayFormMitWidget(mainParentWidget);
    pathImageTransLayout->addWidget(imageFPathWidget);
    pathImageTransLayout->addWidget(grayFormMitWidget);
    modeLayout->addLayout(pathImageTransLayout);

    //The last layer is the fourier transform widget
    FTransformWidget* ftransformWidget = new FTransformWidget(mainParentWidget);
    modeLayout->addWidget(ftransformWidget);
 
    //Connects the filepath read from Imagefromfilepath, to all display, gray display, and fourier transform widgets
    QObject::connect(filePathWidget, &FilePathWidget::FilePath,imageFPathWidget,&ImageFPathWidget::PathSelected);
    QObject::connect(filePathWidget, &FilePathWidget::FilePath, grayFormMitWidget, &GrayFormMitWidget::recieveDroppedImg);
    QObject::connect(filePathWidget, &FilePathWidget::FilePath, ftransformWidget, &FTransformWidget::ImageDropped);
    
    //connect the mode selector in the mode to transmit the mode chosen to this class object to change the mode
    QObject::connect(falseModeWidget, &FalseModeWidget::ModeNumber, this, &ModeSelectorWidget::openModeWindow);

    //Mode2 layout is set to the layout that holds all modes and show it
    layout->addLayout(modeLayout);
    mainParentWidget->show();
}


//This function creates and organizes all the widgets for Mode, the hologram widget mode
//
//Note: for a more detailed example on how these modes are creates in QTwidgets see Mode1
//      which is more heavy commented
void ModeSelectorWidget::Mode3_SobelEdge(QWidget* mainParentWidget , QVBoxLayout* layout)
{

    //The entire mode will be one vertical layout with four elements (two rows and two widgets)
    QVBoxLayout* modeLayout = new QVBoxLayout();
    //makes sure that each minimum size constraint is followed
    modeLayout->setSizeConstraint(QLayout::SetMinimumSize);

    //The top row of widgets will be the menu select and exit widgets next to eachother
    QHBoxLayout* menuExitLayout = new QHBoxLayout();
    FalseModeWidget* falseModeWidget = new FalseModeWidget(mainParentWidget);
    ExitWidget* exitWidget = new ExitWidget(mainParentWidget);
    menuExitLayout->addWidget(falseModeWidget);
    menuExitLayout->addWidget(exitWidget);
    modeLayout->addLayout(menuExitLayout);

    //Second highest layer is the dragDrop widget next to the transmitted image widget in RGB format
    QHBoxLayout* dragTransLayout = new QHBoxLayout();
    DragDropWidget* dragDropWidget = new DragDropWidget(mainParentWidget);
    RgbaDispWidget* rgbaDispWidget = new RgbaDispWidget(mainParentWidget);
    dragTransLayout->addWidget(dragDropWidget);
    dragTransLayout->addWidget(rgbaDispWidget);
    modeLayout->addLayout(dragTransLayout);

    //Third highest layer is the SobelEdgeDetection widget
    SobelEdgeWidget* sobelEdgeWidget = new SobelEdgeWidget(mainParentWidget);
    modeLayout->addWidget(sobelEdgeWidget);

    //The last layer is the fourier transform widget
    FTransformWidget* fTransformWidget = new FTransformWidget(mainParentWidget);
    modeLayout->addWidget(fTransformWidget);

    //connects the dropped image's new file path to the sobel edge detector widget
    QObject::connect(dragDropWidget, &DragDropWidget::ImageDroppedName, sobelEdgeWidget, &SobelEdgeWidget::loadImage);
    //connects the sobelEdgeWidget's generated hologram pattern to the RGBA display Widget
    //this uses a lambda function because of the overloaded fill_widget function
    QObject::connect(sobelEdgeWidget, &SobelEdgeWidget::holoPattern, rgbaDispWidget,[rgbaDispWidget](const QImage& image) { rgbaDispWidget->fill_widget(image); });
    //connects the sobelEdgeWidget's generated hologram pattern to the fourier transform widget
    QObject::connect(sobelEdgeWidget, & SobelEdgeWidget::holoPattern, fTransformWidget, &FTransformWidget::ImageDroppedImg);
    //connect the mode selector in the mode to transmit the mode chosen to this class object to change the mode
    QObject::connect(falseModeWidget, &FalseModeWidget::ModeNumber, this, &ModeSelectorWidget::openModeWindow);

    //Mode3 layout is set to the layout that holds all modes and show it
    layout->addLayout(modeLayout);
    mainParentWidget->show();
}


