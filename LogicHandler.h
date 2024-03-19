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

        //getters and setters for QML interactive members
        QString mainResult() const;
        void setMainResult(const QString &newMainResult);
        QString mainExpression() const;
        void setMainExpression(const QString &newMainExpression);
        QString pastResult() const;
        void setPastResult(const QString &newPastResult);
        QString pastExpression() const;
        void setPastExpression(const QString &newPastExpression);

    signals:
        //emits
        void mainResultChanged();
        void mainExpressionChanged();
        void pastResultChanged();
        void pastExpressionChanged();

    //functions that can be called through qml
    public slots:
        //Sends the user from QML to the c++ class to be processed
        void processButtonInput(const QString &buttonText, const QString &buttonType);

    //private LogicHandler class variables
    private:
        //variables accessed in QML through properties
        QString m_mainResult;
        QString m_mainExpression;
        QString m_pastResult;
        QString m_pastExpression;

        //Internal Variables
        int numInputCount;          //Count amount of digits pressed per operator
        int operatorCount;          //Count how many operators are in the expression
        qreal m_tempResult;         //Store result after every operator input
        QString lastOperator;       //Store the last operator entered by user
        QString currentNumInput;    //Stores the current number string that is being input
        bool operatorHanging;       //true when the last button pressed was an operator


        //private functions
        //Returns a number based on the type of button pressed
        int getButtonType(const QString &buttonType);

        //Checks if a string starts with zero
        bool hasLeadingZero(const QString &checkString);

        //checks if a string is negative
        bool isNegative(const QString &checkString);

        //checks if a string contains a decimal
        bool containsDecimal(const QString & checkString);

        //Removes the last input on a string
        void removeLastInput(QString &mainInput);

        //appends or removes a negative sign to the beginning of a string
        void changeSign(QString &mainInput);

        //performs the math operation that has been selected last
        void performOperation(const QString &lastOperator, QString &mainResult, qreal &tempResult);

        //Various basic math functions
        qreal logicAdd(QString &mainResult, qreal &tempResult);
        qreal logicSubtract(QString &mainResult, qreal &tempResult);
        qreal logicDivide(QString &mainResult, qreal &tempResult);
        qreal logicMultiply(QString &mainResult, qreal &tempResult);
        qreal logicRemainder(QString &mainResult, qreal &tempResult);
};

#endif // LOGICHANDLER_H
