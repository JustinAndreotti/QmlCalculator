#include "LogicHandler.h"
#include <QDebug>
#include <cmath>
//#include <QString>

//********************constructor****************************
LogicHandler::LogicHandler(QObject *parent) : QObject{parent}
{
    m_mainResult = "0";
    m_mainExpression = "";
    m_pastResult = "";
    m_pastExpression = "";
    m_tempResult = 0;
    operatorCount = 0;
    lastOperator = "n/a";
    numInputCount = 0;
    operatorHanging = false;
}





//*********************Members*********************************
QString LogicHandler::mainResult() const
{
    return m_mainResult;
}

void LogicHandler::setMainResult(const QString &newMainResult)
{
    if (m_mainResult == newMainResult)
        return;
    m_mainResult = newMainResult;
    emit mainResultChanged();
}

QString LogicHandler::mainExpression() const
{
    return m_mainExpression;
}

void LogicHandler::setMainExpression(const QString &newMainExpression)
{
    if (m_mainExpression == newMainExpression)
        return;
    m_mainExpression = newMainExpression;
    emit mainExpressionChanged();
}

QString LogicHandler::pastResult() const
{
    return m_pastResult;
}

void LogicHandler::setPastResult(const QString &newPastResult)
{
    if (m_pastResult == newPastResult)
        return;
    m_pastResult = newPastResult;
    emit pastResultChanged();
}

QString LogicHandler::pastExpression() const
{
    return m_pastExpression;
}

void LogicHandler::setPastExpression(const QString &newPastExpression)
{
    if (m_pastExpression == newPastExpression)
        return;
    m_pastExpression = newPastExpression;
    emit pastExpressionChanged();
}





//*****************Functions*******************************
void LogicHandler::processButtonInput(const QString &buttonText, const QString &buttonType)
{
    int inputType = getButtonType(buttonType);
    switch (inputType)
    {
        case 1:     //button is clear
        {
            //reset all values
            setMainResult("0");
            setMainExpression("");
            setPastExpression("");
            setPastResult("");
            operatorCount = 0;
            m_tempResult = 0;
            operatorHanging = false;
            break;
        }
        case 2:     //button is back
        {
            //remove the last input in both result and expression if applicable
            removeLastInput(m_mainResult);
            if (!operatorHanging && numInputCount != 0)
            {
                m_mainExpression.removeLast();
                emit mainExpressionChanged();
            }
            if (numInputCount <= 0)
            {
                numInputCount = 0;
            }
            else numInputCount--;

            emit mainResultChanged();
            break;
        }
        case 3:     //button is changeSign
        {
            changeSign(m_mainResult);
            break;
        }
        case 4:     //button is decimal
        {
            if (operatorHanging)
            {
                setMainExpression(m_mainExpression + "0");
                setMainResult("0");
            }
            if (m_mainExpression.isEmpty())
            {
                setMainExpression("0");
            }
            if (!m_mainResult.contains('.'))
            {
                setMainResult(m_mainResult + '.');
                setMainExpression(m_mainExpression + '.');
                operatorHanging = false;
            }
            if (!m_mainResult.contains('.'))
            {
                numInputCount++;
            }
            break;
        }
        case 5:     //button is operator
        {
            if (!operatorHanging)   //check that last input wasnt an operator
            {
                setMainExpression(m_mainExpression + " " + buttonText + " ");

                //perform background math
                if (operatorCount == 0)
                {
                    m_tempResult = m_mainResult.toDouble();
                }
                else performOperation(lastOperator, m_mainResult, m_tempResult);

                //update flags
                numInputCount = 0;
                lastOperator = buttonText;
                operatorHanging = true;
                operatorCount++;
            }
            break;
        }
        case 6:     //button is number
        {
            //if last button before the number input was an operator then reset reult to 0
            if (operatorHanging)
            {
                setMainResult("0");
            }
            if (hasLeadingZero(m_mainResult))
            {
                if (isNegative(m_mainResult))
                {
                    setMainResult("-");
                }
                else setMainResult("");
            }
            numInputCount++;
            setMainResult(m_mainResult + buttonText);
            setMainExpression(m_mainExpression + buttonText);
            operatorHanging = false;
            break;
        }
        case 7:     //button is equal
        {
            if (operatorCount == 0)
            {
                m_tempResult = m_mainResult.toDouble();
            }

            //process the expression
            if (!operatorHanging) //ensures that if the last button was an operator
            {                     //no math is done as tempResult is already up to date
                performOperation(lastOperator, m_mainResult, m_tempResult);
            }

            if (operatorHanging)
            {
                setPastResult(QString::number(m_tempResult));
                m_mainExpression = m_mainExpression.removeLast(); //These remove the operator
                m_mainExpression = m_mainExpression.removeLast(); //if an operator was pressed
                m_mainExpression = m_mainExpression.removeLast(); //just before equals
                setPastExpression(m_mainExpression);
            }
            else
            {
                if (QString::number(m_tempResult) == "nan" || QString::number(m_tempResult) == "inf")
                {
                    setPastResult("undefined");
                }else setPastResult(QString::number(m_tempResult));
                setPastExpression(m_mainExpression);
            }

            //reset mainResult and main area
            setMainExpression("");
            setMainResult("0");
            operatorCount = 0;
            m_tempResult = 0;
            numInputCount= 0;
            lastOperator = "n/a";
            operatorHanging = false;
            break;
        }
        case 0:     //Error encountered
            break;
    };
}

int LogicHandler::getButtonType(const QString &buttonType)
{
    if (buttonType == "clear")
        return 1;
    else if (buttonType == "back")
        return 2;
    else if (buttonType == "changeSign")
        return 3;
    else if (buttonType == "decimal")
        return 4;
    else if (buttonType == "operator")
        return 5;
    else if (buttonType == "number")
        return 6;
    else if (buttonType == "equal")
        return 7;
    else
        return 0;
}

bool LogicHandler::hasLeadingZero(const QString &checkString)
{
    if (isNegative(checkString))
    {
        //check second character in string for zero
        return checkString.at(1) == '0';
    }
    else if (checkString.contains('.'))
    {
        return false;
    }
    else
    {
        return checkString.at(0) == '0';
    }
}

bool LogicHandler::isNegative(const QString &checkString)
{
    return checkString.front() == '-';
}

bool LogicHandler::containsDecimal(const QString &checkString)
{
    return checkString.contains('.');
}

void LogicHandler::removeLastInput(QString &mainInput)
{
    if (mainInput.length() > 1 && !isNegative(mainInput))
    {
        setMainResult(mainInput.removeLast());
    }
    else if (mainInput.length() > 2 && isNegative(mainInput))
    {
        setMainResult(mainInput.removeLast());
    }
    else
    {
        //keep negative symbol is previous input was negative
        if (isNegative(mainInput))
        {
            setMainResult("-0");
        }
        else setMainResult("0");
    }
}

void LogicHandler::changeSign(QString &mainInput)
{
    if (mainInput.front() == '-')
    {
        setMainResult(mainInput.removeFirst());
        emit mainResultChanged();
    }
    else
    {
        QString tempString = mainInput;
        tempString.push_front('-');
        setMainResult(tempString);
        emit mainResultChanged();
    }
}

void LogicHandler::performOperation(const QString &lastOperator, QString &mainResult, qreal &tempResult)
{
    //find desired operation
    if (lastOperator == "x")
    {
        tempResult = logicMultiply(mainResult, tempResult);
    }
    if (lastOperator == "÷")
    {
        tempResult = logicDivide(mainResult, tempResult);
    }
    if (lastOperator == "+")
    {
        tempResult = logicAdd(mainResult, tempResult);
    }
    if (lastOperator == "-")
    {
        tempResult = logicSubtract(mainResult, tempResult);
    }
    if (lastOperator == "%")
    {
        tempResult = logicRemainder(mainResult, tempResult);
    }
}

qreal LogicHandler::logicAdd(QString &mainResult, qreal &tempResult)
{
    qreal firstValue = tempResult;
    qreal secondValue = mainResult.toDouble();
    return tempResult = firstValue + secondValue;
}

qreal LogicHandler::logicSubtract(QString &mainResult, qreal &tempResult)
{
    qreal firstValue = tempResult;
    qreal secondValue = mainResult.toDouble();
    return tempResult = firstValue - secondValue;
}

qreal LogicHandler::logicDivide(QString &mainResult, qreal &tempResult)
{
    qreal firstValue = tempResult;
    qreal secondValue = mainResult.toDouble();

    return firstValue / secondValue;
}

qreal LogicHandler::logicMultiply(QString &mainResult, qreal &tempResult)
{
    qreal firstValue = tempResult;
    qreal secondValue = mainResult.toDouble();
    return tempResult = firstValue * secondValue;
}

qreal LogicHandler::logicRemainder(QString &mainResult, qreal &tempResult)
{
    qreal firstValue = tempResult;
    qreal secondValue = mainResult.toDouble();
    return tempResult = remainder(firstValue, secondValue);
}
