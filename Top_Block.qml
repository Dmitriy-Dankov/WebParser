import QtQuick
import QtQuick.Controls
import myModul.Parser

Item {
    id:root
    anchors.fill: parent
    ComboBox {
        id: comboBox
        width: 140
        height: 30
        x: 10
        y: 20
        model: ["  UTF-8", "  CP-1251"]
        font.pointSize: 12
        onActivated: {
            currentIndex === 0 ? Parser.setCp_1251(0) : Parser.setCp_1251(1)
        }
    }

    My_Input {
        id: myInputUrl
        width: parent.width / 1.5
        height: 30
        anchors {
            verticalCenter: parent.verticalCenter
            right: parent.right
            rightMargin: 20
        }
        textLabel: "URL:  "
        onAccepted: {
            Parser.request(myInput.text)
            forceActiveFocus(root)
        }
    }
}
