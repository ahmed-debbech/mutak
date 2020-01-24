#include "listitem.h"

listItem :: listItem(Track & v){

    QHBoxLayout *main_layout = new QHBoxLayout();
    QVBoxLayout *m_ver1= new QVBoxLayout();
    QVBoxLayout* m_ver2 = new QVBoxLayout();
    QLabel *m_photo = new QLabel();
    QLabel *m_name = new QLabel();
    QLabel *m_artist = new QLabel();
    QLabel *m_duration = new QLabel();
    QLabel *m_played = new QLabel();
    QWidget *m_item= new QWidget();
    m_photo->setText("hola!");
       m_name->setText("yo");
       m_artist->setText("hey");
       m_duration->setText("lopi");
       m_played->setText("loer");
       main_layout->addWidget(m_photo);
       m_ver1->addWidget(m_name);
       m_ver1->addWidget(m_artist);
       main_layout->addLayout(m_ver1);
       m_ver2->addWidget(m_duration);
       m_ver2->addWidget(m_played);
       main_layout->addLayout(m_ver2);
       m_item->setLayout(main_layout);
}
listItem :: ~listItem(){
    delete main_layout;
    delete m_ver1;
    delete m_ver2;
    delete m_photo;
    delete m_name;
    delete m_artist;
    delete m_duration;
    delete m_played;
    delete m_item;
}
