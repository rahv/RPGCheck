#include "MainWindow.h"

#include <string>
#include <iostream>
#include <QFileDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QButtonGroup>

#include "DiceGen.h"
#include "FileIO.h"

static QString const bold     = "<span style=\"font-size:12pt; font-weight:600\">";
static QString const normal   = "<span style=\"font-size:12pt; font-weight:100\">";
static QString const end      = "</span>";

MainWindow::MainWindow(QWidget* parent)
: _last_check_id(1), _buttons(nullptr), QMainWindow(parent)
{
	setupUi(this);
	FileIO::readStatistics(_n_rolls, _average);
	//setFont(QFont("MS Shell Dlg 2", 12));
}

MainWindow::~MainWindow()
{
	FileIO::writeStatistics(_n_rolls, _average);
	
	delete _buttons;

	std::size_t const n_skills (_data.skill_names.size());
	std::size_t const n_chars  (_data.char_names.size());
	for (std::size_t j=0; j<n_skills; ++j)
		for (std::size_t i=0; i<n_chars; ++i)
			delete (_labels[j])[i];
}

void MainWindow::roll(int id)
{
	std::cout << "  Rolling " << _data.skill_names[id] << "...\n\n";
	unBoldLastRoll();
	std::size_t const n_chars (_data.char_names.size());
	for (std::size_t i=0; i<n_chars; ++i)
	{
		int const mod ((_data.skill_mods[id])[i]);
		int result (0);
		if (id<3)
			result = DiceGen::makeSave(mod, _data.char_names[i], _data.skill_names[id]);
		else
			result = DiceGen::makeSkillCheck(mod, _data.char_names[i], _data.skill_names[id]);
		(_labels[id])[i]->setText(bold + QString::number(result) + end);
	}
	_last_check_id = id;
	std::cout << "\n  * * * *\n\n";
}

void MainWindow::fileOpen()
{
	QString const file_name = QFileDialog::getOpenFileName(this, "Open character file...", "", "*.cfg");
	if (!file_name.isEmpty())
		FileIO::readCharFile(file_name.toStdString(), _data);
	createWidgets();
	setupGUI();
}

void MainWindow::createWidgets()
{
	_buttons = new QButtonGroup();
	std::size_t const n_skills (_data.skill_names.size());
	std::size_t const n_chars  (_data.char_names.size());
	for (std::size_t j=0; j<n_skills; ++j)
	{
		QPushButton* button = new QPushButton("Roll");
		button->setMinimumSize(50,25);
		button->setMaximumSize(50,25);
		_buttons->addButton(button);
		_buttons->setId(button, static_cast<int>(j));

		std::vector<QLabel*> skill_labels;
		for (std::size_t i=0; i<n_chars; ++i)
		{
			skill_labels.push_back(new QLabel(normal + "0" + end));
			skill_labels[i]->setAlignment(Qt::AlignCenter);
		}
		_labels.push_back(skill_labels);
	}
	connect(_buttons, SIGNAL(buttonClicked(int)), this, SLOT(roll(int)));
}

void MainWindow::setupGUI()
{
	int const n_chars (static_cast<int>(_data.char_names.size()));
	for (int i=0; i<n_chars; ++i)
	{
		QLabel* label = new QLabel(this);
		label->setText(bold + QString::fromStdString(_data.char_names[i]) + end);
		label->setAlignment(Qt::AlignCenter);
		this->central_layout->addWidget(label, 0, i+1);
	}

	int const n_skills (static_cast<int>(_data.skill_names.size()));
	for (int j=0; j<n_skills; ++j)
	{
		QLabel* label = new QLabel(this);
		label->setText(normal + QString::fromStdString(_data.skill_names[j]) + end);
		this->central_layout->addWidget(label, j+1, 0);
		for (int i=0; i<n_chars; ++i)
			this->central_layout->addWidget((_labels[j])[i], j+1, i+1);
	}

	QList<QAbstractButton*> const& list = _buttons->buttons();
	auto it = list.constBegin();
	for (int j=0; j<n_skills; ++j)
		this->central_layout->addWidget(dynamic_cast<QPushButton*>(*it++), j+1, n_chars+1);

	QHBoxLayout *hlayout = new QHBoxLayout();
	this->central_layout->addLayout(hlayout, n_skills+1, 0);
	QSpacerItem *const item = new QSpacerItem(1, 1, QSizePolicy::Fixed, QSizePolicy::Expanding);
	hlayout->addSpacerItem(item);
}

void MainWindow::unBoldLastRoll()
{
	std::size_t const n_chars  (_data.char_names.size());
	for (std::size_t i=0; i<n_chars; ++i)
	{
		QString text = (_labels[_last_check_id])[i]->text();
		text.replace(QString("font-weight:600"), QString("font-weight:100"));
		(_labels[_last_check_id])[i]->setText(text);
	}
}

void MainWindow::on_buttonLuck_pressed()
{
	unsigned const result = DiceGen::rollDice(3,6);
	this->result_luck->setText(QString::number(result));
	_average[3] = (_average[3] * _n_rolls[3] + result) / (_n_rolls[3]+3);
	_n_rolls[3] += 3;
}

void MainWindow::on_buttonD2_pressed()
{
	unsigned const n = static_cast<int>(this->nD2->text().toInt());
	unsigned const result = DiceGen::rollDice(n,2);
	this->result_d2->setText(QString::number(result));
	_average[0] = (_average[0] * _n_rolls[0] + result) / (_n_rolls[0]+n);
	_n_rolls[0] += n;
}

void MainWindow::on_buttonD3_pressed()
{
	unsigned const n = static_cast<int>(this->nD3->text().toInt());
	unsigned const result = DiceGen::rollDice(n,3);
	this->result_d3->setText(QString::number(result));
	_average[1] = (_average[1] * _n_rolls[1] + result) / (_n_rolls[1]+n);
	_n_rolls[1] += n;
}

void MainWindow::on_buttonD4_pressed()
{
	unsigned const n = static_cast<int>(this->nD4->text().toInt());
	unsigned const result = DiceGen::rollDice(n,4);
	this->result_d4->setText(QString::number(result));
	_average[2] = (_average[2] * _n_rolls[2] + result) / (_n_rolls[2]+n);
	_n_rolls[2] += n;
}

void MainWindow::on_buttonD6_pressed()
{
	unsigned const n = static_cast<int>(this->nD6->text().toInt());
	unsigned const result = DiceGen::rollDice(n,6);
	this->result_d6->setText(QString::number(result));
	_average[3] = (_average[3] * _n_rolls[3] + result) / (_n_rolls[3]+n);
	_n_rolls[3] += n;
}

void MainWindow::on_buttonD8_pressed()
{
	unsigned const n = static_cast<int>(this->nD8->text().toInt());
	unsigned const result = DiceGen::rollDice(n,8);
	this->result_d8->setText(QString::number(result));
	_average[4] = (_average[4] * _n_rolls[4] + result) / (_n_rolls[4]+n);
	_n_rolls[4] += n;
}

void MainWindow::on_buttonD10_pressed()
{
	unsigned const n = static_cast<int>(this->nD10->text().toInt());
	unsigned const result = DiceGen::rollDice(n,10);
	this->result_d10->setText(QString::number(result));
	_average[5] = (_average[5] * _n_rolls[5] + result) / (_n_rolls[5]+n);
	_n_rolls[5] += n;
}

void MainWindow::on_buttonD12_pressed()
{
	unsigned const n = static_cast<int>(this->nD12->text().toInt());
	unsigned const result = DiceGen::rollDice(n,12);
	this->result_d12->setText(QString::number(result));
	_average[6] = (_average[6] * _n_rolls[6] + result) / (_n_rolls[6]+n);
	_n_rolls[6] += n;
}

void MainWindow::on_buttonD20_pressed()
{
	unsigned const n = static_cast<int>(this->nD20->text().toInt());
	unsigned const result = DiceGen::rollDice(n,20);
	this->result_d20->setText(QString::number(result));
	_average[7] = (_average[7] * _n_rolls[7] + result) / (_n_rolls[7]+n);
	_n_rolls[7] += n;
}

void MainWindow::on_buttonD100_pressed()
{
	unsigned const n = static_cast<int>(this->nD100->text().toInt());
	unsigned const result = DiceGen::rollDice(n,100);
	this->result_d100->setText(QString::number(result));
	_average[8] = (_average[8] * _n_rolls[8] + result) / (_n_rolls[8]+n);
	_n_rolls[8] += n;
}

