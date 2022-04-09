#ifndef ERRORHANDLER_HH
#define ERRORHANDLER_HH

#include "mainwindow.hh"

class errorHandler : public QObject
{
    Q_OBJECT
public:
    explicit errorHandler(MainWindow* mw = nullptr);
    QString checkErrors();
private:
    MainWindow* mw_ = nullptr;
};

#endif // ERRORHANDLER_HH
