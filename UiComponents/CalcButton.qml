import QtQuick 2.15
import QtQuick.Controls
import QmlCalculator
import local.LogicHandler

Item
{
    id: calcButton

    property color buttonColor
    property color buttonTextColor
    property string buttonText
    property string buttonType
    property real buttonSizeRatio: 0.5
    property real buttonHoveredOpacity: 0.7
    property real buttonNormalOpacity: 1
    property bool mouseOverButton: false

    signal buttonClicked

    implicitWidth: parent.width * 0.25
    implicitHeight: parent.height * 0.20

    //Button appearance
    Rectangle
    {
        id: buttonBackground
        anchors.fill: parent
        color: calcButton.buttonColor
        opacity: mouseArea.containsMouse ? calcButton.buttonNormalOpacity
                                         : calcButton.buttonHoveredOpacity
    }

    //button text
    Label
    {
        anchors.fill: parent
        anchors.centerIn: parent
        text: calcButton.buttonText
        color: calcButton.buttonTextColor
        font.pixelSize: if (parent.width <= parent.height){parent.width * buttonSizeRatio}
                        else {parent.height * buttonSizeRatio}
        minimumPixelSize: 1
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.bold: true

    }

    //interaction area
    MouseArea
    {
        id:mouseArea
        hoverEnabled: true
        anchors.fill: parent

        onClicked:
        {
            LogicHandler.processButtonInput(calcButton.buttonText, calcButton.buttonType)
        }
    }
}
