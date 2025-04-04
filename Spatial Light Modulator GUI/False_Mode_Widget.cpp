#include "False_Mode_Widget.h"


False_Mode_Widget::False_Mode_Widget(QWidget* parent) :QWidget(parent) {
    //makes sure that the entire mode widget can be seen by the user
    setMinimumSize(250, 50);

    //creates empty layout for Mode selector
    QHBoxLayout* layout_m = new QHBoxLayout(this);

    //creates text label and adds it to the Mode Selector
    QLabel* label = new QLabel("Select a mode:", this);
    layout_m->addWidget(label);

    //creates and adds comboBox to Mode Selector
    QComboBox* comboBox = new QComboBox(this);
    comboBox->addItem("--------");
    comboBox->addItem("Drag and Drop Gray");
    comboBox->addItem("File Path Key Press Shift");
    comboBox->addItem("Edge Detection Hologram");
    layout_m->addWidget(comboBox);

    //connects the signal from the combo box (which will be the index of the mode chosen) to the current object(this)'s function
    QObject::connect(comboBox, QOverload<int>::of(&QComboBox::activated), this, &False_Mode_Widget::ModeSelection);

}

//emits the signal of what index was chosen on the widget
void False_Mode_Widget::ModeSelection(int index) {
    emit ModeNumber(index);
}
