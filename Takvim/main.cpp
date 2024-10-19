#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QCalendarWidget>
#include <QWidget>
#include <QDate>
#include <QLabel>
#include <QTimer>

class TakvimUygulamasi : public QMainWindow {
    Q_OBJECT

public:
    TakvimUygulamasi() {
        setWindowTitle("Takvim");

        QVBoxLayout *layout = new QVBoxLayout();

        takvim = new QCalendarWidget(this);
        takvim->setGridVisible(true);
        layout->addWidget(takvim);

        mevcutTarih = QDate::currentDate();
        takvim->setSelectedDate(mevcutTarih);

        connect(takvim, &QCalendarWidget::clicked, this, &TakvimUygulamasi::tarihGuncelle);

        saatEtiketi = new QLabel(this);
        saatEtiketi->setStyleSheet("font-size: 24px; font-weight: bold;");
        layout->addWidget(saatEtiketi);

        QTimer *zamanlayici = new QTimer(this);
        connect(zamanlayici, &QTimer::timeout, this, &TakvimUygulamasi::zamanGuncelle);
        zamanlayici->start(1000);

        zamanGuncelle();

        QWidget *merkezWidget = new QWidget(this);
        merkezWidget->setLayout(layout);
        setCentralWidget(merkezWidget);
    }

private slots:
    void tarihGuncelle(const QDate &tarih) {
        takvim->setSelectedDate(mevcutTarih);
    }

    void zamanGuncelle() {
        QTime zaman = QTime::currentTime();
        saatEtiketi->setText(zaman.toString("hh:mm:ss"));
    }

private:
    QCalendarWidget *takvim;
    QLabel *saatEtiketi;
    QDate mevcutTarih;
};

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    TakvimUygulamasi w;
    w.show();
    return a.exec();
}

#include "main.moc"
