#include <QtCore/QFile>

#include <QApplication>
#include <QWidget>
#include <QLayout>

#include <QWebView>
#include <QWebFrame>

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
	    
	    qDebug("URL loaded form a file: " + url.toLatin1());
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
    
    if(geom != nullptr) {
	qDebug("DEBUG: Geometry from cmd-line: " + geom.toLatin1());
    } else {
	qWarning("No geometry specified on cmd-line, looking for a file called geom.txt");
	QFile *file = new QFile("geom.txt");
	if(!file->open(QIODevice::ReadOnly)) {
	    qWarning("File not found / could not open: " + file->errorString().toLatin1());
	} else {
	    QTextStream *in = new QTextStream(file);
	    
	    if(!in->atEnd()) {
		geom = in->readLine();
	    }
	    
	    qDebug("Geometry loaded form a file: " + url.toLatin1());
    	}
    	
    	file->close();
	
    }
    
    if(geom == nullptr) {
	geom = "800x600";
	qWarning("No geometry provided on cmd-line / a file, loaded hardcoded value: " + geom.toLatin1());
    }
    
    int width, height;
    
    QStringList parts = geom.split("x");
    if(parts.count() < 2) {
	qWarning("ERROR: Invalid geometry specified, falling back to 800x600");
	width = 800;
	height = 600;
    } else {
	width  = parts.at(0).toInt();
	height = parts.at(1).toInt();
    }
    

    // Initialize window

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

    window->resize(width, height);
    window->setLayout(layout);
    layout->addWidget(webview);
    webview->show();
    window->showMaximized();

    // Exec...

    return app.exec();
}
