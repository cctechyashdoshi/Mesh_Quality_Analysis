#include <QFileDialog>
#include <QGridLayout>
#include <QDebug>
#include "Visualizer.h"
#include "STLReader.h"
#include "OBJReader.h"
#include "OBJWriter.h"
#include "STLWriter.h"
#include "DataWriter.h"
#include "QualityAnalysis.h"
#include "ModifiedTriangulation.h"
#include "ModifiedTriangle.h"

Visualizer::Visualizer(QWidget* parent) : QMainWindow(parent)
{
    setupUi();
    connect(loadFile, &QPushButton::clicked, this, &Visualizer::onLoadFileClick);
}

Visualizer::~Visualizer()
{
}

void Visualizer::setupUi()
{
    loadFile = new QPushButton("Load File", this);
    openglWidgetInput = new OpenGlWidget(this);
    progressBar = new QProgressBar(this);
    containerWidget = new QWidget(this);
    firstCheckBox = new QCheckBox("Bounding Box", containerWidget);
    secondCheckBox = new QCheckBox("Aspect Ratio", containerWidget);
    thirdCheckBox = new QCheckBox("Orthogonality", containerWidget);
    param1textbox = new QTextEdit("", containerWidget);
    param2textbox = new QTextEdit("", containerWidget);
    param3textbox = new QTextEdit("", containerWidget);
    param4textbox = new QTextEdit("", containerWidget);
    param5textbox = new QTextEdit("", containerWidget);
    Parameter1 = createReadOnlyTextEdit("No. of Triangles", containerWidget);
    Parameter2 = createReadOnlyTextEdit("Surface Area", containerWidget);
    Parameter3 = createReadOnlyTextEdit("Triangle Density", containerWidget);
    Parameter4 = createReadOnlyTextEdit("ObjectLength", containerWidget);
    Parameter5 = createReadOnlyTextEdit("No. of Vertices", containerWidget);

    QString buttonStyle = "QPushButton {"
        "    background-color: #4CAF50;"
        "    color: white;"
        "    border: none;"
        "    padding: 10px 20px;"
        "    font-size: 16px;"
        "    border-radius: 5px;"
        "    border: 2px solid black;"
        "}"
        "QPushButton:hover {"
        "    background-color: #45a049;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #3e8e41;"
        "}";

    QString widgetStyle = "QWidget {"
        "    background-color: #333;"
        "    color: #f5f5f5;"
        "}";

    QString containerStyle = "background-color: lightyellow; color: black;";

    loadFile->setStyleSheet(buttonStyle);
    this->setStyleSheet(widgetStyle);
    containerWidget->setStyleSheet(containerStyle);

    QVBoxLayout* containerLayout = new QVBoxLayout(containerWidget);
    containerLayout->addWidget(firstCheckBox);
    containerLayout->addWidget(secondCheckBox);
    containerLayout->addWidget(thirdCheckBox);
    containerLayout->addWidget(Parameter1);
    containerLayout->addWidget(param1textbox);
    containerLayout->addWidget(Parameter2);
    containerLayout->addWidget(param2textbox);
    containerLayout->addWidget(Parameter3);
    containerLayout->addWidget(param3textbox);
    containerLayout->addWidget(Parameter4);
    containerLayout->addWidget(param4textbox);
    containerLayout->addWidget(Parameter5);
    containerLayout->addWidget(param5textbox);

    QGridLayout* layout = new QGridLayout();
    QWidget* centralWidget = new QWidget(this);

    layout->addWidget(loadFile, 0, 0, 1, 3);
    layout->addWidget(openglWidgetInput, 1, 0, 1, 3);
    layout->addWidget(progressBar, 2, 0, 1, 6);
    layout->addWidget(containerWidget, 0, 3, 2, 3);

    layout->setContentsMargins(20, 20, 20, 20);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
}

void Visualizer::onLoadFileClick()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("files (*.stl *.obj)"));
    if (!fileName.isEmpty())
    {
        inputFilePath = fileName;
        triangulation = readFile(inputFilePath);
        //OpenGlWidget::Data data = convertTrianglulationToGraphicsObject(triangulation);
        //openglWidgetInput->setData(data);
        //qDebug() << "---------------------------------" << data.normals[0];
        OpenGlWidget::Data data = convertBoundingBoxTriangulatonToGraphcsObject(boundingBoxTriangulation);
        //qDebug() << "---------------------------------" << data.normals[0];
        openglWidgetInput->setData(data);

        QualityAnalysis::QualityAnalysis qualityAnalysis;

        param1Value = triangulation.Triangles.size();  // Example: No. of Triangles
        param2Value = qualityAnalysis.surfaceArea(triangulation);  // Surface Area calculation method
        param3Value = qualityAnalysis.triangleDensity(triangulation);  // Triangle Density calculation method
        param4Value = qualityAnalysis.objectLength(triangulation);  // Volume calculation method
        param5Value = qualityAnalysis.numberOfVertices(triangulation);  // Example: No. of Vertices

        // Update the textboxes with the new values
        param1textbox->setText(QString::number(param1Value));
        param2textbox->setText(QString::number(param2Value));
        param3textbox->setText(QString::number(param3Value));
        param4textbox->setText(QString::number(param4Value));
        param5textbox->setText(QString::number(param5Value));
    }
}

Triangulation Visualizer::readFile(const QString& filePath)
{
    Triangulation tri;

    if (filePath.endsWith(".stl", Qt::CaseInsensitive))
    {
        STLReader reader;
        reader.read(filePath.toStdString(), tri);
    }
    else if (filePath.endsWith(".obj", Qt::CaseInsensitive))
    {
        OBJReader reader;
        reader.read(filePath.toStdString(), tri);
    }
    
	ModifiedTriangulation modifiedTriangulation;
    QualityAnalysis::QualityAnalysis qualityAnalysis;

    modifiedTriangulation._minX = qualityAnalysis.minX(tri);
	modifiedTriangulation._minY = qualityAnalysis.minY(tri);
	modifiedTriangulation._minZ = qualityAnalysis.minZ(tri);
	modifiedTriangulation._maxX = qualityAnalysis.maxX(tri);
	modifiedTriangulation._maxY = qualityAnalysis.maxY(tri);
	modifiedTriangulation._maxZ = qualityAnalysis.maxZ(tri);

    Visualizer::createBoundingBoxTriangulation(modifiedTriangulation._minX, modifiedTriangulation._minY, modifiedTriangulation._minZ, modifiedTriangulation._maxX, modifiedTriangulation._maxY, modifiedTriangulation._maxZ);

    return tri;
}

void Visualizer::writeFile(const QString& filePath, const Triangulation& tri)
{
    if (filePath.endsWith(".stl", Qt::CaseInsensitive))
    {
        STLWriter writer;
        writer.Write(filePath.toStdString(), tri, progressBar);
    }
    else if (filePath.endsWith(".obj", Qt::CaseInsensitive))
    {
        ObjWriter writer;
        writer.Write(filePath.toStdString(), tri, progressBar);
    }
}

void Visualizer::createBoundingBoxTriangulation(double _minX, double _minY, double _minZ, double _maxX, double _maxY, double _maxZ)
{
    std::vector<double> p1 = { _minX, _minY, _minZ };
    std::vector<double> p2 = { _maxX, _minY, _minZ };
    std::vector<double> p3 = { _maxX, _maxY, _minZ };
    std::vector<double> p4 = { _minX, _maxY, _minZ };
    std::vector<double> p5 = { _minX, _minY, _maxZ };
    std::vector<double> p6 = { _maxX, _minY, _maxZ };
    std::vector<double> p7 = { _maxX, _maxY, _maxZ };
    std::vector<double> p8 = { _minX, _maxY, _maxZ };

    boundingBoxTriangulation.push_back({ p1, p2, p3 });
    boundingBoxTriangulation.push_back({ p1, p4, p3 });
    boundingBoxTriangulation.push_back({ p1, p4, p8 });
    boundingBoxTriangulation.push_back({ p1, p5, p8 });
    boundingBoxTriangulation.push_back({ p1, p2, p6 });
    boundingBoxTriangulation.push_back({ p1, p5, p6 });
    boundingBoxTriangulation.push_back({ p2, p7, p6 });
    boundingBoxTriangulation.push_back({ p2, p7, p3 });
    boundingBoxTriangulation.push_back({ p5, p6, p7 });
    boundingBoxTriangulation.push_back({ p5, p8, p7 });
    boundingBoxTriangulation.push_back({ p3, p4, p8 });
    boundingBoxTriangulation.push_back({ p3, p7, p8 });
}

void Visualizer::createOrthgonilityTriangulation(ModifiedTriangulation& inTriangulation)
{
	for each (Triangle triangle in inTriangulation.Triangles)
	{
		Point normal = triangle.Normal();
		Point p1 = triangle.P1();
		Point p2 = triangle.P2();
		Point p3 = triangle.P3();
		Triangle t(normal, p1, p2, p3);
		orthogonalityTriangulation.Triangles.push_back(t);

        progressBar->setValue(Vcount);
        progressBar->setRange(0, inTriangulation.Triangles.size() - 1);
        Vcount++;
	}
}

void Visualizer::createAspectRatioTriangulation(ModifiedTriangulation& inTriangulation)
{
	for each (Triangle triangle in inTriangulation.Triangles)
	{
		Point normal = triangle.Normal();
		Point p1 = triangle.P1();
		Point p2 = triangle.P2();
		Point p3 = triangle.P3();
		Triangle t(normal, p1, p2, p3);
		aspectRatioTriangulation.Triangles.push_back(t);

		progressBar->setValue(Vcount);
		progressBar->setRange(0, inTriangulation.Triangles.size() - 1);
		Vcount++;
	}
}

OpenGlWidget::Data Visualizer::convertOrthogonalityTriangulationToGraphcsObject(ModifiedTriangulation orthogonalityTriangulation)
{
    OpenGlWidget::Data data;
    for each (Triangle triangle in orthogonalityTriangulation.Triangles)
    {
        for each (Point point in triangle.Points())
        {
            data.vertices.push_back(orthogonalityTriangulation.UniqueNumbers[point.X()]);
            data.vertices.push_back(orthogonalityTriangulation.UniqueNumbers[point.Y()]);
            data.vertices.push_back(orthogonalityTriangulation.UniqueNumbers[point.Z()]);
        }

        Point normal = triangle.Normal();
        for (size_t i = 0; i < 3; i++)
        {
            data.normals.push_back(orthogonalityTriangulation.UniqueNumbers[normal.X()]);
            data.normals.push_back(orthogonalityTriangulation.UniqueNumbers[normal.Y()]);
            data.normals.push_back(orthogonalityTriangulation.UniqueNumbers[normal.Z()]);
        }
        progressBar->setValue(Vcount);
        progressBar->setRange(0, orthogonalityTriangulation.Triangles.size() - 1);
        Vcount++;
    }
    return data;
}

OpenGlWidget::Data Visualizer::convertAspectRatioTriangulationToGraphcsObject(ModifiedTriangulation aspectRatioTriangulation)
{
    OpenGlWidget::Data data;
    for each (Triangle triangle in aspectRatioTriangulation.Triangles)
    {
        for each (Point point in triangle.Points())
        {
            data.vertices.push_back(aspectRatioTriangulation.UniqueNumbers[point.X()]);
            data.vertices.push_back(aspectRatioTriangulation.UniqueNumbers[point.Y()]);
            data.vertices.push_back(aspectRatioTriangulation.UniqueNumbers[point.Z()]);
        }

        Point normal = triangle.Normal();
        for (size_t i = 0; i < 3; i++)
        {
            data.normals.push_back(aspectRatioTriangulation.UniqueNumbers[normal.X()]);
            data.normals.push_back(aspectRatioTriangulation.UniqueNumbers[normal.Y()]);
            data.normals.push_back(aspectRatioTriangulation.UniqueNumbers[normal.Z()]);
        }
        progressBar->setValue(Vcount);
        progressBar->setRange(0, aspectRatioTriangulation.Triangles.size() - 1);
        Vcount++;
    }
    return data;
}

OpenGlWidget::Data Visualizer::convertBoundingBoxTriangulatonToGraphcsObject(std::vector<std::vector<std::vector<double>>> boundingBoxTriangulation)
{
    OpenGlWidget::Data data;
    int Vcount = 0;
    progressBar->setRange(0, boundingBoxTriangulation.size() - 1);

    for (const auto& triangle : boundingBoxTriangulation)
    {
        for (size_t i = 0; i < 3; ++i)
        {
            data.vertices.push_back(triangle[i][0]);
            data.vertices.push_back(triangle[i][1]);
            data.vertices.push_back(triangle[i][2]);
        }
        Vcount++;
        progressBar->setValue(Vcount);
    }
    return data;
}

OpenGlWidget::Data Visualizer::convertTrianglulationToGraphicsObject(const Triangulation& inTriangulation)
{
    OpenGlWidget::Data data;
    for each (Triangle triangle in inTriangulation.Triangles)
    {
        for each (Point point in triangle.Points())
        {
            data.vertices.push_back(inTriangulation.UniqueNumbers[point.X()]);
            data.vertices.push_back(inTriangulation.UniqueNumbers[point.Y()]);
            data.vertices.push_back(inTriangulation.UniqueNumbers[point.Z()]);
        }

        Point normal = triangle.Normal();
        for (size_t i = 0; i < 3; i++)
        {
            data.normals.push_back(inTriangulation.UniqueNumbers[normal.X()]);
            data.normals.push_back(inTriangulation.UniqueNumbers[normal.Y()]);
            data.normals.push_back(inTriangulation.UniqueNumbers[normal.Z()]);
        }
        progressBar->setValue(Vcount);
        progressBar->setRange(0, inTriangulation.Triangles.size() - 1);
        Vcount++;
    }
    return data;
}

QTextEdit* Visualizer::createReadOnlyTextEdit(const QString& text, QWidget* parent)
{
    QTextEdit* textEdit = new QTextEdit(text, parent);
    textEdit->setReadOnly(true);

    // Center-align the text
    QTextCursor cursor = textEdit->textCursor();
    QTextBlockFormat format;
    format.setAlignment(Qt::AlignCenter);
    cursor.select(QTextCursor::Document);
    cursor.mergeBlockFormat(format);
    textEdit->setTextCursor(cursor);

    // Apply a basic style
    textEdit->setStyleSheet("QTextEdit { color: black; background-color: #f0f0f0; font-size: 14px; }");

    return textEdit;
}
