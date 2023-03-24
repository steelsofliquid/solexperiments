#include <QApplication>
#include <QMainWindow>
#include <QScrollArea>
#include <QLabel>
#include <poppler/qt5/poppler-qt5.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QMainWindow window;
    window.setWindowTitle("PDF Viewer");

    // Load the PDF document
    Poppler::Document *document = Poppler::Document::load("example.pdf");
    if (!document || document->isLocked())
    {
        qDebug() << "Could not load PDF document!";
        return -1;
    }

    // Create a scroll area for the PDF pages
    QScrollArea *scrollArea = new QScrollArea(&window);
    scrollArea->setWidgetResizable(true);
    window.setCentralWidget(scrollArea);

    // Display each page of the PDF as a QLabel inside the scroll area
    for (int i = 0; i < document->numPages(); ++i)
    {
        Poppler::Page *page = document->page(i);
        QImage image = page->renderToImage(96.0, 96.0);

        QLabel *label = new QLabel();
        label->setPixmap(QPixmap::fromImage(image));
        scrollArea->setWidget(label);
    }

    // Clean up the Poppler document object
    delete document;

    window.show();

    return app.exec();
}

