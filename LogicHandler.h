#ifndef LOGICHANDLER_H
#define LOGICHANDLER_H

#include <QObject>

class LogicHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString mainResult READ mainResult WRITE setMainResult NOTIFY mainResultChanged);
    Q_PROPERTY(QString mainExpression READ mainExpression WRITE setMainExpression NOTIFY mainExpressionChanged)
    Q_PROPERTY(QString pastResult READ pastResult WRITE setPastResult NOTIFY pastResultChanged);
    Q_PROPERTY(QString pastExpression READ pastExpression WRITE setPastExpression NOTIFY pastExpressionChanged);

    public:
        explicit LogicHandler(QObject *parent = nullptr);

        QString mainResult() const;
        void setMainResult(const QString &newMainResult);
        QString mainExpression() const;
        void setMainExpression(const QString &newMainExpression);
        QString pastResult() const;
        void setPastResult(const QString &newPastResult);
        QString pastExpression() const;
        void setPastExpression(const QString &newPastExpression);

    signals:
        void mainResultChanged();
        void mainExpressionChanged();
        void pastResultChanged();
        void pastExpressionChanged();

    //functions that can be called through qml
    public slots:
        void processButtonInput(const QString &buttonText, const QString &buttonType);

    //private LogicHandler class variables
    private:
        //variables accessed in QML through properties
        QString m_mainResult;
        QString m_mainExpression;
        QString m_pastResult;
        QString m_pastExpression;

       //Internal Variables
        qreal m_tempResult;

        //private functions
        int getButtonType(const QString &buttonType);
        bool hasLeadingZero(const QString &checkString);
        bool isNegative(const QString &checkString);
        bool containsDecimal(const QString & checkString);
        void removeLastInput(QString &mainInput);
        void changeSign(QString &mainInput);
        void performOperation(const QString &lastOperator, QString &mainResult, qreal &tempResult);
        qreal logicAdd(QString &mainResult, qreal &tempResult);
        qreal logicSubtract(QString &mainResult, qreal &tempResult);
        qreal logicDivide(QString &mainResult, qreal &tempResult);
        qreal logicMultiply(QString &mainResult, qreal &tempResult);
        qreal logicRemainder(QString &mainResult, qreal &tempResult);

        bool operatorHanging;   //true when the last button pressed was an operator
        int operatorCount;

        QString lastOperator;

        //debug function
        void printOperator();
        void printTempValue();
        void printMainResult();
};

#endif // LOGICHANDLER_H
