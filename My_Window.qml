import QtQuick
import QtQuick.Controls
import myModul.Parser

Window {
    id: root
    minimumWidth: 640
    minimumHeight: 480
    visible: false

    property alias topBlock: topBlock
    property alias leftBlock: leftBlock
    property alias bottomBlock: bottomBlock
    property alias edit: edit.textEdit
    property alias forEdit_2: forEdit_2
    property alias edit_2: edit_2.textEdit

    Rectangle {
        id: topBlock
        height: 64
        color: "#062d19"
        anchors {
            left: parent.left
            right: parent.right
            top:  parent.top
        }
    }

    Rectangle {
        id: leftBlock
        width: 160
        anchors {
            left: parent.left
            top: topBlock.bottom
            bottom: bottomBlock.top
        }
        color: "#a8a7a7"
    }

    Rectangle {
        id: forEdit
        anchors {
            left: leftBlock.right
            right: parent.right
            top: topBlock.bottom
            bottom: forEdit_2.visible == true ? forEdit_2.top : bottomBlock.top
        }
        Scroll_TextEdit {
            id: edit
        }
    }

    Rectangle {
        id: forEdit_2
        implicitHeight: 70
        visible: false
        anchors {
            left: leftBlock.right
            right: parent.right
            bottom: bottomBlock.top
        }

        Rectangle {
            id:rectForEdit_2
            height: 8
            color: "#a8a7a7"
            anchors {
                left: parent.left
                top: parent.top
                right: parent.right
            }
            MouseArea {
                cursorShape: Qt.SizeVerCursor
                height: 5
                anchors {
                    left: parent.left
                    right: parent.right
                    bottom: parent.bottom
                }

                acceptedButtons: Qt.LeftButton
                hoverEnabled: false
                onMouseYChanged: {
                    if (pressed && forEdit_2.height > 31) {
                        forEdit_2.height -= mouseY
                    }
                    else if (pressed && mouseY < 0) {
                        forEdit_2.height -= mouseY
                    }
                }
            }
        }

        Scroll_TextEdit {
            id: edit_2
            anchors.topMargin: 10
        }
    }

    Rectangle {
        id: bottomBlock
        height: 50
        color: "#062d19"
        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
    }

    BusyIndicator {
        anchors.centerIn: forEdit
        running: Parser.pSRequest.yes
        scale: 1.5
    }
}
