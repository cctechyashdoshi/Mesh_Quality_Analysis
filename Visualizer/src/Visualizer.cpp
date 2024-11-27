#include <QFileDialog>
#include <QGridLayout>
#include <QDebug>
#include "Visualizer.h"
#include "STLReader.h"
#include "OBJReader.h"
#include "QualityAnalysis.h"

using namespace QualityAnalysis;

Visualizer::Visualizer(QWidget* parent) : QMainWindow(parent)
{
    origObjId = 0;
    orthoObjectId = 0;
    aspectObjId = 0;
    setupUi();
    connect(loadFile, &QPushButton::clicked, this, &Visualizer::onLoadFileClick);
    connect(firstCheckBox, &QCheckBox::stateChanged, this, &Visualizer::onFirstCheckBoxChanged);
    connect(secondCheckBox, &QCheckBox::stateChanged, this, &Visualizer::onSecondCheckBoxChanged);
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
    firstCheckBox = new QCheckBox("Orthogonality", containerWidget);
    secondCheckBox = new QCheckBox("Aspect Ratio", containerWidget);

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

void Visualizer::resetObjectIds()
{
    if (origObjId != -1) {
        openglWidgetInput->removeObject(origObjId);
        origObjId = -1;
    }

    if (orthoObjectId != -1) {
        openglWidgetInput->removeObject(orthoObjectId);
        orthoObjectId = -1;
    }

    if (aspectObjId != -1) {
        openglWidgetInput->removeObject(aspectObjId);
        aspectObjId = -1;
    }
}


void Visualizer::fireFunction(int option)
{
    if (option == 1)
    {
        // Orthogonality
        Visualizer::resetObjectIds();
        OpenGlWidget::Data orthogonalityOpenGlData = convertTriangulationToGraphicsObject(orthogonalityData.orthogonality.triangulation);
        orthoObjectId = openglWidgetInput->addObject(orthogonalityOpenGlData);
    }
    else if (option == 2)
    {
        // Aspect Ratio
        Visualizer::resetObjectIds();
        OpenGlWidget::Data aspectRatioOpenGlData = convertTriangulationToGraphicsObject(aspectRatioData.aspectRatio.triangulation);
        aspectObjId = openglWidgetInput->addObject(aspectRatioOpenGlData);
    }
}

void Visualizer::onLoadFileClick()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("files (*.stl *.obj)"));

    if (!fileName.isEmpty())
    {
        inputFilePath = fileName;
        triangulation = readFile(inputFilePath);
        OpenGlWidget::Data data = convertTriangulationToGraphicsObject(triangulation);
        origObjId = openglWidgetInput->addObject(data);

        MeshAnalysis analyzer;
        analyzer.GetMeshOrthogonalityData(triangulation, orthogonalityData);
        analyzer.GetMeshAspectRatioData(triangulation, aspectRatioData);
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

    return tri;
}

OpenGlWidget::Data Visualizer::convertTriangulationToGraphicsObject(Geometry::Triangulation triangulation)
{
    int Vcount = 0;
    OpenGlWidget::Data data;
    for each(Triangle triangle in triangulation.Triangles)
    {
        for each(Point point in triangle.Points())
        {
            data.vertices.push_back(triangulation.UniqueNumbers[point.X()]);
            data.vertices.push_back(triangulation.UniqueNumbers[point.Y()]);
            data.vertices.push_back(triangulation.UniqueNumbers[point.Z()]);
            data.colors.push_back(triangle.Color()[0]);
            data.colors.push_back(triangle.Color()[1]);
            data.colors.push_back(triangle.Color()[2]);
        }

        Point normal = triangle.Normal();
        for (size_t i = 0; i < 3; i++)
        {
            data.normals.push_back(triangulation.UniqueNumbers[normal.X()]);
            data.normals.push_back(triangulation.UniqueNumbers[normal.Y()]);
            data.normals.push_back(triangulation.UniqueNumbers[normal.Z()]);
        }

        data.drawStyle = OpenGlWidget::DrawStyle::TRIANGLES;

        progressBar->setValue(Vcount);
        progressBar->setRange(0, triangulation.Triangles.size() - 1);
        Vcount++;
    }
    return data;
}

void Visualizer::onFirstCheckBoxChanged(int state)
{
    resetObjectIds();

    if (state == Qt::Checked) {
        QSignalBlocker blocker(secondCheckBox); 
        secondCheckBox->setChecked(false);     
        // Add orthogonality object
        OpenGlWidget::Data orthogonalityOpenGlData = convertTriangulationToGraphicsObject(orthogonalityData.orthogonality.triangulation);
        orthoObjectId = openglWidgetInput->addObject(orthogonalityOpenGlData);
        origObjId = 0; // Disable original object
    }
    else if (state == Qt::Unchecked) {
        // Display original object
        OpenGlWidget::Data originalData = convertTriangulationToGraphicsObject(triangulation);
        origObjId = openglWidgetInput->addObject(originalData);
    }
}

void Visualizer::onSecondCheckBoxChanged(int state)
{
    resetObjectIds();

    if (state == Qt::Checked) {
        QSignalBlocker blocker(firstCheckBox);
        firstCheckBox->setChecked(false);     
        // Add aspect ratio object
        OpenGlWidget::Data aspectRatioOpenGlData = convertTriangulationToGraphicsObject(aspectRatioData.aspectRatio.triangulation);
        aspectObjId = openglWidgetInput->addObject(aspectRatioOpenGlData);
        origObjId = 0; // Disable original object
    }
    else if (state == Qt::Unchecked) {
        // Display original object
        OpenGlWidget::Data originalData = convertTriangulationToGraphicsObject(triangulation);
        origObjId = openglWidgetInput->addObject(originalData);
    }
}
