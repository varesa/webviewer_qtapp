import QtQuick 2.0
import QtWebKit 3.0

/*Rectangle {
    width: 360
    height: 360
    Text {
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }
}*/
Rectangle {
    width: 800
    height: 600

    WebView {
        anchors.fill: parent
        //url: "/home/esa/projects/programming/qt/webviewer/webtest-testsite/page1.html"
        url: "http://youtube.com"
    }
}
