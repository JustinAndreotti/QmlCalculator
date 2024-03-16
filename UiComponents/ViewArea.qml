import QtQuick 2.15
import QtQuick.Controls
import local.LogicHandler

Item
{
    id: viewArea

    property string mainResult: LogicHandler.mainResult
    property string mainExpression: LogicHandler.mainExpression
    property string pastResult: LogicHandler.pastResult
    property string pastExpression: LogicHandler.pastExpression

    property color mainResultColor: appProperties.buttonTextColorWhite2
    property color expressionColor: appProperties.buttonTextColorGrey
    property color pastResultColor: appProperties.buttonTextColorWhite
    property real largeTextSizeRatio: 0.3
    property real smallTextSizeRatio: 0.13

    width: parent.width
    height: parent.height * 0.29

    Rectangle
    {
        anchors.fill: parent
        color: appProperties.applicationBackground
    }

    //label holds the current expression or most recent result
    Label
    {
        id: currentInput
        anchors
        {
            right: parent.right
            bottom: parent.bottom
            bottomMargin: 5
            rightMargin: 20
        }
        font.bold: true
        font.pixelSize: if (parent.width <= parent.height){parent.width * largeTextSizeRatio}
                        else {parent.height * largeTextSizeRatio}
        minimumPixelSize: 1
        text: viewArea.mainResult
        color: viewArea.mainResultColor
        clip: false
    }

    //holds the expression that was current before the equal sign was pressed
    Label
    {
        id: recentExpression
        anchors
        {
            right: parent.right
            bottom: currentInput.top
            bottomMargin: -7
            rightMargin: 20
        }
        font.bold: true
        font.pixelSize: if (parent.width <= parent.height){parent.width * smallTextSizeRatio}
                        else {parent.height * smallTextSizeRatio}
        minimumPixelSize: 1
        text: viewArea.mainExpression
        color: viewArea.expressionColor
        clip: true
    }

    //holds the last result
    Label
    {
        id: pastResult
        anchors
        {
            right: parent.right
            bottom: recentExpression.top
            bottomMargin: 10
            rightMargin: 20
        }
        font.bold: true
        font.pixelSize: if (parent.width <= parent.height){parent.width * smallTextSizeRatio}
                        else {parent.height * smallTextSizeRatio}
        minimumPixelSize: 1
        text: viewArea.pastResult
        color: viewArea.pastResultColor
        clip: true
    }

    //holds the last result
    Label
    {

        id: pastExpression
        anchors
        {
            right: parent.right
            bottom: pastResult.top
            bottomMargin: 0
            rightMargin: 20
        }
        font.bold: true
        font.pixelSize: if (parent.width <= parent.height){parent.width * smallTextSizeRatio}
                        else {parent.height * smallTextSizeRatio}
        minimumPixelSize: 1
        text: viewArea.pastExpression
        color: viewArea.expressionColor
        clip: true
    }
}
