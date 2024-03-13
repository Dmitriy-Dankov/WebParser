import QtQuick
import QtQuick.Controls
Item {
    id: root
    property alias textLabel: rootLabel.text
    property alias myInput: rootInput
    signal accepted
    Label {
       id: rootLabel
       anchors {
           left: parent.left
           top: parent.top
           bottom: parent.bottom
       }
       text: ""
       color: "white"
       font.pointSize: 13
    }
    Rectangle {
        color: "white"
        anchors {
            left: rootLabel.right
            top: parent.top
            right: parent.right
            bottom: parent.bottom
        }

        TextInput {
            id: rootInput
            clip: true
            anchors.fill: parent
            color: "#5c5c5c"
            font.pointSize: 14
            leftPadding: 10
            rightPadding: 10
            selectionColor: "#959393"
            onAccepted: {
                root.accepted()
            }
        }
    }
}
