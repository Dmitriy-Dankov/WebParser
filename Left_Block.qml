import QtQuick
import QtQuick.Dialogs
import myModul.Parser

Item {
    id: root
    anchors.fill: parent
    anchors.topMargin: 8

    Column {
        anchors.fill: parent
        spacing: parent.anchors.topMargin

        My_Button {
            id: btnData
            //enabled: false
            width: 140
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Page data"
            onClicked: {
                Parser.dataset.dataOutput()
            }
        }

        My_Button {
            id: btnBlock
            width: 140
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Block"
            onClicked: {
                winBlock.visible = true
            }
        }

        My_Button {
            id: btnHref
            width: 140
            anchors.horizontalCenter: parent.horizontalCenter
            text: "All href..."
            onClicked: {
                Parser.functionsOfButtons(text)
            }
        }

        My_Button {
            id: btnSrc
            width: 140
            anchors.horizontalCenter: parent.horizontalCenter
            text: "All src..."
            onClicked: {
                Parser.functionsOfButtons(text)
            }
        }

        My_Button {
            id: btnText
            width: 140
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Text"
            onClicked: {
                winText.visible = true
            }
        }

        My_Button {
            id: btnImages
            width: 140
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Images"
            onClicked: {
                Parser.functionsOfButtons("SrchImgs")
                winImage.visible = true
            }
        }
    }

}
