#include "mainwindow.h"

/**
 * Default constructor
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);

    // Specify event handler and start the 'livePlotter' thread.
    this->livePlotter = new LiveFilePlotter(this);
    QObject::connect(this, &MainWindow::changeFile, livePlotter, &LiveFilePlotter::changeFile);
    QObject::connect(livePlotter, &LiveFilePlotter::finished, livePlotter, &QObject::deleteLater);
    this->livePlotter->start();
}

/**
 * Generic destructor that terminates the live plotter and the ui.
 * Gets called when the application gets terminated.
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow() {
    this->livePlotter->terminate();
    this->livePlotter->wait();

    delete livePlotter;
    delete ui;
}

/**
 * Event handler that gets called when the 'Visaulize' button gets pressed.
 * It opens a file dialog, clears the plot area and emits the event 'changeFile()'.
 * @brief MainWindow::on_visualizeButton_clicked
 */
void MainWindow::on_visualizeButton_clicked() {
    QString s = QFileDialog::getOpenFileName();
    this->ui->srf02Plot->clearGraphs();
    this->ui->srf02Plot->addGraph();
    this->ui->srf02Plot->xAxis->setLabel("Number of measurements");
    this->ui->srf02Plot->yAxis->setLabel("Measured distance in cm");
    this->ui->srf02Plot->xAxis->setRange(0, 1);
    this->ui->srf02Plot->yAxis->setRange(15, 600);
    emit changeFile(s, this->ui->srf02Plot);
}
