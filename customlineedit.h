#ifndef CUSTOMLINEEDIT_H
#define CUSTOMLINEEDIT_H

#include <QLineEdit>
#include <QKeyEvent>
class CustomLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    enum Behavior {
        IPLine,
        floatNumLine
    };

    CustomLineEdit(QWidget* parent = nullptr, Behavior mode = IPLine);
    void changeBehaviaur(Behavior mode);

private:

    Behavior mode;
    bool lastIsDot = true;
    int lastDotIndex = -1;

    void behaviorChanger();

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // CUSTOMLINEEDIT_H
