#include "tcpfileclient.h"

TcpFileClient::TcpFileClient(QWidget *parent)
    : QDialog(parent)
{
    loadsize =1024*4;
    totalBytes=0;
    bytesWritten=0;
    bytesToWrite=0;
    clientProgressBar=new QProgressBar;
    clientStatusLabel=new QLabel(tr("客戶端就緒"));
    startButton=new QPushButton(tr("開始"));
    quitButton=new QPushButton(tr("退出"));
    openButton=new QPushButton(tr("開檔"));
    startButton->setEnabled(false);
    buttonBox=new QDialogButtonBox;
    buttonBox -> addButton(startButton,QDialogButtonBox::ActionRole);
    buttonBox -> addButton(openButton,QDialogButtonBox::ActionRole);
    buttonBox -> addButton(quitButton,QDialogButtonBox::ActionRole);

    QVBoxLayout *mainLayout =new QVBoxLayout;
    mainLayout ->addWidget(clientProgressBar);
    mainLayout ->addWidget(clientStatusLabel);
    mainLayout ->addStretch(1);
    mainLayout ->addSpacing(10);
    mainLayout ->addWidget(buttonBox);
    setLayout(mainLayout);
    setWindowTitle("傳送檔案");

    connect(openButton,SIGNAL(clicked()),this,SLOT(openFile()));
    connect(startButton,SIGNAL(clicked()),this,SLOT(start()));
    connect(&tcpClient,SIGNAL(connect()),this,SLOT(startTransfer()));
    connect(&tcpClient,SIGNAL(bytesWritten(qint64)),this,SLOT(updateClientProgress(qint64)));
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
}

TcpFileClient::~TcpFileClient() = default;

void TcpFileClient::start(){
    startButton ->setEnabled(false);
    bytesWritten=0;
    clientStatusLabel -> setText(tr("連接中..."));
    tcpClient.connectToHost(QHostAddress::LocalHost,49664);
}
void TcpFileClient::startTransfer(){
    localFile=new QFile(fileName);
    if(!localFile->open(QFile::ReadOnly)){
        QMessageBox::warning(this,tr("應用程式"),tr("無法讀取%1:\n%2.").arg(fileName).arg(localFile->errorString()));
    }
}
void TcpFileClient::openFile(){
    fileName=QFileDialog::getOpenFileName(this);
    if(!fileName.isEmpty())startButton -> setEnabled(true);
}
void TcpFileClient::updateClientProgress(qint64 numBytes){

}