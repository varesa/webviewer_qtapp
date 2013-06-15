#include <QtCore/QFile>

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLayout>

#include <QWebView>
#include <QtWebKitWidgets/QWebFrame>

#include <QDebug>


int main(int argc, char *argv[])
{
    
    // Initialize app

    QApplication app(argc, argv);
    app.setOverrideCursor(Qt::BlankCursor);

    // Read values
    
    QString url;
    QString geom;
    
      // Parse cmd-line arguments
      
    QStringList args = QCoreApplication::arguments();
    
    int pos;
    
    pos = args.lastIndexOf("-url");
    if(pos != -1) {
	qDebug("DEBUG: -url found");
	if(args.count() > pos+1) {
	    qDebug("DEBUG: There are arguments after it");
	    if(!args.at(pos+1).startsWith("-")) {
		qDebug("DEBUG: Next is not another argument");
		url = args.at(pos+1);
	    }
	}
    }
    
    pos = args.lastIndexOf("-geom");
    if(pos != -1) {
	qDebug("DEBUG: -geom found");
	if(args.count() > pos+1) {
	    qDebug("DEBUG: There are arguments after it");
	    if(!args.at(pos+1).startsWith("-")) {
		qDebug("DEBUG: Next is not another argument");
		geom = args.at(pos+1);
	    }
	}
    }
    
    if(url != nullptr) {
	qDebug("DEBUG: url from cmd-line: " + url.toLatin1());
    } else {
	qWarning("No url specified on cmd-line, looking for a file called url.txt");
	QFile *file = new QFile("url.txt");
	if(!file->open(QIODevice::ReadOnly)) {
	    qWarning("File not found / could not open: " + file->errorString().toLatin1());
	} else {
	    QTextStream *in = new QTextStream(file);
	    
	    if(!in->atEnd()) {
		url = in->readLine();
	    }
	    
	    qDebug("DEBUG: URL loaded form a file: " + url.toLatin1());
    	}
    	
    	file->close();
	
    }
    
    if(url == nullptr) {
	url = "http://www.google.com";
	qWarning("No URL provided on cmd-line / a file, loaded hardcoded value: " + url.toLatin1());
    }
    
    if(!url.contains(":")) {
	qWarning("WARNING: You should specify the protocol (for example http://) in the url");
    }
    
    if(geom != nullptr) {
	qDebug("DEBUG: goem from cmd-line: " + url.toLatin1());
    }
    
    //qDebug("%d", args.lastIndexOf("-url"));
    //qDebug("%d",args.count());

    // Initialize window

    QWidget *window = new QWidget();
    window->setCursor(Qt::BlankCursor);

    QBoxLayout::Direction dir = QBoxLayout::TopToBottom;

    QBoxLayout *layout = new QBoxLayout(dir);
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);

    // Initialize web browser

    QWebView *webview = new QWebView();
    //webview->setUrl(QUrl("http://www.google.com"));
    webview->setUrl(QUrl(url));
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
