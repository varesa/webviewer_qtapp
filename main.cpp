#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLayout>
#include <QWebView>
#include <QtWebKitWidgets/QWebFrame>


int main(int argc, char *argv[])
{
    
    // Initialize app

    QApplication app(argc, argv);
    app.setOverrideCursor(Qt::BlankCursor);

    // Initialize window

    QWidget *window = new QWidget();
    window->setCursor(Qt::BlankCursor);

    QBoxLayout::Direction dir = QBoxLayout::TopToBottom;

    QBoxLayout *layout = new QBoxLayout(dir);
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);

    // Initialize web browser

    QWebView *webview = new QWebView();
    webview->setUrl(QUrl("http://www.google.com"));
    webview->page()->mainFrame()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
    webview->page()->mainFrame()->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);


    // Open window

    window->resize(800, 1000);
    window->setLayout(layout);
    layout->addWidget(webview);
    webview->show();
    window->showMaximized();

    // Exec...

    return app.exec();
}
