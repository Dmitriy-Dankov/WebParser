import QtQuick

Rectangle {
    id: root

    property alias text: myBtnText.text

    signal clicked

    width: myBtnText.width
    height: myBtnText.height + 18
    color: "#313131"
    radius: 5
    opacity: myBtnAreaMouse.containsMouse ? 0.75 : 1

    Text {
        id: myBtnText
        anchors.centerIn: parent
        font.pointSize: 13
        color: "white"
        wrapMode: Text.WordWrap
    }

    MouseArea {
        id: myBtnAreaMouse
        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
            root.clicked()
        }
    }
}
