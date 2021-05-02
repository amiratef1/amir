#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "canvas.h"
#include <QFile>
#include <QFileDialog>
#include <QColorDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QImageWriter>
#include <QCloseEvent>
#include <QToolBar>

// MainWindow Constructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMenu *file = menuBar()->addMenu("&File");
    auto *New = new QAction("&New", this);
    file->addAction(New);
    file->addSeparator();
    auto *openAct = new QAction("&Open", this);
    file->addAction(openAct);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));
    auto *openproject = new QAction("&OpenProject", this);
    file->addAction(openproject);
    file->addSeparator();
    auto *save = new QAction("&Save", this);
    file->addAction(save);
    auto *saveas = new QAction("&SaveAs", this);
    file->addAction(saveas);
    file->addSeparator();
    auto *print = new QAction("&Print", this);
    file->addAction(print);
    file->addSeparator();
    auto *closeproject = new QAction("&CloseProject", this);
    file->addAction(closeproject);
    auto *exit = new QAction("&Exit", this);
    file->addAction(exit);
    QMenu *edit = menuBar()->addMenu("&Edit");
    auto *undo = new QAction("&Undo", this);
    edit->addAction(undo);
    auto *redo = new QAction("&Redo", this);
    edit->addAction(redo);
    edit->addSeparator();
    auto *copy = new QAction("&Copy", this);
    edit->addAction(copy);
    auto *paste = new QAction("&Paste", this);
    edit->addAction(paste);
    edit->addSeparator();
    auto *selectall = new QAction("&SelectAll", this);
    edit->addAction(selectall);
    QMenu *image = menuBar()->addMenu("&Image");
    auto *mode = new QAction("&Mode", this);
    image->addAction(mode);
    auto *adjustments = new QAction("&Adjustments", this);
    image->addSeparator();
    image->addAction(adjustments);
    auto *imagesize = new QAction("&ImageSize", this);
    image->addSeparator();
    image->addAction(imagesize);
    auto *canvassize = new QAction("&CanvasSize", this);
    image->addAction(canvassize);
    auto *imagerotation = new QAction("&ImageRotation", this);
    image->addAction(imagerotation);
    auto *crop = new QAction("&Crop", this);
    image->addAction(crop);
    QMenu *layer = menuBar()->addMenu("&Layer");
    auto *newlayer = new QAction("&NewLayer", this);
    layer->addAction(newlayer);
    auto *Delete = new QAction("&Delete", this);
    layer->addAction(Delete);
    layer->addSeparator();
    auto *renamelayer = new QAction("&RenameLayer", this);
    layer->addAction(renamelayer);
    auto *layerstyle = new QAction("&LayerStyle", this);
    layer->addAction(layerstyle);
    auto *smartfilter = new QAction("&SmartFilter", this);
    layer->addAction(smartfilter);
    layer->addSeparator();
    auto *grouplayers = new QAction("&GroupLayers", this);
    layer->addAction(grouplayers);
    auto *ungrouplayers = new QAction("&UnGroupLayers", this);
    layer->addAction(ungrouplayers);
    auto *hidelayers = new QAction("&HideLayers", this);
    layer->addAction(hidelayers);
    layer->addSeparator();
    auto *align = new QAction("&Align", this);
    layer->addAction(align);
    QMenu *select = menuBar()->addMenu("&Select");
    auto *all = new QAction("&All", this);
    select->addAction(all);
    auto *deselect = new QAction("&DeSelect", this);
    select->addAction(deselect);
    select->addSeparator();
    auto *alllayers = new QAction("&All Layers", this);
    select->addAction(alllayers);
    auto *deselectlayers = new QAction("&Deselect Layers", this);
    select->addAction(deselectlayers);
    auto *findlayers = new QAction("&Find Layers", this);
    select->addAction(findlayers);
    QMenu *filter = menuBar()->addMenu("&Filter");
    auto *lastfilter = new QAction("&Last Filter", this);
    filter->addAction(lastfilter);
     filter->addSeparator();
    auto *convertforsmartfilters = new QAction("&Convert For Smart Filters", this);
    filter->addAction(convertforsmartfilters);
     filter->addSeparator();
    auto *lenscorrection = new QAction("&Lens Correction", this);
    filter->addAction(lenscorrection);
     filter->addSeparator();
    auto *blur = new QAction("&Blur", this);
    filter->addAction(blur);
    auto *distort = new QAction("&Distort", this);
    filter->addAction(distort);
    auto *noise = new QAction("&Noise", this);
    filter->addAction(noise);
    auto *pixelate = new QAction("&Pixelate", this);
    filter->addAction(pixelate);
    auto *render = new QAction("&Render", this);
    filter->addAction(render);
    auto *sharpen = new QAction("&Sharpen", this);
    filter->addAction(sharpen);
    auto *stylize = new QAction("&Stylize", this);
    filter->addAction(stylize);
    QMenu *view = menuBar()->addMenu("&View");
    auto *zoomin = new QAction("&Zoom In", this);
    view->addAction(zoomin);
    auto *zoomout = new QAction("&Zoom Out", this);
    view->addAction(zoomout);
    auto *fitonscreen = new QAction("&Fit On Screen", this);
    view->addAction(fitonscreen);
    view->addSeparator();
    auto *fliphorizontal = new QAction("&Flip Horizontal", this);
    view->addAction(fliphorizontal);
    view->addSeparator();
    auto *rulers = new QAction("&Rulers", this);
    view->addAction(rulers);
    view->addSeparator();
    auto *lockguides = new QAction("&Lock Guides", this);
    view->addAction(lockguides);
    auto *clearguides = new QAction("&Clear Guides", this);
    view->addAction(clearguides);
    QMenu *help = menuBar()->addMenu("&Help");
    auto *aboutimageeditor = new QAction("&About Image Editor", this);
    help->addAction(aboutimageeditor);





    this->setStyleSheet("background-color: rgb(57, 57, 57);");
    QPixmap movepix("E:/CS 4/toolbar/img/move.png");
    QPixmap selectionpix("E:/CS 4/toolbar/img/selection.png");
    QPixmap croppix("E:/CS 4/toolbar/img/crop.png");
    QPixmap framepix("E:/CS 4/toolbar/img/frame.png");
    QPixmap brushpix("E:/CS 4/toolbar/img/brush.png");
    QPixmap stamppix("E:/CS 4/toolbar/img/stamp.png");
    QPixmap blurpix("E:/CS 4/toolbar/img/blur.png");
    QPixmap pencilpix("E:/CS 4/toolbar/img/pencil.png");
    QPixmap textpix("E:/CS 4/toolbar/img/text.png");
    QPixmap slicepix("E:/CS 4/toolbar/img/slice.png");
    QPixmap orientationpix("E:/CS 4/toolbar/img/orientation.png");
    QPixmap eraserpix("E:/CS 4/toolbar/img/eraser.png");
    QToolBar *toolbar = addToolBar("main toolbar");
    toolbar->addAction(QIcon(movepix), "move image");
    toolbar->addAction(QIcon(selectionpix), "select an area");
    toolbar->addAction(QIcon(croppix), "crop");
    toolbar->addAction(QIcon(framepix), "make frame");
    toolbar->addAction(QIcon(brushpix), "paint");
    toolbar->addAction(QIcon(stamppix), "clone stamp");
    toolbar->addAction(QIcon(blurpix), "blur");
    toolbar->addAction(QIcon(pencilpix), "pencil for paint");
    toolbar->addAction(QIcon(textpix), "set a text");
    toolbar->addAction(QIcon(slicepix), "slice");
    toolbar->addAction(QIcon(orientationpix), "change orientation");
    toolbar->addAction(QIcon(eraserpix), "erase something");
    addToolBar(Qt::LeftToolBarArea, toolbar);
    toolbar->show();

    // Create the Canvas widget and make it
    // the central widget
    canvas = new Canvas;
    setCentralWidget(canvas);

    // Create actions and menus
    createActions();
    createMenus();

    // Set the title
    setWindowTitle(tr("Image Process"));

    // Size the app
    resize(500,500);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_actioncroppix_triggered()
{
    cv::Mat image1,image2;
    image1=cv::imread("E:\achievements\amir.jpg");
    //Input for the program
    cv::Rect crop_region(250, 10,400, 400);
    // specifies the region of interest in Rectangle form

    image2=image1(crop_region);
    //creates image2 by extracting the specified region of image1

    //Window creation
    cv::imshow("input image ",image1);
    cv::imshow("cropped image ",image2);
    cv::waitKey(0);


}

// User tried to close the app
void MainWindow::closeEvent(QCloseEvent *event)
{
    // If they try to close maybeSave() returns true
    // if no changes have been made and the app closes
    if(maybeSave()){
        event->accept();
    }else {
        // If there have been changes ignore the event
        event->ignore();
    }
}

// Check if the current image has been changed and then
// open a dialog to open a file
void MainWindow::open()
{
    // Check if changes have been made since last save
    // maybeSave() returns true if no changes have been made
    if(maybeSave()){

        // Get the file to open from a dialog
        // tr sets the window title to Open File
        // QDir opens the current dirctory
        QString fileName = QFileDialog::getOpenFileName(this,
                tr("Open File"), QDir::currentPath());

        // If we have a file name load the image and place
        // it in the scribbleArea
        if(!fileName.isEmpty()){
            canvas->openImage(fileName);
        }
    }
}

// Called when the user clicks Save As in the menu
void MainWindow::save()
{
    // A QAction represents the action of the user clicking
    QAction *action = qobject_cast<QAction *>(sender());

    // Stores the array of bytes of the users data
    QByteArray fileFormat = action->data().toByteArray();

    // Pass it to be saved
    saveFile(fileFormat);
}

// Opens a dialog to change the pen color
void MainWindow::penColor()
{
    // Store the chosen color from the dialog
    QColor newColor = QColorDialog::getColor(canvas->penColor());

    // If a valid color set it
    if(newColor.isValid())
    {
        canvas->setPenColor(newColor);
    }
}

// Opens a dialog that allows the user to change the pen width
void MainWindow::penWidth()
{
    // Stores button value
    bool ok;

    // tr("Scribble") is the title
    // the next tr is the text to display
    // Get the current pen width
    // Define the min, max, step and ok button
    int newWidth = QInputDialog::getInt(this, tr("Scribble"),
                                        tr("Select Pen Width : "),
                                        canvas->penWidth(),
                                        1, 50, 1, &ok);
    // Change the pen width
    if(ok)
    {
        canvas->setPenWidth(newWidth);
    }
}

// Open an about dialog
void MainWindow::about()
{
    // Window title and text to display
    QMessageBox::about(this, tr("About"),
                       tr("<p>The <b>Scribble</b> example is awesome</p>"));
}

// Define menu actions that call functions
void MainWindow::createActions()
{
    // Create the action tied to the menu
    openAct = new QAction(tr("&Open"), this);

    // Define the associated shortcut key
    openAct->setShortcuts(QKeySequence::Open);

    // Tie the action to MainWindow::open()
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    // Get a list of the supported file formats
    // QImageWriter is used to write images to files
    foreach(QByteArray format, QImageWriter::supportedImageFormats())  // returns supported image formats by QImageWriter
    {
        QString text = tr("%1...").arg(QString(format).toUpper());  // PNG,JPEG,.. and save it on our Qstring (text)

        // Create an action for each file format
        QAction *action = new QAction(text, this);
        action->setData(format);    // set action for each of the file formats

        // When clicked call MainWindow::save()
        connect(action, SIGNAL(triggered()), this, SLOT(save()));
        saveAsActs.append(action);  // Attach each file format option menu item to Save As
    }

    // Create print action and tie to MainWindow::print()
    printAct = new QAction(tr("&Print..."), this);
    connect(printAct, SIGNAL(triggered()), canvas, SLOT(print()));

    // Create exit action and tie to MainWindow::close()
    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    // Create pen color action and tie to MainWindow::penColor()
    penColorAct = new QAction(tr("&Pen Color..."), this);
    connect(penColorAct, SIGNAL(triggered()), this, SLOT(penColor()));

    // Create pen width action and tie to MainWindow::penWidth()
    penWidthAct = new QAction(tr("Pen &Width..."), this);
    connect(penWidthAct, SIGNAL(triggered()), this, SLOT(penWidth()));

    // Create clear screen action and tie to MainWindow::clearImage()
    clearScreenAct = new QAction(tr("&Clear Screen"), this);
    clearScreenAct->setShortcut(tr("Ctrl+L"));
    connect(clearScreenAct, SIGNAL(triggered()),
            canvas, SLOT(clearImage()));

    // Create about action and tie to MainWindow::about()
    aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    // Create about Qt action and tie to MainWindow::aboutQt()
    aboutQtAct = new QAction(tr("About &Qt"), this);
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

// Create the menubar
void MainWindow::createMenus()
{
    // Create Save As option and the list of file types
    saveAsMenu = new QMenu(tr("&Save As"), this);
    foreach(QAction *action, saveAsActs)
        saveAsMenu->addAction(action);

    // Attach all actions to File
    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addMenu(saveAsMenu);
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    // Attach all actions to Options
    optionMenu = new QMenu(tr("&Options"), this);
    optionMenu->addAction(penColorAct);
    optionMenu->addAction(penWidthAct);
    optionMenu->addSeparator();
    optionMenu->addAction(clearScreenAct);

    // Attach all actions to Help
    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    // Add menu items to the menubar
    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(optionMenu);
    menuBar()->addMenu(helpMenu);
}

// if the user try to leave the application without saving
bool MainWindow::maybeSave()
{
   // Check for changes since last save
    if(canvas->isModified()){
        QMessageBox::StandardButton ret;

        // Image Editor is the title
        // Add text and the buttons
        ret = QMessageBox::warning(this, tr("Image Editor"),
                                   tr("The Image has been modified. \n"
                                      "Do you want to save your changes?"),
                                   QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

   // If save button clicked call for file to be saved
     if(ret == QMessageBox::Save){
         return saveFile("png");

       // If cancel do nothing
     } else if(ret == QMessageBox::Cancel){
         return false;
     }

    }
    return true;
}

bool MainWindow::saveFile(const QByteArray &fileFormat)
{
    // Define path, name and default file type
    QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;

    // Get selected file from dialog box
    // Add the proper file formats and extensions
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                                                    initialPath,
                                                    tr("%1 Files (*.%2);;All Files (*)")
                                                    .arg(QString::fromLatin1(fileFormat.toUpper()))
                                                    .arg(QString::fromLatin1(fileFormat)));
    // If no file do nothing
    if(fileName.isEmpty()){
        return false;
    } else {
        // Call for the file to be saved
        // .constData() --> Returns a pointer to the data stored in the byte array.
        // This function is mostly useful to pass a byte array to a function that accepts a const char *.
        return canvas->saveImage(fileName, fileFormat.constData());
    }
}
