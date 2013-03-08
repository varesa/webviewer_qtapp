#include <QtGui/QApplication>
#include <QtGui/QWidget>
#include <QtGui/QLayout>
#include <QWebView>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget *window = new QWidget();

    QBoxLayout::Direction dir = QBoxLayout::TopToBottom;

    QBoxLayout *layout = new QBoxLayout(dir);

    QWebView *webview = new QWebView();
    webview->setUrl(QUrl("http://192.168.0.5/"));

    window->resize(500, 500);
    window->setLayout(layout);
    layout->addWidget(webview);
    webview->show();
    window->show();

    return app.exec();
}
