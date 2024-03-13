import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import myModul.Parser

My_Window {
    id:root
    modality: "WindowModal"
    title: qsTr("Images")

    edit.text: Parser.dataset.displayImage

    topBlock.children: Item {
        anchors.fill: parent
    }

    leftBlock.children: Item {
        anchors.fill: parent
        Column {
            anchors.fill: parent
            anchors.topMargin: 10
            spacing: 8

            My_Button {
                id: btnBegining
                width: 140
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Begining"
                onClicked: {
                    propertyDialog.myText = "The search is carried out by matching the beginning of the string.\n"
                    propertyDialog.forWin = "img"
                    propertyDialog.forFunc = "bgn"
                    propertyDialog.visible = true
                }
            }

            My_Button {
                id: btnSorting
                width: 140
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Sorting"
                onClicked: {

                }
            }
        }
    }

    forEdit_2.visible: true
    edit_2.text: Parser.errorInfo

    bottomBlock.children: Item {
        anchors.fill: parent
        Row {
            anchors {
                top: parent.top
                bottom: parent.bottom
                horizontalCenter: parent.horizontalCenter
            }
            spacing: 10

            Text {
                anchors.verticalCenter: parent.verticalCenter
                text: Parser.pforVisualElem.progressBarPercent
                font.pointSize: 14
                color: "white"
            }

            ProgressBar {
                id: progBar
                width: 200
                height: 15
                anchors.verticalCenter: parent.verticalCenter
                from: 0
                to: 100
                value: Parser.pforVisualElem.progressBarVal
            }

            My_Button {
                id: btnDwlAll
                width: 120
                height: 30
                anchors.verticalCenter: parent.verticalCenter
                text: "Download All"
                onClicked: {
                    folderDialog.open()
                }
            }
        }
    }

    FolderDialog {
        id: folderDialog
        currentFolder: selectedFolder
        onAccepted: {
            Parser.functionsOfButtons("imgDwl", selectedFolder.toString().replace("file:///", ""))
        }
    }
}
