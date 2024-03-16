import QtQuick
import "Properties"
import "UiComponents"
import local.LogicHandler

Window
{
    id: root
    width: appProperties.appWidth
    height: appProperties.appHeight
    visible: true
    title: qsTr("Qml Calculator")

    AppProperties
    {
        id: appProperties
    }

    //Main container for the Layout
    Item
    {
        anchors.fill: parent

        ViewArea
        {
            id: viewArea
            anchors.bottom: buttonArea.top
        }

        //Area of the UI that contains all the calculator buttons
        ButtonArea
        {
            id: buttonArea
            anchors.bottom: parent.bottom
            buttonWidth: root.width * 0.25
            buttonHeight: root.width * 0.20
        }
    }
}
