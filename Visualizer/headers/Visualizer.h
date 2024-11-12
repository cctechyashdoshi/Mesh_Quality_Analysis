#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QProgressBar>
#include <QWidget>

#include "Triangulation.h"
#include "OpenGlWidget.h"

using namespace Geometry;

class Visualizer : public QMainWindow
{
    Q_OBJECT

public:
    Visualizer(QWidget *parent = nullptr);
    ~Visualizer();

private slots:
    void onLoadFileClick();

private:
    void setupUi();
    OpenGlWidget::Data convertTrianglulationToGraphicsObject(const Triangulation& inTriangulation);
    Triangulation readFile(const QString& filePath);
    void writeFile(const QString& filePath, const Triangulation& tri);

private:
    Triangulation triangulation;
    Triangulation outputTriangulation;

    QPushButton* loadFile;
    QPushButton* translate;
    QPushButton* exportFile;

    OpenGlWidget* openglWidgetInput;

    QProgressBar* progressBar;

    QVector<GLfloat> vertices;

    QWidget* containerWidget;

    // translation data
    QString inputFilePath;
    QString exportFileName;
};
