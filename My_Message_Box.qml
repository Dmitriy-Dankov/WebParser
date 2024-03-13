import QtQuick
import myModul.Parser

Window {
    id: root
    modality: "WindowModal"
    flags: "Dialog"
    title: "Message:"
    minimumWidth: 240
    minimumHeight: 180
    visible: false;
    color: "lightgray"

    Column {
        anchors {
            verticalCenter: parent.verticalCenter
            horizontalCenter: parent.horizontalCenter
            topMargin: 10
            bottomMargin: 10
        }
        spacing: 20
        Rectangle {
            clip: true
            width: root.width - 30
            height: txt.height + 15
            anchors.horizontalCenter: parent.horizontalCenter
            radius: 5
            color: "#a8a7a7"
            Text {
                id: txt
                width: parent.width - 20
                horizontalAlignment: Text.AlignHCenter
                anchors.verticalCenter: parent.verticalCenter
                text: Parser.pInfoMessage.message
                font.pointSize: 14
                wrapMode: Text.WordWrap
                color: "#880005"
                onTextChanged: root.visible = true
            }
        }
        My_Button {
            anchors.horizontalCenter: parent.horizontalCenter
            width: 60
            text: "Ok"
            onClicked: {
                root.visible = false
            }
        }
    }
}
