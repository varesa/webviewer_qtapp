#ifndef MAIN_H
#define MAIN_H

#include <QApplication>
#include <QString>
#include <QWebView>

#define WIDTH 0
#define HEIGHT 1

class WebViewer : public QApplication {
    Q_OBJECT

public:
    WebViewer(int argc, char *argv[]);

private:
    QString getArgsAfter(QString specifier);
    QString readFromFile(QString filename);

    QString getUrl();

    int* parseGeom(QString geomstring);
    int* getGeom();

    QWebView* showWebView(int *geom, QString url);
};

#endif // MAIN_H
