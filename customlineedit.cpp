#include "customlineedit.h"
#include <QRegularExpression>

QRegularExpression reg("\\.+");

CustomLineEdit::CustomLineEdit(QWidget* parent, Behavior mode) : QLineEdit(parent), mode{mode}
{
    // behaviorChanger();

    connect(this, &QLineEdit::editingFinished, [this]{
        QString input = text();
        QString replacement('.');

        input.replace(reg, replacement);
        this->setText(input);

        if(!text().isEmpty() && text().first(1) == "."){
            this->setText("0" + text());
            lastDotIndex = text().lastIndexOf(".");
        }

        if(!text().isEmpty() && text().last(1) == "."){
            this->setText(text().removeLast());
            lastDotIndex = text().lastIndexOf(".");
        }
    });
}

void CustomLineEdit::changeBehaviaur(Behavior mode)
{
    if(this->mode == mode){
        return;
    }
    else{
        //disconnect(this);
        this->mode = mode;
        //behaviorChanger();
    }
}

void CustomLineEdit::behaviorChanger()
{
    switch (mode) {
    case IPLine:
        connect(this, &QLineEdit::editingFinished, [this]{
            if(!text().isEmpty() && text().last(1) == "."){
                this->setText(text().removeLast());
                lastDotIndex = text().lastIndexOf(".");
            }
        });
        break;
    case floatNumLine:
        connect(this, &QLineEdit::editingFinished, [this]{
            if(!text().isEmpty() && text().first(1) == "."){
                this->setText("0" + text());
                lastDotIndex = text().lastIndexOf(".");
            }
        });
    default:
        break;
    }
}

void CustomLineEdit::keyPressEvent(QKeyEvent *event)
{
    switch (mode) {
    case IPLine:
        if(event->key() == Qt::Key_Period){
            qDebug() << "inside" << cursorPosition();
            if(text().isEmpty()){
                event->ignore();
            }
            else if(cursorPosition() == 0 && text().at(0) != '.'){
                qDebug() << "[Key_Period] 1 else if";
                QLineEdit::keyPressEvent(event);
            }
            else if((cursorPosition() == text().length()) && text().at(cursorPosition() - 1) != '.'){
                qDebug() << "[Key_Period] 2 else if";
                QLineEdit::keyPressEvent(event);
            }
            else if((text().length() > 0 && text().at((cursorPosition() - 1)) != '.')
                      && ((text().length() > 1 && text().length() != cursorPosition()) && text().at(cursorPosition()) != '.')){
                qDebug() << "[Key_Period] 3 else if";
                qDebug() << "cursorPos 3" << cursorPosition();
                //qDebug() << "lastDotindex" << lastDotIndex << "text lenght" << text().length();
                QLineEdit::keyPressEvent(event);
            }
            else{
                qDebug() << "ignore";
                event->ignore();
            }
        }
        else if(event->key() >= Qt::Key_0 && event->key() <= Qt::Key_9){
            QLineEdit::keyPressEvent(event);
        }
        else if(event->key() == Qt::Key_Backspace){
            QLineEdit::keyPressEvent(event);
        }
        else if(event->key() == Qt::Key_Up || event->key() == Qt::Key_Down || event->key() == Qt::Key_Left || event->key() == Qt::Key_Right){
            QLineEdit::keyPressEvent(event);
        }
        break;

    case floatNumLine:
        if(event->key() == Qt::Key_Period){
            if(lastDotIndex != -1 || text().isEmpty()){
                event->ignore();
            }
            else{
                QLineEdit::keyPressEvent(event);
            }
        }
        else if(event->key() >= Qt::Key_0 && event->key() <= Qt::Key_9){
            QLineEdit::keyPressEvent(event);
        }
        else if(event->key() == Qt::Key_Backspace){
            QLineEdit::keyPressEvent(event);
        }
        else if(event->key() == Qt::Key_Up || event->key() == Qt::Key_Down || event->key() == Qt::Key_Left || event->key() == Qt::Key_Right){
            QLineEdit::keyPressEvent(event);
        }
        lastDotIndex = text().lastIndexOf(".");
        qDebug() << "cursorPos" << cursorPosition();
        break;

    default:
        qDebug() << "[CustomLineEdit] keyPressEvent unknown type";
        break;
    }
}

void CustomLineEdit::mousePressEvent(QMouseEvent *event)
{
    //if(mode == floatNumLine)
    //    QLineEdit::mousePressEvent(event);
   // else{
        //event->ignore();
   // }
    QLineEdit::mousePressEvent(event);
}

void CustomLineEdit::mouseReleaseEvent(QMouseEvent *event)
{
    event->ignore();
}

void CustomLineEdit::mouseDoubleClickEvent(QMouseEvent *event){
    event->ignore();
}
void CustomLineEdit::mouseMoveEvent(QMouseEvent *event){
    event->ignore();
}
