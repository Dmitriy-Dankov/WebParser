import QtQuick
import myModul.Filters

Window {
    id: root
    modality: "WindowModal"
    minimumWidth: 240
    minimumHeight: 360
    title: qsTr("Clarifying dialog box")
    visible: false
    color: "#a8a7a7"

    property string myText
    required property string forWin
    required property string forFunc

    onVisibleChanged: {
        if (root.visible) {
            inputExpr.myInput.text = ""
        }
    }

    Column {
        anchors.centerIn: parent
        spacing: 10
        Rectangle {
            clip: true
            width: root.width - 30
            height: txt.height + 15
            anchors.horizontalCenter: parent.horizontalCenter
            radius: 5
            color: "#a8a7a7"
            Text {
                id:txt
                width: parent.width - 20
                horizontalAlignment: Text.AlignHCenter
                anchors.verticalCenter: parent.verticalCenter
                text: myText + "You can enter multiple values separated by commas."
                color: "#062d19"
                font.pointSize: 14
                wrapMode: Text.WordWrap
            }
        }

        My_Input {
            id: inputExpr
            width: root.width / 1.2
            height: 120
            myInput.wrapMode: Text.WordWrap
            onAccepted: {
                Filters.handler(forWin, forFunc, inputExpr.myInput.text)
                root.visible = false
            }
        }
    }
}
