#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QProgressBar>
#include <QWidget>
#include <QCheckBox>
#include "OpenGlWidget.h"
#include "Triangulation.h"
#include "QualityAnalysis.h"

using namespace Geometry;
using namespace QualityAnalysis;

class Visualizer : public QMainWindow
{
    Q_OBJECT

public:
    Visualizer(QWidget *parent = nullptr);
    ~Visualizer();

private slots:
    void onLoadFileClick();
    void onFirstCheckBoxChanged(int state);
    void onSecondCheckBoxChanged(int state);

private:
    void setupUi();
    Triangulation readFile(const QString& filePath);
	void Visualizer::fireFunction(int option);
    OpenGlWidget::Data convertTriangulationToGraphicsObject(Triangulation triangulation);
    void resetObjectIds();

private:
	Triangulation triangulation;

    QPushButton* loadFile;
    QPushButton* translate;
    QPushButton* exportFile;

    OpenGlWidget* openglWidgetInput;

    QProgressBar* progressBar;

    QCheckBox* firstCheckBox;
    QCheckBox* secondCheckBox;

    QVector<GLfloat> vertices;

    QWidget* containerWidget;

    QString inputFilePath;

    MeshQualityData orthogonalityData;
	MeshQualityData aspectRatioData;

    int origObjId;
    int orthoObjectId;
    int aspectObjId;
};
