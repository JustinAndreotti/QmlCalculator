import QtQuick 2.15
import QtQuick.Layouts
import local.LogicHandler   //local class

Item
{
    id: root
    property int buttonWidth
    property int buttonHeight

    width: parent.width
    height: parent.height * 0.65

    //background color (temp)
    Rectangle
    {
        anchors.fill: parent
        color: appProperties.applicationBackground
    }

    GridLayout
    {
        rows: 5
        columns: 4
        columnSpacing: 2
        rowSpacing: 2
        anchors.fill: root
        anchors.bottomMargin: 10 //For some reason the grid hangs off the bottom
                                 //of the window by ~10 pixels

        Repeater
        {
            model: buttonModel      //accessed with modelData.item
            CalcButton
            {
                width: root.buttonWidth
                height: root.buttonHeight
                buttonText: modelData.buttonText
                buttonColor: modelData.buttonColor
                buttonTextColor: modelData.buttonTextColor
                buttonType: modelData.buttonType
            }
        }
    }

    //Model for button properties
    property var buttonModel:
    [
        {"buttonText" : "C", "buttonColor" : appProperties.buttonColor,
         "buttonTextColor" : appProperties.buttonTextColorRed,
         "buttonType" : "clear"},

        {"buttonText" : "⇤", "buttonColor" : appProperties.buttonColor,
         "buttonTextColor" : appProperties.buttonTextColorWhite,
         "buttonType" : "back"},

        {"buttonText" : "%", "buttonColor" : appProperties.buttonColor,
         "buttonTextColor" : appProperties.buttonTextColorWhite,
         "buttonType" : "operator"},

        {"buttonText" : "÷", "buttonColor" : appProperties.buttonColor,
         "buttonTextColor" : appProperties.buttonTextColorGrey,
         "buttonType" : "operator"},

        {"buttonText" : "7", "buttonColor" : appProperties.buttonColor,
         "buttonTextColor" : appProperties.buttonTextColorWhite,
         "buttonType" : "number"},

        {"buttonText" : "8", "buttonColor" : appProperties.buttonColor,
         "buttonTextColor" : appProperties.buttonTextColorWhite,
         "buttonType" : "number"},

        {"buttonText" : "9", "buttonColor" : appProperties.buttonColor,
         "buttonTextColor" : appProperties.buttonTextColorWhite,
         "buttonType" : "number"},

        {"buttonText" : "x", "buttonColor" : appProperties.buttonColor,
         "buttonTextColor" : appProperties.buttonTextColorGrey,
         "buttonType" : "operator"},

        {"buttonText" : "4", "buttonColor" : appProperties.buttonColor,
         "buttonTextColor" : appProperties.buttonTextColorWhite,
         "buttonType" : "number"},

        {"buttonText" : "5", "buttonColor" : appProperties.buttonColor,
         "buttonTextColor" : appProperties.buttonTextColorWhite,
         "buttonType" : "number"},

        {"buttonText" : "6", "buttonColor" : appProperties.buttonColor,
         "buttonTextColor" : appProperties.buttonTextColorWhite,
         "buttonType" : "number"},

        {"buttonText" : "-", "buttonColor" : appProperties.buttonColor,
         "buttonTextColor" : appProperties.buttonTextColorGrey,
         "buttonType" : "operator"},

        {"buttonText" : "1", "buttonColor" : appProperties.buttonColor,
         "buttonTextColor" : appProperties.buttonTextColorWhite,
         "buttonType" : "number"},

        {"buttonText": "2", "buttonColor" : appProperties.buttonColor,
         "buttonTextColor" : appProperties.buttonTextColorWhite,
         "buttonType" : "number"},

        {"buttonText": "3", "buttonColor" : appProperties.buttonColor,
         "buttonTextColor" : appProperties.buttonTextColorWhite,
         "buttonType" : "number"},

        {"buttonText": "+", "buttonColor" : appProperties.buttonColor,
         "buttonTextColor" : appProperties.buttonTextColorGrey,
         "buttonType" : "operator"},

        {"buttonText": "0", "buttonColor" : appProperties.buttonColor,
         "buttonTextColor" : appProperties.buttonTextColorWhite,
         "buttonType" : "number"},

        {"buttonText": ".", "buttonColor" : appProperties.buttonColor,
         "buttonTextColor" : appProperties.buttonTextColorWhite,
         "buttonType" : "decimal"},

        {"buttonText": "±", "buttonColor" : appProperties.buttonColor,
         "buttonTextColor" : appProperties.buttonTextColorWhite,
         "buttonType" : "changeSign"},

        {"buttonText": "=", "buttonColor" : appProperties.buttonColor,
         "buttonTextColor" : appProperties.buttonTextColorGrey,
         "buttonType" : "equal"},
    ]
}
