import QtQuick 2.15

Item
{
    id: appProperties


    //16x9 screen ratio that can be multiplied out
    property real appWidth: 9 * appMagnitude
    property real appHeight: 16 * appMagnitude
    property real appMagnitude: 40


    property color buttonColor: "#131c25"
    property color buttonTextColorRed: "#f93737"
    property color buttonTextColorWhite: "#c4d0dc"
    property color buttonTextColorGrey: "#526271"
    property color applicationBackground: "#1c2632"
    property color buttonTextColorWhite2: "white"
}
