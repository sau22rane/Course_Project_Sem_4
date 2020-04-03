#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <backend.h>
#include <QPixmap>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

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
        QStringList titles;
        ui->tableWidget->setColumnCount(8);
        titles<<"Sr No."<<"Flight No."<<"Airline"<<"From"<<"To"<<"Date"<<"Time"<<"Price";
        ui->tableWidget->setHorizontalHeaderLabels(titles);
        while (ui->tableWidget->rowCount()>0)
            ui->tableWidget->removeRow(0);
        struct LinkedListNode *temp;
        temp=head;
        while(temp->next!=NULL)
        {
            QString Index(temp->index);
            ui->statusbar->showMessage(Index);
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem("1"));
            QString FN(temp->ptr->flight_number);
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(FN));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,new QTableWidgetItem(temp->ptr->flight_name));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,3,new QTableWidgetItem(temp->ptr->from));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,4,new QTableWidgetItem(temp->ptr->dst));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,5,new QTableWidgetItem(temp->ptr->date));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,6,new QTableWidgetItem(temp->ptr->time));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,7,new QTableWidgetItem(temp->ptr->price));
            temp=temp->next;
        }
        QString Index(temp->index);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(Index));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(temp->ptr->flight_number));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,new QTableWidgetItem(temp->ptr->flight_name));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,3,new QTableWidgetItem(temp->ptr->from));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,4,new QTableWidgetItem(temp->ptr->dst));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,5,new QTableWidgetItem(temp->ptr->date));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,6,new QTableWidgetItem(temp->ptr->time));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,7,new QTableWidgetItem(temp->ptr->price));
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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Airline Reservation System");
    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_Search_Flights_2_clicked()
{
    Node *root=NULL;
    QFile file("C:/Users/Pro1501/Desktop/DS Course Project/flight data.txt");
    if(!file.open(QIODevice::ReadOnly))
        QMessageBox::information(0,"Info",file.errorString());

    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList A = line.split(" ");

        QString Fno = A[0];
        QByteArray ba = Fno.toLatin1();
        char *fno=ba.data();
        int ifno=atoi(fno);

        QString Fname = A[1];
        ba = Fname.toLatin1();
        char *fname=ba.data();

        QString Fr = A[2];
        ba = Fr.toLatin1();
        char *fr=ba.data();

        QString To = A[3];
        ba = To.toLatin1();
        char *to=ba.data();

        QString Fdate = A[4];
        ba = Fdate.toLatin1();
        char *fdate=ba.data();

        QString Ftime = A[5];
        ba = Ftime.toLatin1();
        char *ftime=ba.data();

        QString Fprice = A[6];
        ba = Fprice.toLatin1();
        char *fprice=ba.data();
        int ifprice=atoi(fprice);

        root = insert(root, ifno, fdate, fr, to, fname, ftime, ifprice);
    }
    file.close();

    QString From = ui->lineEdit_From_2->text();
    QByteArray ba = From.toLatin1();
    char *from=ba.data();
    QString To = ui->lineEdit_To_2->text();
    ba = To.toLatin1();
    char *to=ba.data();
    QString Date = ui->lineEdit_Date_2->text();
    ba = Date.toLatin1();
    char *date=ba.data();

    search(root, date, from, to);
    int no = display(head);
    if (no==0)
        ui->statusbar->showMessage("No Flights Available",3000);
}

void MainWindow::on_pushButton_Exit_clicked()
{
    MainWindow::close();
}

void MainWindow::on_pushButton_Exit_3_clicked()
{
    MainWindow::close();
}

void MainWindow::on_pushButton_Book_a_Flight_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_Back_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
