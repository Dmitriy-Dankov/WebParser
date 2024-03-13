import QtQuick
import myModul.Parser

Window {
    id: root
    modality: "WindowModal"
    minimumWidth: 240
    minimumHeight: 180
    title: qsTr("Block")
    visible: false
    color: "#a8a7a7"

    Column {
        anchors.centerIn: parent
        spacing: 10
        Text {
            text: "Attribute:"
            font.pointSize: 14
            color: "#062d19"
        }

        My_Input {
            id: inputAtrbt
            width: root.width / 1.2
            myInput.focus: true
            height: 30
            onAccepted: {
                forceActiveFocus(inputName)
                inputName.rootInput.focus = true
            }
        }

        Text {
            text: "Attribute name:"
            font.pointSize: 14
            color: "#062d19"
        }

        My_Input {
            id: inputName
            width: root.width / 1.2
            height: 30
            onAccepted: {
                Parser.functionsOfButtons("Block", inputAtrbt.myInput.text, inputName.myInput.text)
                root.visible = false
            }
        }
    }
}
