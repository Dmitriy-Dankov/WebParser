import QtQuick
import myModul.Parser

Item {
    anchors.fill: parent
    property var setDisplay
    Row {
        anchors {
            top: parent.top
            bottom: parent.bottom
            horizontalCenter: parent.horizontalCenter
        }
        spacing: 10

        Column {
            anchors.verticalCenter: parent.verticalCenter
            spacing: 2
            Rectangle {
                opacity: mA_1.containsMouse ? 0.75 : 1
                width: 23
                height: 14
                color: "#313131"
                Text{
                    anchors.centerIn: parent
                    font.pointSize: 13
                    color: "white"
                    text: "▲"
                }
                MouseArea {
                    id: mA_1
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        btnSearch.ind = Parser.pforVisualElem.srchPrevious(btnSearch.ind)
                        edit.moveCursorSelection(Parser.pforVisualElem.searchWord[btnSearch.ind])
                        edit.selectWord()
                    }
                }
            }

            Rectangle {
                opacity: mA_2.containsMouse ? 0.75 : 1
                width: 23
                height: 14
                color: "#313131"
                Text{
                    anchors.centerIn: parent
                    font.pointSize: 13
                    color: "white"
                    text: "▲"
                    rotation: 180
                }
                MouseArea {
                    id: mA_2
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        btnSearch.ind = Parser.pforVisualElem.srchNext(btnSearch.ind)
                        edit.moveCursorSelection(Parser.pforVisualElem.searchWord[btnSearch.ind])
                        edit.selectWord()
                    }
                }
            }
        }

        My_Input {
            id: inpSearch
            anchors.verticalCenter: parent.verticalCenter
            width: 200
            height: 28
            onAccepted: {
                btnSearch.clicked()
            }
        }

        My_Button {
            id: btnSearch
            width: 80
            height: 28
            anchors.verticalCenter: parent.verticalCenter
            text: "Search"

            property int ind

            onClicked: {                
                if(inpSearch.myInput.text === "") return
                if( Parser.pforVisualElem.srchWord(setDisplay, inpSearch.myInput.text)) {
                edit.moveCursorSelection(Parser.pforVisualElem.searchWord[ind])
                edit.selectWord()
                }
            }
        }
    }
}
