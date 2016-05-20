#include <QtCore/QFile>

#include <QApplication>
#include <QWidget>
#include <QLayout>

#include <QWebView>
#include <QWebFrame>

#include <QDebug>
#include <QString>
#include <QTimer>
#include <QRect>

#include "webviewer.h"

QString WebViewer::getArgsAfter(QString specifier) {
    QStringList args = QCoreApplication::arguments();

    int pos = args.lastIndexOf(specifier);

    if(pos != -1) {
        qDebug("DEBUG: " + specifier.toLatin1() + " found");
        if(args.count() > pos+1) {
            qDebug("DEBUG: There are arguments after it");
            if(!args.at(pos+1).startsWith("-")) {
                qDebug("DEBUG: Next is not another argument");
                return args.at(pos+1);
            }
        }
    }
    return nullptr;
}

QString WebViewer::readFromFile(QString filename) {
    QFile *file = new QFile(filename);
    QString data;
    if(!file->open(QIODevice::ReadOnly)) {
        qWarning("File not found / could not open: " + file->errorString().toLatin1());
        file->close();
        return nullptr;
    } else {
        QTextStream *in = new QTextStream(file);

        if(!in->atEnd()) {
            data = in->readLine();
        } else {
            return nullptr;
        }
        file->close();
        return data;
    }
}

QString WebViewer::getUrl() {

    QString url = getArgsAfter("-url");

    if(url != nullptr) {
        qDebug("DEBUG: url from cmd-line: " + url.toLatin1());
    } else {
        qWarning("No url specified on cmd-line, looking for a file called url.txt");
        url = readFromFile("url.txt");
    }

    if(url == nullptr) {
        url = "http://www.google.com";
        qWarning("No URL provided on cmd-line / a file, loaded hardcoded value: " + url.toLatin1());
    }

    if(!url.contains(":")) {
        qWarning("WARNING: You should specify the protocol (for example http://) in the url");
    }

    return url;
}

int* WebViewer::parseGeom(QString geomstring) {
    QStringList parts = geomstring.split("x");
    //int geom[2];
    int *geom = (int*)malloc(sizeof(int) * 2);
    if(parts.count() < 2) {
        qWarning("ERROR: Invalid geometry specified, falling back to 800x600");
        geom[WIDTH] = 800;
        geom[HEIGHT] = 600;
    } else {
        geom[WIDTH]  = parts.at(0).toInt();
        geom[HEIGHT] = parts.at(1).toInt();
    }

    return geom;
}

int* WebViewer::getGeom() {
    QString geom = getArgsAfter("-geom");

    if(geom != nullptr) {
        qDebug("DEBUG: Geometry from cmd-line: " + geom.toLatin1());
    } else {
        qWarning("No geometry specified on cmd-line, looking for a file called geom.txt");
        geom = readFromFile("geom.txt");
    }

    if(geom == nullptr) {
        QRect rect = QApplication::desktop()->screenGeometry();
        int *geom = (int*)malloc(sizeof(int) * 2);
        geom[WIDTH] = rect.width();
        geom[HEIGHT] = rect.height();
        
        return geom;
        //geom = "800x600";
        //qWarning("No geometry provided on cmd-line / a file, loaded hardcoded value: " + geom.toLatin1());
    } else {
        return parseGeom(geom);
    }
    
     


    
}

QWebView* WebViewer::showWebView(int* geom, QString url)
{
    setOverrideCursor(Qt::BlankCursor);

    QWidget *window = new QWidget();
    window->setCursor(Qt::BlankCursor);

    QBoxLayout::Direction dir = QBoxLayout::TopToBottom;

    QBoxLayout *layout = new QBoxLayout(dir);
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);

    // Initialize web browser

    QWebView *webview = new QWebView();
    webview->setUrl(QUrl(url));
    webview->page()->mainFrame()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
    webview->page()->mainFrame()->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);

    // Open window

    window->resize(geom[WIDTH], geom[HEIGHT]);
    window->setLayout(layout);
    layout->addWidget(webview);
    webview->show();
    window->showMaximized();

    return webview;
}

void WebViewer::setupTimeout(QWebView* webview, QTimer* timer) {
    connect(webview, SIGNAL(loadStarted()), SLOT(webViewLoadStarted()) );
    connect(timer, SIGNAL(timeout()), SLOT(timerTimedOut()) );
    timer->start(30000);
}

void WebViewer::webViewLoadStarted() {
    qDebug("Page load, resetting timer");
    QWebSettings::globalSettings()->clearMemoryCaches(); // try to cap memory usage
    timer->start(30000); // Reset timer
}

void WebViewer::timerTimedOut() {
    qDebug("Timer timed out, reloading");
    webview->reload();
}

WebViewer::WebViewer(int argc, char *argv[]) : QApplication(argc, argv)
{
    // Read values
    QString url = getUrl();
    int* geom;
    geom = getGeom();

    // Initialize window
    webview = showWebView(geom, url);
    timer = new QTimer(this);

    setupTimeout(webview, timer);

    // Exec...
    exec();
}
