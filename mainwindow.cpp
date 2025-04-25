#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <fstream>

#include "Io.h"
#include "Parse.h"
#include "Test.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GCodeOptimizerQt)
{
    ui->setupUi(this);

    // Prepojenie tlacidiel s funkciami
    connect(ui->buttonInputBrowse, &QPushButton::clicked, this, &MainWindow::onButtonInputBrowseClicked);
    connect(ui->buttonOutputBrowse, &QPushButton::clicked, this, &MainWindow::onButtonOutputBrowseClicked);
    connect(ui->buttonOptimize, &QPushButton::clicked, this, &MainWindow::onButtonOptimizeClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onButtonInputBrowseClicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Vyberte vstupny subor", "", "CNC Files (*.cnc);;All Files (*)");
    if (!fileName.isEmpty())
    {
        ui->lineEditInput->setText(fileName);
        ui->textEditLog->append("[INFO] Vybraty vstupny subor: " + fileName);

        // Nastavime vystupny subor na zaklade vstupneho
        QFileInfo inputInfo(fileName);
        QString outputPath = inputInfo.absolutePath() + "/output.cnc";
        ui->lineEditOutput->setText(outputPath);
        ui->textEditLog->append("[INFO] Predvoleny vystupny subor nastaveny na: " + outputPath);
    }
}


void MainWindow::onButtonOutputBrowseClicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Vyberte vystupny subor", "", "CNC Files (*.cnc);;All Files (*)");
    if (!fileName.isEmpty())
    {
        ui->lineEditOutput->setText(fileName);
        ui->textEditLog->append("[INFO] Vybraty vystupny subor: " + fileName);
    }
}

void MainWindow::onButtonOptimizeClicked()
{
    QString inputFile = ui->lineEditInput->text();
    QString outputFile = ui->lineEditOutput->text();

    if (inputFile.isEmpty() || outputFile.isEmpty())
    {
        QMessageBox::warning(this, "Chyba", "Musite vybrat vstupny aj vystupny subor.");
        return;
    }

    try
    {
        ui->textEditLog->append("[INFO] Nacitavam vstupny subor...");
        auto lines = readLinesFromFile(inputFile.toStdString());

        ui->textEditLog->append("[INFO] Parsujem prikazy...");
        auto commands = parseCommands(lines);

        ui->textEditLog->append("[INFO] Optimalizujem prikazy...");
        auto optimized = optimize(std::move(commands), EOptimizeMode::returning_back | EOptimizeMode::the_same_movement);

        std::vector<std::string> outputLines;
        outputLines.reserve(optimized.size());

        for (const auto& cmd : optimized)
        {
            outputLines.push_back(cmd->toString());
        }

        writeLinesToFile(outputFile.toStdString(), outputLines);

        ui->textEditLog->append("[INFO] Optimalizacia dokoncena. Zapisane do suboru.");

        // ------- Nova cast: nacitanie vystupneho suboru a vypis do outputBrowser --------

        QStringList fileContent;
        std::ifstream outputFileStream(outputFile.toStdString());
        std::string line;

        if (outputFileStream.is_open())
        {
            while (std::getline(outputFileStream, line))
            {
                fileContent << QString::fromStdString(line);
            }
            outputFileStream.close();

            // Nastavime obsah vystupneho browsera
            ui->outputBrowser->setPlainText(fileContent.join('\n'));
            ui->textEditLog->append("[INFO] Obsah vystupneho suboru zobrazeny.");
        }
        else
        {
            ui->textEditLog->append("[WARNING] Nepodarilo sa otvorit vystupny subor na citanie.");
        }
    }
    catch (const std::exception& ex)
    {
        QMessageBox::critical(this, "Error", ex.what());
        ui->textEditLog->append("[ERROR] " + QString::fromStdString(ex.what()));
    }
}
