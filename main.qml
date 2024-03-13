import QtQuick
import myModul.Parser

My_Window {
    id: mainWin
    visible: true
    title: qsTr("Web Parser")

    topBlock.children: Top_Block{}

    leftBlock.children: Left_Block{}

    edit.text: Parser.dataset.displayData

    bottomBlock.children: Bottom_Block{ setDisplay: Parser.dataset.displayData }

    Win_Image { id: winImage; x: mainWin.x +20; y: mainWin.y +20 }

    Win_Text { id: winText; x: mainWin.x +20; y: mainWin.y +20 }

    Properties_Dialog { id: propertyDialog; forWin: ""; forFunc: ""; }

    Win_Block { id: winBlock }

    My_Message_Box { id: message }
}
