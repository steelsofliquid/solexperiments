#include <QApplication>
#include <QMainWindow>
#include <QTableWidget>
#include <QTableWidgetItem>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QMainWindow window;
    window.setWindowTitle("Spreadsheet Editor");

    // Create a table widget to display the spreadsheet
    QTableWidget *tableWidget = new QTableWidget(&window);
    tableWidget->setRowCount(10);
    tableWidget->setColumnCount(10);
    window.setCentralWidget(tableWidget);

    // Set the default values for each cell in the spreadsheet
    for (int row = 0; row < 10; ++row)
    {
        for (int col = 0; col < 10; ++col)
        {
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setData(Qt::EditRole, 0.0);
            tableWidget->setItem(row, col, item);
        }
    }

    window.show();

    return app.exec();
}
