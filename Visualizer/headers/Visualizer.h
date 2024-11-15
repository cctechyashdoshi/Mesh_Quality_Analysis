#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QProgressBar>
#include <QWidget>
#include <QCheckBox>
#include "Triangulation.h"
#include "OpenGlWidget.h"
#include "ModifiedTriangulation.h"

using namespace Geometry;

class Visualizer : public QMainWindow
{
    Q_OBJECT

public:
    Visualizer(QWidget *parent = nullptr);
    ~Visualizer();

private slots:
    void onLoadFileClick();
    void onBoundingBoxCheckboxToggled(bool checked);

private:
    void setupUi();
	void createBoundingBoxTriangulation(double _minX, double _minY, double _minZ, double _maxX, double _maxY, double _maxZ);
	void createOrthgonilityTriangulation(ModifiedTriangulation& inTriangulation);
    void createAspectRatioTriangulation(ModifiedTriangulation& inTriangulation);
	OpenGlWidget::Data convertOrthogonalityTriangulationToGraphcsObject(ModifiedTriangulation orthogonalityTriangulation);
	OpenGlWidget::Data convertAspectRatioTriangulationToGraphcsObject(ModifiedTriangulation aspectRatioTriangulation);
    OpenGlWidget::Data convertBoundingBoxTriangulatonToGraphcsObject(std::vector<std::vector<std::vector<double>>> boundingBoxTriangulation);
    OpenGlWidget::Data convertTrianglulationToGraphicsObject(const ModifiedTriangulation& inTriangulation);
    ModifiedTriangulation readFile(const QString& filePath);
    void writeFile(const QString& filePath, const ModifiedTriangulation& tri);

private:
    std::vector<std::vector<std::vector<double>>> boundingBoxTriangulation;
	ModifiedTriangulation triangulation;
    ModifiedTriangulation orthogonalityTriangulation;
	ModifiedTriangulation aspectRatioTriangulation;

    QPushButton* loadFile;
    QPushButton* translate;
    QPushButton* exportFile;

    OpenGlWidget* openglWidgetInput;

    QProgressBar* progressBar;

    QCheckBox* firstCheckBox;
    QCheckBox* secondCheckBox;
    QCheckBox* thirdCheckBox;

    QTextEdit* param1textbox;
    QTextEdit* param2textbox;
    QTextEdit* param3textbox;
    QTextEdit* param4textbox;
    QTextEdit* param5textbox;
    QTextEdit* param6textbox;
    QTextEdit* param7textbox;

    double param1Value;  // No. of Triangles
    double param2Value;  // Surface Area
    double param3Value;  // Triangle Density
    double param4Value;  // Object Length
    double param5Value;  // No. of Vertices
    double param6Value;  // Object Height
    double param7Value;  // Object Breadth

    QTextEdit* Parameter1;
    QTextEdit* Parameter2;
    QTextEdit* Parameter3;
    QTextEdit* Parameter4;
    QTextEdit* Parameter5;
    QTextEdit* Parameter6;
    QTextEdit* Parameter7;

    QTextEdit* createReadOnlyTextEdit(const QString& text, QWidget* parent);

    QVector<GLfloat> vertices;

    QWidget* containerWidget;

    // translation data
    QString inputFilePath;
    QString exportFileName;

};
