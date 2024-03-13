import QtQuick
import QtQuick.Controls

Item {
    id: root
    anchors.fill: parent
    property alias textEdit: edit

    Flickable {
        id: flick
        contentWidth: edit.contentWidth
        contentHeight: edit.contentHeight
        anchors.fill: parent
        clip: true

        ScrollBar.vertical: ScrollBar {
            id: scrollBar
            anchors {
                top: parent.top
                right: parent.right
                bottom: parent.bottom
            }
        }

        function ensureVisible(r)
        {
            if (contentX >= r.x)
                contentX = r.x;
            else if (contentX+width <= r.x+r.width)
                contentX = r.x+r.width-width;
            if (contentY >= r.y)
                contentY = r.y;
            else if (contentY+height <= r.y+r.height)
                contentY = r.y+r.height-height;
        }

        TextEdit {
            id: edit
            width: flick.width - 10
            padding: 10
            font.pointSize: 13
            wrapMode: TextEdit.Wrap
            selectByMouse: true
            selectionColor: "gray"
            onCursorRectangleChanged: flick.ensureVisible(cursorRectangle)
        }
    }
}
