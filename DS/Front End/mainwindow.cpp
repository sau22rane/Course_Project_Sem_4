#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <backend.h>
#include <QPixmap>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

int ino,i,indx,c=0,c1=0,e=0,p=0,j=1;
char flightticket[] = "Flight Ticket.txt";
char confirm[] = "confirm.txt";
char flightdata[] = "Flight data.txt";

Node* newNode(int key, char a[],char b[],char c[], char d[], char e[], int f)
{
    Node* node = (Node*) malloc(sizeof(Node));
    node->flight_number  = key;
    node->price = f;
    strcpy(node->date,a);
    strcpy(node->from,b);
    strcpy(node->dst,c);
    strcpy(node->flight_name,d);
    strcpy(node->time,e);
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;

    return(node);
}

int MainWindow::display(struct LinkedListNode* head)
{
    if(head==NULL)
        return 0;
    else
    {
        ui->stackedWidget->setCurrentIndex(1);
        while (ui->tableWidget->rowCount()>0)
            ui->tableWidget->removeRow(0);
        struct LinkedListNode *temp;
        temp=head;
        while(temp->next!=NULL)
        {
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            QString Fn = QString::number(temp->ptr->flight_number);
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(Fn));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(temp->ptr->flight_name));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,new QTableWidgetItem(temp->ptr->from));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,3,new QTableWidgetItem(temp->ptr->dst));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,4,new QTableWidgetItem(temp->ptr->date));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,5,new QTableWidgetItem(temp->ptr->time));
            QString Price = QString::number(temp->ptr->price);
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,6,new QTableWidgetItem(Price));
            temp=temp->next;
        }
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        QString Fn = QString::number(temp->ptr->flight_number);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(Fn));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(temp->ptr->flight_name));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,new QTableWidgetItem(temp->ptr->from));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,3,new QTableWidgetItem(temp->ptr->dst));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,4,new QTableWidgetItem(temp->ptr->date));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,5,new QTableWidgetItem(temp->ptr->time));
        QString Price = QString::number(temp->ptr->price);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,6,new QTableWidgetItem(Price));
        return 1;
    }
}

void add(Node* root)
{
    if(head == NULL)
    {
        head = (LinkedListNode*) malloc(sizeof(LinkedListNode));
        head->ptr = root;
        head->next = NULL;
        head->index = 1;
    }
    else
    {
        LinkedListNode *temp, *n;
        n = (LinkedListNode*) malloc(sizeof(LinkedListNode));
        n -> ptr = root;
        n -> next = NULL;
        temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        n->index = (temp->index)+1;
        temp->next = n;
    }
}

void search(Node *root, char a[], char b[], char c[])
{
    if(root != NULL)
    {
        if(strcmp(root->date,a)==0 && strcmp(root->from,b)==0 && strcmp(root->dst,c)==0)
        {
            add(root);
        }
        search(root->left,a,b,c);
        search(root->right,a,b,c);
    }
}

int height(Node *N)
{
    if (N == NULL)
        return 0;

    return N->height;
}

int max(int a, int b)
{
    return (a > b)? a : b;
}

Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *temp = x->right;

    x->right = y;
    y->left = temp;

    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    return x;
}

Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *temp = y->left;

    y->left = x;
    x->right = temp;

    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    return y;
}

int getBalance(Node *N)
{
    if (N == NULL)
        return 0;

    return height(N->left) - height(N->right);
}

Node* insert(Node* node, int key, char a[],char b[],char c[], char d[], char e[], int f)
{
    if (node == NULL)
        return(newNode(key,a,b,c,d,e,f));

    if (key < node->flight_number)
        node->left  = insert(node->left, key,a,b,c,d,e,f);
    else if (key > node->flight_number)
        node->right = insert(node->right, key, a,b,c,d,e,f);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && key < node->left->flight_number)
        return rightRotate(node);

    if (balance < -1 && key > node->right->flight_number)
        return leftRotate(node);

    if (balance > 1 && key > node->left->flight_number)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->flight_number)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

void MainWindow::book(struct LinkedListNode* head)
{
    int amount;
    LinkedListNode *temp;
    temp = head;

    while(temp->index != indx)
        temp=temp->next;
    QString Fn = QString::number(temp->ptr->flight_number);
    QString Fprice = QString::number(temp->ptr->price);

    QFile file(flightticket);
    if(!file.open(QIODevice::Append | QIODevice::Text))
        QMessageBox::information(0,"Info",file.errorString());

    QTextStream out(&file);
    out << "Flight Information:-" << endl << "Flight Number: " << Fn << endl << "Airline: " << temp->ptr->flight_name << endl << "From: " << temp->ptr->from << endl << "To: " << temp->ptr->dst << endl << "Date: " << temp->ptr->date << endl << "Departure Time: "<< temp->ptr->time << endl;
    out<<"----------------------------------------------------------------------------------------------------------------------------------";

    amount = ino * temp->ptr->price;
    QString Amount = QString::number(amount);
    ui->plainTextEdit_Total_Amount->setPlainText(Amount);
    ui->statusbar->showMessage("Warning: Do not press EXIT before verification. Press CANCEL to cancel the booking");
    file.close();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Airline Reservation System");
    QPixmap pix("plane.bmp");
    ui->label_planepic->setPixmap(pix);
    QStringList titles;
    ui->tableWidget->setColumnCount(8);
    titles<<"Flight No."<<"Airline"<<"From"<<"To"<<"Date"<<"Time"<<"Price";
    ui->tableWidget->setHorizontalHeaderLabels(titles);
    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_Search_Flights_2_clicked()
{
    e=0;
    ui->statusbar->showMessage("");
    while (ui->tableWidget->rowCount()>0)
        ui->tableWidget->removeRow(0);
    QFile file(flightdata);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        QMessageBox::information(0,"Info",file.errorString());

    QTextStream in(&file);
    Node *root=NULL;
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList A = line.split(" ");

        QString Fno = A[0];
        QByteArray ba = Fno.toLatin1();
        char *fno=ba.data();
        int ifno=atoi(fno);

        QString Fname = A[1];
        QByteArray bb = Fname.toLatin1();
        char *fname=bb.data();

        QString Fr = A[2];
        QByteArray bc = Fr.toLatin1();
        char *fr=bc.data();

        QString To = A[3];
        QByteArray bd = To.toLatin1();
        char *to=bd.data();

        QString Fdate = A[4];
        QByteArray be = Fdate.toLatin1();
        char *fdate=be.data();

        QString Ftime = A[5];
        QByteArray bf = Ftime.toLatin1();
        char *ftime=bf.data();

        QString Fprice = A[6];
        QByteArray bg = Fprice.toLatin1();
        char *fprice=bg.data();
        int ifprice=atoi(fprice);

        root = insert(root, ifno, fdate, fr, to, fname, ftime, ifprice);
    }
    file.close();

    QString From = ui->lineEdit_From_2->text();
    QByteArray bh = From.toLatin1();
    char *from=bh.data();
    QString To = ui->lineEdit_To_2->text();
    QByteArray bi = To.toLatin1();
    char *to=bi.data();
    QString Date = ui->lineEdit_Date_2->text();
    QByteArray bj = Date.toLatin1();
    char *date=bj.data();

    search(root, date, from, to);
    int no = display(head);
    if (From == "" || To == "" || Date == "")
    {
        ui->statusbar->showMessage("Please fill up all details");
        return;
    }
    if (no==0)
        ui->statusbar->showMessage("No Flights Available",3000);
}

void MainWindow::on_pushButton_Exit_clicked()
{
    e+=1;
    ui->statusbar->showMessage("Press EXIT again to confirm");
    if(e==2)
    {
        remove(flightticket);
        remove(confirm);
        MainWindow::close();
    }
}

void MainWindow::on_pushButton_Exit_3_clicked()
{
    e+=1;
    ui->statusbar->showMessage("Press EXIT again to confirm");
    if(e==2)
    {
        remove(flightticket);
        remove(confirm);
        MainWindow::close();
    }
}

void MainWindow::on_pushButton_Book_a_Flight_clicked()
{
    int flag=0;
    i=0;
    e=0;
    c1=0;
    ui->statusbar->showMessage("");
    LinkedListNode *temp;
    temp = head;
    QFile file(flightticket);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        QMessageBox::information(0,"Info",file.errorString());
    QTextStream out(&file);
    out << "";
    file.close();
    QFile file2(confirm);
    if(!file2.open(QIODevice::WriteOnly | QIODevice::Text))
        QMessageBox::information(0,"Info",file2.errorString());
    QTextStream out2(&file2);
    out2 << "";
    file.close();
    QString ind = ui->lineEdit_Index->text();
    QByteArray bh = ind.toLatin1();
    char *Ind=bh.data();
    indx=atoi(Ind);
    while(temp->next != NULL)
    {
        if(temp->index==indx)
        {
            flag=1;
            break;
        }
        else
            temp=temp->next;
    }
    if(flag==1)
        ui->stackedWidget->setCurrentIndex(2);
    else
        ui->statusbar->showMessage("Please enter a valid index",3000);
}

void MainWindow::on_pushButton_Back_clicked()
{
    e=0;
    ui->statusbar->showMessage("");
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_Exit_4_clicked()
{
    e+=1;
    ui->statusbar->showMessage("Press EXIT again to confirm");
    if(e==2)
    {
        remove(flightticket);
        remove(confirm);
        MainWindow::close();
    }
}

void MainWindow::on_pushButton_Back_2_clicked()
{
    e=0;
    ui->statusbar->showMessage("");
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_Confirm_2_clicked()
{
    e=0;
    ui->statusbar->showMessage("");
    if(c1==1)
    {
        ui->statusbar->showMessage("No. of tickets already confirmed. Use BACK to reset");
        return;
    }
    QFile file(flightticket);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        QMessageBox::information(0,"Info",file.errorString());
    QTextStream out(&file);
    out << "";
    file.close();
    QFile file2(confirm);
    if(!file2.open(QIODevice::WriteOnly | QIODevice::Text))
        QMessageBox::information(0,"Info",file2.errorString());
    QTextStream out2(&file2);
    out2 << "";
    QString No = ui->lineEdit_NoT->text();
    QByteArray bh = No.toLatin1();
    char *no=bh.data();
    ino=atoi(no);
    if(ino<=0||No=="")
    {
        ui->statusbar->showMessage("Please enter a valid value");
        return;
    }
    ui->statusbar->showMessage("Confirmed");
    c1=1;
}

void MainWindow::on_pushButton_Confirm_clicked()
{
    e=0;
    ui->statusbar->showMessage("");
    QFile file1(flightticket);
        if(!file1.open(QIODevice::Append | QIODevice::Text))
            QMessageBox::information(0,"Info",file1.errorString());
    QFile file3(confirm);
        if(!file3.open(QIODevice::ReadOnly | QIODevice::Text))
            QMessageBox::information(0,"Info",file3.errorString());

    QTextStream out(&file1);
    QTextStream in(&file3);

    QString text = in.readAll();
    if(text=="")
    {
        ui->statusbar->showMessage("Use NEXT and confirm details",3000);
        return;
    }
    i+=1;
    out << text;
    file1.close();
    file3.close();

    QFile file2(confirm);
    if(!file2.open(QIODevice::WriteOnly | QIODevice::Text))
        QMessageBox::information(0,"Info",file2.errorString());

    QTextStream out2(&file2);
    out2 << "";
    file2.close();

    if (i==ino)
    {
        ui->stackedWidget->setCurrentIndex(3);
        book(head);
    }
}

void MainWindow::on_pushButton_Next_clicked()
{
    e=0;
    ui->statusbar->showMessage("");
    if(c1!=1)
    {
        ui->statusbar->showMessage("Please confirm number of tickets first");
        return;
    }
    QFile file2(confirm);
    if(!file2.open(QIODevice::WriteOnly | QIODevice::Text))
        QMessageBox::information(0,"Info",file2.errorString());
    QTextStream out(&file2);
    QString Name = ui->lineEdit_PName->text();
    QString Age = ui->lineEdit_PAge->text();
    QString Gender = ui->lineEdit_PGender->text();
    QString Mn = ui->lineEdit_PMn->text();
    if(Name == "" || Age == "" || Gender == "" || Mn == "")
    {
        ui->statusbar->showMessage("Please fill up all details",3000);
        return;
    }

    out << "Passenger Details:-" << endl << "Name: " << Name << endl << "Age: " << Age << endl << "Gender: " << Gender << endl << "Mobile Number: " << Mn << endl << endl;
    file2.flush();
    QFile file3(confirm);
    if(!file3.open(QIODevice::ReadOnly | QIODevice::Text))
        QMessageBox::information(0,"Info",file3.errorString());
    QTextStream inf(&file3);
    QString text = inf.readAll();
    ui->plainTextEdit_ConDet->setPlainText(text);
    file2.close();
    file3.close();
}

void MainWindow::on_pushButton_Cancel_clicked()
{
    c+=1;
    e=0;
    ui->statusbar->showMessage("Press CANCEL again to confirm");
    if(p==1)
        ui->statusbar->showMessage("Unavailable after payment. Use EXIT to quit");
    else if(c==2)
    {
        remove(flightticket);
        remove(confirm);
        MainWindow::close();
    }
}

void MainWindow::on_pushButton_Exit_5_clicked()
{
    c=0;
    if(p==1)
        MainWindow::close();
    else
    {
        ui->statusbar->showMessage("Unavailable during payment. Use CANCEL to cancel booking process");
        c=0;
    }
}

void MainWindow::on_pushButton_OTP_clicked()
{
    c=0;
    QString OTP = ui->lineEdit_OTP->text();
    if (OTP == "1234")
    {
        p=1;
        ui->plainTextEdit_status->setPlainText("Ticket Booked Successfully and saved as 'Flight Ticket.txt'. Have a safe journey!");
        ui->statusbar->showMessage("Thank you. Press the EXIT button.");
        remove(confirm);
    }
    else if (OTP != "1234" && j == 3)
    {
        p=1;
        remove(flightticket);
        remove(confirm);
        ui->plainTextEdit_status->setPlainText("Wrong OTP was entered, please try booking again.");
        ui->statusbar->showMessage("Sorry. Press the EXIT button");
    }
    else if(j == 2)
    {
        ui->plainTextEdit_status->setPlainText("Wrong OTP! You have 1 more chance");
        ui->statusbar->showMessage("Wrong OTP",3000);
        j+=1;
    }
    else if(j == 1)
    {
        ui->plainTextEdit_status->setPlainText("Wrong OTP! You have 2 more chances");
        ui->statusbar->showMessage("Wrong OTP",3000);
        j+=1;
    }

}

void MainWindow::on_pushButton_Decline_clicked()
{
    e=0;
    ui->statusbar->showMessage("");
}
