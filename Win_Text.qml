import QtQuick
import myModul.Parser

My_Window {
    id:root
    modality: "WindowModal"
    title: qsTr("Text")
    onVisibleChanged: {
        if (root.visible) {
             Parser.dataset.setDisplayText(Parser.dataset.displayData)
        }
    }

    leftBlock.children: Item {
        anchors.fill: parent
        Column {
            anchors.fill: parent
            anchors.topMargin: 10
            spacing: 8

            My_Button {
                id: btnData
                //enabled: false
                width: 140
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Page data"
                onClicked: {
                    Parser.dataset.setDisplayText(Parser.dataset.displayData)
                }
            }

            My_Button {
                id: btnSearchText
                width: 140
                anchors.horizontalCenter: parent.horizontalCenter
                text: "By tags"
                onClicked: {
                    propertyDialog.myText = "Enter a tag for example: span or h1 or p or a etc.\n"
                    propertyDialog.forWin = "txt"
                    propertyDialog.forFunc = "tags"
                    propertyDialog.visible = true
                }
            }

            My_Button {
                id: btnFilter
                width: 140
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Begining"
                onClicked: {
                    propertyDialog.myText = "The search is carried out by matching the beginning of the string.\n"
                    propertyDialog.forWin = "txt"
                    propertyDialog.forFunc = "bgn"
                    propertyDialog.visible = true
                }
            }

            My_Button {
                id: btnRegExp
                width: 140
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Expression"
                onClicked: {
                    propertyDialog.myText = "Enter the regular expression without parentheses and quotes\n"
                    propertyDialog.forWin = "txt"
                    propertyDialog.forFunc = "reg"
                    propertyDialog.visible = true
                }
            }
        }
    }

    edit.text: Parser.dataset.displayText

    bottomBlock.children: Bottom_Block{ setDisplay: Parser.dataset.displayText }
}
