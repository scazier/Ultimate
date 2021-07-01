#include "circlebar.h"
#include "ui_circlebar.h"

CircleBar::~CircleBar()
{
    delete ui;
    delete mChart;
}

CircleBar::CircleBar(const QString &title, const QStringList &colors, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CircleBar),
    mColors(colors),
    mChart(new QChart),
    mChartView(new QChartView(mChart)),
    mSeries(new QPieSeries(this)),
    mChartValue(new QLabel(this))
{
    ui->setupUi(this);

    ui->lblCircleChartTitle->setText(title);

    init();
}

void CircleBar::init()
{
    QColor transparent("transparent");

    // series settings
    mSeries->setHoleSize(0.80);
    mSeries->setPieSize(165);
    mSeries->setPieStartAngle(-140);
    mSeries->setPieEndAngle(140);
    mSeries->setLabelsVisible(false);
    mSeries->append("Used", 0);
    mSeries->append("Free", 0);
    mSeries->slices().first()->setBorderColor(transparent);
    mSeries->slices().last()->setBorderColor(transparent);
    QConicalGradient gradient;
    gradient.setAngle(185);
    for (int i = 0; i < mColors.count(); ++i) {
        gradient.setColorAt(i, QColor(mColors.at(i)));
    }
    mSeries->slices().first()->setBrush(gradient);

    // chart settings
    mChart->setBackgroundBrush(QBrush(transparent));
    mChart->setContentsMargins(-20, -20, -20, -45);
    mChart->addSeries(mSeries);
    mChart->legend()->hide();

    // chartview settings
    mChartView->setRenderHint(QPainter::Antialiasing);

    ui->layoutCircleBar->insertWidget(1, mChartView);

    QGridLayout *grid = new QGridLayout(mChartView);
    grid->addWidget(mChartValue, 0, 0, Qt::AlignCenter);
    mChartValue->move(0,10);

    connect(SignalMapper::ins(), &SignalMapper::sigChangedAppTheme, [=] {
        QSettings *styleValues = AppManager::ins()->getStyleValues();
        mChartView->setBackgroundBrush(QColor(styleValues->value("@circleChartBackgroundColor").toString()));
        mSeries->slices().last()->setColor(styleValues->value("@pageContent").toString()); // trail color
    });
}

void CircleBar::setValue(const int &value, const QString &valueText)
{
    mSeries->slices().first()->setValue(value);
    mSeries->slices().last()->setValue(1000-value);

    mChartValue->setText(valueText);
}
