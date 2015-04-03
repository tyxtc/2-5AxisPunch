#ifndef ICPROGRAMPAGE_H
#define ICPROGRAMPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <iccheckedbutton.h>
#include <QTableWidgetItem>
#include <virtualnumerickeypaddialog.h>
#include "icvirtualhost.h"


#define MAX_POINTS 5
#define AXIS_COUNTS 5
#define COLUMN_COUNTS (AXIS_COUNTS + 4)
#define RESERVE_COUNTS (MAX_POINTS - 3)

namespace Ui {
class ICProgramPage;
}

#define _MoldParam(addr) ICMold::CurrentMold()->MoldParam(static_cast<ICMold::ICMoldParam>(addr))

typedef struct{
   qint16 x;
   qint16 y;
   qint16 s;
   qint16 r;
   qint16 t;
} ICPoint_;

typedef QSharedPointer<ICPoint_>  PointPtr;
typedef QSharedPointer<ICMoldItem>  MoldItemPtr;


class ICProgramPage : public QWidget
{
    Q_OBJECT

public:
    explicit ICProgramPage(QWidget *parent = 0,int pageIndex = 0);
    void setItemNames(QStringList & contents);
    QList<PointPtr> GT_Points();
    QList<ICMoldItem> GT_Items();
    QList<ICMoldItem> GT_Pos(int pos);


    PointPtr MK_Point(qint16 x,qint16 y,qint16 s,qint16 r,qint16 t);
    ICMoldItem MK_MoldItem(uint seq,
                            uint num,
                            uint8_t subNum,
                            uint gmVal,
                            uint pos,
                            uint ifVal,
                            uint ifPos,
                            uint sVal,
                            uint dVal,
                            uint sum);

    void InitFixMoldItems();
    ~ICProgramPage();

protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);
    
signals:
    void returnProgram();

private slots:
    void itemClicked(QTableWidgetItem*);
    void saveButtonsCliked();
    void testButonsClicked();
    void usedButtonsClicked(bool);

    void on_pushButton_clicked();


private:
    void InitTableWidget();
    void InitPoints();

private:
    Ui::ICProgramPage *ui;
    VirtualNumericKeypadDialog *_dialog;
    QList<QPushButton*> saveButtons;
    QList<QPushButton*> testButtons;
    QList<ICCheckedButton*> reserveButtons;
    QList<int> reserveIndexs;

    ICVirtualHost *_host;
    int _index;
    QList<PointPtr> allPoints;
    QList<ICMoldItem> allItems;


    ICMoldItem waitM10;
    ICMoldItem outY37On;
    ICMoldItem outM11;
    ICMoldItem waitM12;
    ICMoldItem outY37Off;
    ICMoldItem outY31On;
    ICMoldItem outY31Off;
    ICMoldItem waitM14;
    ICMoldItem outPermit;


};

#endif // ICPROGRAMPAGE_H
