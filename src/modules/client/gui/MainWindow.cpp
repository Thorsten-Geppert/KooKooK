#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(
	QWidget *parent
) : QMainWindow(
	parent
), ui(
	new Ui::MainWindow
) {
	ui->setupUi(this);
	
	loginWidget = new LoginWidget(this);
	setCentralWidget(loginWidget);
}

MainWindow::~MainWindow() {
	delete ui;
}

