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
    int wait_interval = 50;

    while (1) {
        /* Algorithm:
         *
         * 1) Check if fname is not null
         *      -> true:    cp val into org_fname and reset fname
         *      -> false:   check if org_fname is null
         *              -> true:    wait unitl change
         *              -> false:   load file, read file, plot graph
         */

        // Check if the file name has not changed
        if (this->fname.isNull() || this->fname.isEmpty()) {
            // Check if the file name is empty or null and wait
            if (org_fname.isNull() || org_fname.isEmpty()) {
                msleep(wait_interval);
            } else {
                QFile *file = new QFile(org_fname);
                QVector<double> y;

                // Check if file could get opened, is readable and the content is plain text
                if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
                    break;

                // Read the content of the file
                QTextStream in(file);
                while (!in.atEnd()) {
                    // Read a line
                    QString line = in.readLine();
                    // Parse the values into int and store them in the vector
                    y.append(line.toInt());
                }

                // Create a simple x axis that represents the count of measured values
                QVector<double> x(y.size());
                for(int i = 0; i < x.size(); i++) {
                    x[i] = i;
                }

                // Set the data, resize the range and replot the graph
                this->plot->graph(0)->setData(x, y);
                this->plot->xAxis->setRange(0, y.size());
                this->plot->replot();

                // Close the file to make sure no *_ACCESS errors occur
                file->close();
                // Close to prevent a flickering plot and overlapping painting jobs of the UI
                msleep(wait_interval);
            }
        // If file name has changed
        } else {
            // Check if the file name has literrally changed. Otherwise ignore the new file name.
            if (QString::compare(this->fname,org_fname) != 0 ) {
                org_fname = this->fname;
            }

            // Reset the file name so it can recoginzed again
            this->fname.clear();
        }
    }
}
