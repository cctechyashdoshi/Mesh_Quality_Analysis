#include <QFileDialog>
#include <QGridLayout>
#include <QDebug>
#include "Visualizer.h"
#include "STLReader.h"
#include "OBJReader.h"
#include "QualityAnalysis.h"

Visualizer::Visualizer(QWidget* parent) : QMainWindow(parent)
{
    setupUi();
    connect(loadFile, &QPushButton::clicked, this, &Visualizer::onLoadFileClick);
    connect(firstCheckBox, &QCheckBox::stateChanged, this, &Visualizer::onFirstCheckBoxChanged);
    connect(secondCheckBox, &QCheckBox::stateChanged, this, &Visualizer::onSecondCheckBoxChanged);
    connect(thirdCheckBox, &QCheckBox::stateChanged, this, &Visualizer::onThirdCheckBoxChanged);
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
    param6textbox = new QTextEdit("", containerWidget);
    param7textbox = new QTextEdit("", containerWidget);

    param1textbox->setReadOnly(true);
    param2textbox->setReadOnly(true);
    param3textbox->setReadOnly(true);
    param4textbox->setReadOnly(true);
    param5textbox->setReadOnly(true);
    param6textbox->setReadOnly(true);
    param7textbox->setReadOnly(true);

    Parameter1 = createReadOnlyTextEdit("No. of Triangles", containerWidget);
    Parameter2 = createReadOnlyTextEdit("Surface Area (sq.unit)", containerWidget);
    Parameter3 = createReadOnlyTextEdit("Triangle Density", containerWidget);
    Parameter4 = createReadOnlyTextEdit("Object Length (unit)", containerWidget);
    Parameter5 = createReadOnlyTextEdit("No. of Vertices", containerWidget);
    Parameter6 = createReadOnlyTextEdit("Object Height (unit)", containerWidget);
    Parameter7 = createReadOnlyTextEdit("Object Breadth (unit)", containerWidget);

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
    containerLayout->addWidget(Parameter6);
    containerLayout->addWidget(param6textbox);
    containerLayout->addWidget(Parameter7);
    containerLayout->addWidget(param7textbox);

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

void Visualizer::fireFunction(int option)
{
	QualityAnalysis::QualityAnalysis analyzer;
    if (option == 1) 
    {
        //BoundingBox boundingBox;
        //boundingBox.createBoundingBoxTriangulation();
        //OpenGlWidget::Data data;
        //data = Visualizer::convertBoundingBoxArrayToGraphcsObject(boundingBox.boundingBoxArray);
        //QVector<OpenGlWidget::Data> dataList = { data };
        //openglWidgetInput->setData(dataList);
    }
    else if (option == 2)
    {
        std::vector<std::vector<QualityAnalysis::QualityAnalysis::TriangleAnalysisResult>> orthogonalityAnalysis = analyzer.calculateOrthogonality(triangulation);
        OpenGlWidget::Data data;
        data= Visualizer::convertMeshQualityStructToGraphicsObject(orthogonalityAnalysis);
        openglWidgetInput->addObject(data);
    }
	else if (option == 3)
	{
        std::vector<std::vector<QualityAnalysis::QualityAnalysis::TriangleAnalysisResult>> aspectRatioAnalysis = analyzer.calculateAspectRatio(triangulation);
        OpenGlWidget::Data data;
        data = Visualizer::convertMeshQualityStructToGraphicsObject(aspectRatioAnalysis);
        openglWidgetInput->addObject(data); 
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
        openglWidgetInput->addObject(data);

  //      MeshOperations::QualityAnalysis qualityAnalysis(triangulation);
		//MeshOperations::MeshInformation meshInformation;

  //      param1Value = triangulation.mTriangles.size();  // No. of Triangles
  //      param2Value = qualityAnalysis.caculateTotalsurfaceArea(triangulation);  // Surface Area calculation method
  //      param3Value = meshInformation.triangleDensity(triangulation);  // Triangle Density calculation method
  //      param4Value = meshInformation.objectLength();  // Object Length 
  //      param5Value = meshInformation.numberOfVertices(triangulation);  // No. of Vertices
  //      param6Value = meshInformation.objectHeight();  // Object Height 
  //      param7Value = meshInformation.objectBreadth();  // Object Breadth

        param1textbox->setText(QString::number(param1Value));
        param2textbox->setText(QString::number(param2Value));
        param3textbox->setText(QString::number(param3Value));
        param4textbox->setText(QString::number(param4Value));
        param5textbox->setText(QString::number(param5Value));
        param6textbox->setText(QString::number(param6Value));
        param7textbox->setText(QString::number(param7Value));
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

//OpenGlWidget::Data Visualizer::convertBoundingBoxArrayToGraphcsObject(double boundingBoxArray[24])
//{
//    OpenGlWidget::Data data;
//    int Vcount = 0;
//    progressBar->setRange(0, 23);
//    
//	for (int i = 0; i < 24; i++)
//	{
//		data.vertices.push_back(boundingBoxArray[i]);
//		progressBar->setValue(Vcount);
//		Vcount++;
//	}
//	data.drawStyle = OpenGlWidget::DrawStyle::LINES;
//    return data;
//}

OpenGlWidget::Data Visualizer::convertTriangulationToGraphicsObject(Geometry::Triangulation triangulation)
{
    int Vcount = 0;
    OpenGlWidget::Data data;
    for each (Triangle triangle in triangulation.Triangles)
    {
        for each (Point point in triangle.Points())
        {
            data.vertices.push_back(triangulation.UniqueNumbers[point.X()]);
            data.vertices.push_back(triangulation.UniqueNumbers[point.Y()]);
            data.vertices.push_back(triangulation.UniqueNumbers[point.Z()]);
        }

        Point normal = triangle.Normal();
        for (size_t i = 0; i < 3; i++)
        {
            data.normals.push_back(triangulation.UniqueNumbers[normal.X()]);
            data.normals.push_back(triangulation.UniqueNumbers[normal.Y()]);
            data.normals.push_back(triangulation.UniqueNumbers[normal.Z()]);
        }
        progressBar->setValue(Vcount);
        progressBar->setRange(0, triangulation.Triangles.size() - 1);
        Vcount++;
    }
    return data;
}

OpenGlWidget::Data Visualizer::convertMeshQualityStructToGraphicsObject(std::vector<std::vector<QualityAnalysis::QualityAnalysis::TriangleAnalysisResult>> qualityStruct)
{
    int Vcount = 0;
    OpenGlWidget::Data data;

    for (const auto& triangleGroup : qualityStruct) {
        for (const auto& result : triangleGroup) {
            const Geometry::Triangle& triangle = result.triangle;
            int value = result.value;

            // Extract points and push them into the vertices vector
            for (const auto& point : triangle.Points()) {
                data.vertices.push_back(point.X());
                data.vertices.push_back(point.Y());
                data.vertices.push_back(point.Z());
            }

            // Extract normal and push it into the normals vector
            const Point& normal = triangle.Normal();
            for (int i = 0; i < 3; i++) {
                data.normals.push_back(normal.X());
                data.normals.push_back(normal.Y());
                data.normals.push_back(normal.Z());
            }

            if (value == 0) 
            {
                for (int i = 0; i < 3; ++i) 
                {
                    data.colors.push_back(1.0f);
                    data.colors.push_back(0.0f);
                    data.colors.push_back(0.0f);
                }
            }
            else 
            {
                for (int i = 0; i < 3; ++i) 
                {
                    data.colors.push_back(0.0f);
                    data.colors.push_back(1.0f);
                    data.colors.push_back(0.0f);
                }
            }

            data.drawStyle = OpenGlWidget::DrawStyle::TRIANGLES;

            progressBar->setValue(Vcount);
            progressBar->setRange(0, qualityStruct.size() * triangleGroup.size() - 1);
            Vcount++;
        }
    }

    return data;
}


void Visualizer::onFirstCheckBoxChanged(int state)
{
    if (state == Qt::Checked) {
        secondCheckBox->setChecked(false);
        thirdCheckBox->setChecked(false);
        Visualizer::fireFunction(1); 
    }
}

void Visualizer::onSecondCheckBoxChanged(int state)
{
    if (state == Qt::Checked) {
        firstCheckBox->setChecked(false);
        thirdCheckBox->setChecked(false);
        Visualizer::fireFunction(2);
    }
}

void Visualizer::onThirdCheckBoxChanged(int state)
{
    if (state == Qt::Checked) {
        firstCheckBox->setChecked(false);
        secondCheckBox->setChecked(false);
        Visualizer::fireFunction(3);
    }
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

    // Apply a light background color to both the widget and text area
    QPalette palette = textEdit->palette();
    palette.setColor(QPalette::Base, QColor("#f8f9fa"));  // Light grey background for the text area
    palette.setColor(QPalette::Text, QColor("#333333"));  // Darker text color for readability
    textEdit->setPalette(palette);

    // Apply a basic style
    textEdit->setStyleSheet("QTextEdit {size: 5px; color: #333333; background-color: #f0f0f0; font-size: 14px;}");

    return textEdit;
}
