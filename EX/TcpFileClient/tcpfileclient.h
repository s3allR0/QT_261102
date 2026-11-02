#ifndef TCPFILECLIENT_H
#define TCPFILECLIENT_H

#include <QDialog>
#include <QtNetwork>
#include <QtWidgets>

class TcpFileClient : public QDialog
{
    Q_OBJECT

public:
    explicit TcpFileClient(QWidget *parent = nullptr);
    ~TcpFileClient() override;
private slots:
    void start();
    void startTransfer();
    void openFile();
    void updateClientProgress(qint64 numBytes);
private:
    QProgressBar *clientProgressBar;
    QLabel *clientStatusLabel;
    QPushButton *startButton;
    QPushButton *openButton;
    QPushButton *quitButton;
    QDialogButtonBox *buttonBox;
    QTcpSocket tcpClient;

    qint64 totalBytes;
    qint64 bytesWritten;
    qint64 bytesToWrite;
    qint64 loadsize;
    QString fileName;
    QFile *localFile;
    QByteArray outBlock;
};
#endif // TCPFILECLIENT_H
