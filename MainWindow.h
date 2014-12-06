
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_MainWindow.h"
#include <QMainWindow>

#include "RpgData.h"

class QButtonGroup;
class QLabel;

class MainWindow : public QMainWindow, private Ui_MainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent = 0);
	~MainWindow();

public slots:
	void fileOpen();

private:
	void createWidgets();
	void setupGUI();
	void unBoldLastRoll();

	std::size_t _last_check_id;
	RpgData _data;
	QButtonGroup* _buttons;
	std::vector< std::vector<QLabel*> > _labels;

private slots:
	void roll(int id);
	void on_buttonLuck_pressed() const;
	void on_buttonD2_pressed() const;
	void on_buttonD3_pressed() const;
	void on_buttonD4_pressed() const;
	void on_buttonD6_pressed() const;
	void on_buttonD8_pressed() const;
	void on_buttonD10_pressed() const;
	void on_buttonD12_pressed() const;
	void on_buttonD20_pressed() const;
	void on_buttonD100_pressed() const;
};

#endif //MAINWINDOW_H
