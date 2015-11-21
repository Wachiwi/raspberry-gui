#include "livefileplotter.h"

/**
 * Default constructor.
 * @brief LiveFilePlotter::LiveFilePlotter
 * @param parent
 */
LiveFilePlotter::LiveFilePlotter(QObject *parent) : QThread(parent) {}

/**
 * Default desconstructor.
 * @brief LiveFilePlotter::~LiveFilePlotter
 */
LiveFilePlotter::~LiveFilePlotter() {}

/**
 * Event handler after the 'changeFile()' event from the 'MainWindow'.
 * @brief LiveFilePlotter::changeFile
 * @param fname The name of the new file.
 * @param plot Pointer to the original plot.
 */
void LiveFilePlotter::changeFile(QString fname, QCustomPlot *plot){
    this->fname = fname;
    this->plot = plot;
}

/**
 * Essential thread that is watching a specific file and is updating
 * the data in the plot of 'MainWindow'. It watches the file by checking
 * every 50ms. Otherwise the software is unstable.
 *
 * ToDo: Improve simplicity and improve algorithm concerning:
 *  - Remove read values from file
 *  - React only to new values
 *  - Delegate the 'replot' responsibility to 'MainWindow' by emitting an event
 *
 * @brief LiveFilePlotter::run
 */
void LiveFilePlotter::run() {
    QString org_fname;

    while (1) {
        // Check if fname is not null
        //  true: cp val into org_fname and reset fname
        //  false: check if org_fname is null
        //         true: wait unitl change
        //         false: load file, read file, plot graph
        if (this->fname.isNull() || this->fname.isEmpty()) {
            if (org_fname.isNull() || org_fname.isEmpty()) {
                msleep(10);
            } else {
                QFile *file = new QFile(org_fname);
                QVector<double> y;

                // Check if file could get opened, is readable and content is plain text
                if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
                    break;

                // Read content of file
                QTextStream in(file);
                while (!in.atEnd()) {
                   QString line = in.readLine();
                   // Parse the read values into int and store them in the vector
                   y.append(line.toInt());
                }

                // Create a simple x axis that represents the count of measured values
                QVector<double> x(y.size());
                for(int i = 0; i < x.size(); i++) {
                    x[i] = i;
                }

                // Add a graph to the canvas, label the axis and set the data
                this->plot->graph(0)->setData(x, y);
                this->plot->xAxis->setRange(0, y.size());
                this->plot->replot();

                // Close the file to make sure
                file->close();
                msleep(50);
            }
        } else {
            // Check if the file name has changed. Otherwise ignore the new file name.
            if (QString::compare(this->fname,org_fname) != 0 ) {
                org_fname = this->fname;
            }

            this->fname.clear();
        }
    }
}
