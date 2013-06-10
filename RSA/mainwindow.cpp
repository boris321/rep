#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "superlong.h"
#include <string>
#include <fstream>
#include <QTime>

using namespace std;


// �������� - �������� ��������

void MainWindow::Start()
{
    Inicialization(); // ������������� � ��������� ������� ����������

    string str;

    // ������������ ����������
    superlong pB, qB, nB, eB, n, e, mA, meA, me, fiB, dB, mB;

    // �������� - �������� ��������

    // **************************************************************************

    // ��� �������� ������� p � q
    pB.get( ui->lineEdit_pBob->text().toStdString() );  // ������� �����
    qB.get( ui->lineEdit_qBob->text().toStdString() );  // ������� �����
    // ��� ���������
    nB = pB * qB;                   // n = p * q
    fiB = ( pB - 1) * ( qB - 1 );   // fi (������� ������)
    // ��� �������� e (�������� ����������)
    eB.get( ui->lineEdit_eBob->text().toStdString() );
    // ��� ��������� d = e^-1 (�������� ����������)
    dB = evklid_ext_x( eB, fiB );
    // ��� ��������� n � e
    n = nB;
    e = eB;

    // ����� �������� ��������� m
    mA.get( ui->lineEdit_mAlisa->text().toStdString() );
    // ����� ������������� ���������
    meA = powm( mA, e, n );
    // ����� ��������� ������������� ��������� me
    me = meA;

    // ��� ������������� ���������
    mB = powm( me, dB, n );

    // **************************************************************************

    // ����� ���������� �� �����
    nB.give( str );
    ui->lineEdit_nBob->setText( QString::fromStdString( str ) );
    eB.give( str );
    ui->lineEdit_eBob->setText( QString::fromStdString( str ) );
    n.give( str );
    ui->lineEdit_n->setText( QString::fromStdString( str ) );
    e.give( str );
    ui->lineEdit_e->setText( QString::fromStdString( str ) );
    mA.give( str );
    ui->lineEdit_mAlisa->setText( QString::fromStdString( str ) );
    meA.give( str );
    ui->lineEdit_meAlisa->setText( QString::fromStdString( str ) );
    me.give( str );
    ui->lineEdit_me->setText( QString::fromStdString( str ) );
    fiB.give( str );
    ui->lineEdit_fiBob->setText( QString::fromStdString( str ) );
    dB.give( str );
    ui->lineEdit_dBob->setText( QString::fromStdString( str ) );
    mB.give( str );
    ui->lineEdit_mBob->setText( QString::fromStdString( str ) );
}

 // ������������� � ��������� ������� ����������
void MainWindow::Inicialization()
{
    if ( ui->lineEdit_pBob->text().isEmpty() ) generate_p();
    if ( ui->lineEdit_qBob->text().isEmpty() ) generate_q();
    if ( ui->lineEdit_eBob->text().isEmpty() ) generate_e();
    if ( ui->lineEdit_mAlisa->text().isEmpty() ) generate_m();
}

void MainWindow::generate_p()
{
    superlong p;
    string str;
    p = generatep( "1000000000000" );
    p.give( str );
    ui->lineEdit_pBob->setText( QString::fromStdString( str ));
}

void MainWindow::generate_q()
{
    superlong q;
    string str;
    q = generatep( "1000000000000" );
    q.give( str );
    ui->lineEdit_qBob->setText( QString::fromStdString( str ));
}

void MainWindow::generate_n() {
    if ( ui->lineEdit_pBob->text().isEmpty() ) generate_p();
    if ( ui->lineEdit_qBob->text().isEmpty() ) generate_q();
    superlong p, q, n;
    string str;
    p.get( ui->lineEdit_pBob->text().toStdString() );
    q.get( ui->lineEdit_pBob->text().toStdString() );
    n = p * q;
    n.give( str );
    ui->lineEdit_nBob->setText( QString::fromStdString( str ));
}

void MainWindow::generate_fi() {
    if ( ui->lineEdit_pBob->text().isEmpty() ) generate_p();
    if ( ui->lineEdit_qBob->text().isEmpty() ) generate_q();
    superlong p, q, fi;
    string str;
    p.get( ui->lineEdit_pBob->text().toStdString() );
    q.get( ui->lineEdit_pBob->text().toStdString() );
    fi = ( p - 1 ) * ( q - 1 );
    fi.give( str );
    ui->lineEdit_fiBob->setText( QString::fromStdString( str ));
}

void MainWindow::generate_e() {
    if ( ui->lineEdit_fiBob->text().isEmpty() ) generate_fi();
    superlong fi, e;
    string str;
    fi.get( ui->lineEdit_pBob->text().toStdString() );
    e = generatep( fi );
    e.give( str );
    ui->lineEdit_eBob->setText( QString::fromStdString( str ));
}

void MainWindow::generate_m() {
    ui->lineEdit_mAlisa->setText( "2013" );
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_Start, SIGNAL( clicked() ), SLOT( Start() ));
    connect(ui->pushButton_pBob, SIGNAL( clicked() ), SLOT( generate_p() ));
    connect(ui->pushButton_qBob, SIGNAL( clicked() ), SLOT( generate_q() ));
    connect(ui->pushButton_eBob, SIGNAL( clicked() ), SLOT( generate_e() ));

    // ������������� ���������� ��������� �����
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
