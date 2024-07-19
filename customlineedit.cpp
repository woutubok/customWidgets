#include "customlineedit.h"


CustomLineEdit::CustomLineEdit(QWidget* parent, Behavior mode) : QLineEdit(parent), mode{mode}
{
    behaviorChanger();
}

void CustomLineEdit::changeBehaviaur(Behavior mode)
{
    if(this->mode == mode){
        return;
    }
    else{
        disconnect(this);
        this->mode = mode;
        behaviorChanger();
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
                lastIsDot = false;
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
            if(lastIsDot || text().isEmpty()){
                event->ignore();
            }
            else if(!text().isEmpty() && lastDotIndex == text().length() - 1){
                qDebug() << "ddddd";
                event->ignore();
            }
            else{
                QLineEdit::keyPressEvent(event);
                lastIsDot = true;
            }
        }
        else if(event->key() >= Qt::Key_0 && event->key() <= Qt::Key_9){
            QLineEdit::keyPressEvent(event);
            lastIsDot = false;
        }
        else if(event->key() == Qt::Key_Backspace){
            if(lastIsDot)
                lastIsDot = false;
            QLineEdit::keyPressEvent(event);
        }
        lastDotIndex = text().lastIndexOf(".");
        break;

    case floatNumLine:
        if(event->key() == Qt::Key_Period){
            if(lastDotIndex != -1 || text().isEmpty()){
                event->ignore();
            }
            else{
                QLineEdit::keyPressEvent(event);
                //lastIsDot = true;
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
        break;

    default:
        qDebug() << "[CustomLineEdit] keyPressEvent unknown type";
        break;
    }
}

void CustomLineEdit::mousePressEvent(QMouseEvent *event)
{
    if(mode == floatNumLine)
        QLineEdit::mousePressEvent(event);
    else{
        event->ignore();
    }
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
