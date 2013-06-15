#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLayout>
#include <QWebView>
#include <QtWebKitWidgets/QWebFrame>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setOverrideCursor(Qt::BlankCursor);

    QWidget *window = new QWidget();
    window->setCursor(Qt::BlankCursor);

    QBoxLayout::Direction dir = QBoxLayout::TopToBottom;

    QBoxLayout *layout = new QBoxLayout(dir);
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);

    QWebView *webview = new QWebView();
    webview->setUrl(QUrl("http://www.google.com"));
    webview->page()->mainFrame()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
    webview->page()->mainFrame()->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);

    //window->setWindowFlags(Qt::FramelessWindowHint);
    window->resize(800, 1000);
    window->setLayout(layout);
    layout->addWidget(webview);
    webview->show();
    window->showMaximized();

    return app.exec();
}
