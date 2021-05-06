from PySide2.QtUiTools import *
from PySide2.QtWidgets import *
from PySide2.QtGui import *
from PySide2.QtCore import *
import cv2
import sys
import subprocess
from ui_main1 import Ui_MainWindow

class Main():
    def __init__(self):
        self.ui = Ui_MainWindow()
        # self.ui =QUiLoader().load('main.ui')
        desktop = QApplication.desktop()
        self.ui.setGeometry(0,0,desktop.width()*0.8,desktop.height()*0.8)
        size = self.ui.geometry()
        self.ui.move((desktop.width() - size.width()) / 2,
                  (desktop.height() - size.height()) / 2)
        self.stack1 = QUiLoader().load('one.ui')
        self.stack2 = QUiLoader().load('two.ui')
        self.stack3 = QUiLoader().load('three.ui')
        self.ui.stack.addWidget(self.stack1)
        self.ui.stack.addWidget(self.stack2)
        self.ui.stack.addWidget(self.stack3)
        self.ui.stack.setCurrentIndex(2+1)
        self.ui.button.clicked.connect(self.handle)
        self.ui.button1.clicked.connect(self.handle1)
        self.ui.button2.clicked.connect(self.handle2)
        self.ui.button3.clicked.connect(self.handle3)

        self.ui.min.clicked.connect(self.on_pushButton_min_clicked)
        self.ui.close1.clicked.connect(self.on_pushButton_close_clicked)
        self.ui.max.clicked.connect(self.on_pushButton_max_clicked)

        self.stack1_1 = QUiLoader().load('one(1).ui')
        self.stack1_2 = QUiLoader().load('one(2).ui')
        self.stack1.stack.addWidget(self.stack1_1)
        self.stack1.stack.addWidget(self.stack1_2)
        self.stack1.stack.setCurrentIndex(2+1)
        self.stack1.fanhui.clicked.connect(self.handle4)
        self.stack1.qianjin.clicked.connect(self.handle5)
        self.label1 = QLabel(self.stack1_2.scrollAreaWidgetContents)
        self.label2 = QLabel(self.stack1_2.scrollAreaWidgetContents)
        self.label3 = QLabel(self.stack1_2.scrollAreaWidgetContents)
        self.list=[]
        self.h=-150
        self.h0=0

        for i in range(0,23):
             self.list.append(i)
             self.list[i]=QPushButton(self.stack1_1.scrollAreaWidgetContents)
             if i<9:
                 num='0'+str(i+1)
             else :
                 num=str(i+1)
             path = './imgs/' + num + '.jpg'
             w=300
             h=300
             self.list[i].resize(w, h)
             w1=20 + i % 3 * 450
             h1=self.h+150
             self.list[i].move(w1, h1)
             self.list[i].setStyleSheet("QPushButton{border-image: url("+path+")}")
             self.clicked_connect(i)
             self.h0=max(h1+h,self.h0)
             if (i+1)%3==0:
                 self.h=self.h0
                 self.h0=0

        self.handle7()
        self.ok=0
    def on_pushButton_max_clicked(self):
            if self.ui.isMaximized():
                self.ui.showNormal()
            else:
                self.ui.showMaximized()

    def on_pushButton_min_clicked(self):
        self.ui.showMinimized()

    def on_pushButton_close_clicked(self):
        self.ui.close()

    def clicked_connect(self, i):
        self.list[i].clicked.connect(lambda: self.handle6(i))

    def handle(self):
        self.ok = 1
        self.ui.button.setEnabled(0)
        self.stack1_1.scrollArea.verticalScrollBar().setValue(0)
        self.stack1.stack.setCurrentIndex(2 + 1)
        self.ui.stack.setCurrentIndex(2 + 1)

        main = "ClassNet.exe"
        a = subprocess.getstatusoutput(main)  # 我这边使用subprocess.getstatusoutput()方法，还是不能直接调用执行exe文件
        print(a)

        pre_path="result1"
        list=[]
        self.h=-150
        self.h0=0
        for i in range(0,23):
             list.append(i)
             list[i]=QLabel(self.stack2.scrollAreaWidgetContents)
             path = './'+pre_path+'/' + str(i) + '_matting.jpg'
             w=300
             h=300
             list[i].resize(w, h)
             w1=20 + i % 3 * 450
             h1=self.h+150
             list[i].move(w1, h1)
             list[i].setPixmap(QPixmap(path))
             list[i].setScaledContents(1)
             self.h0=max(h1+h,self.h0)
             if (i + 1) % 3 == 0:
                 self.h = self.h0
                 self.h0 = 0

        pre_path = "result2"
        self.h=-150
        self.h0=0
        for i in range(0,23):
             list[i]=QLabel(self.stack3.scrollAreaWidgetContents)
             path = './'+pre_path+'/' + str(i) + '_matting.jpg'
             w=300
             h=300
             list[i].resize(w, h)
             w1=20 + i % 3 *450
             h1=self.h+150
             list[i].move(w1, h1)
             list[i].setPixmap(QPixmap(path))
             list[i].setScaledContents(1)
             self.h0 = max(h1 + h, self.h0)
             if (i + 1) % 3 == 0:
                 self.h = self.h0
                 self.h0 = 0

        mesBox = QMessageBox()
        mesBox.setWindowTitle('结果')
        mesBox.setText('算法运行成功！')
        mesBox.setIcon(QMessageBox.Information)
        mesBox.setStandardButtons(QMessageBox.Ok)
        mesBox.setStyleSheet('''
                   QLabel{
                   font-family:微软雅黑;
                   font-size:30px;
                   color: rgb(0, 0, 0);
               }
               QPushButton{
                    background-color:rgb(0, 170, 255);
                    border-style:outset;
                    border-width:4px;
                    border-radius:10px;
                    border-color:rgb(85, 170, 127);
                    font:bold 25px;
                    color:rgba(0,0,0,100);
                    padding:6px;
               }
               QPushButton:pressed{
                   background-color:rgb(0, 170, 255);
                   border-color:rgba(255,255,255,30);
                   border-style:inset;
                   color:rgba(0,0,0,100);
               }
               QPushButton:hover{
                   background-color:rgba(100,255,100,100);
                   border-color:rgba(255,255,255,200);
                   color:rgba(0,0,0,200);
               }''')
        mesBox.setWindowFlag(Qt.FramelessWindowHint)
        mesBox.setWindowOpacity(1.0)  # 设置窗口透明度
        mesBox.show()
        mesBox.exec_()

    def handle1(self):
        self.stack1.stack.setCurrentIndex(2 + 1)
        self.ui.stack.setCurrentIndex(2 + 1)

    def handle2(self):
        self.ui.stack.setCurrentIndex(2 + 2)

    def handle3(self):
        self.ui.stack.setCurrentIndex(2 + 3)

    def handle4(self):
        self.stack1.stack.setCurrentIndex(2 + 1)

    def handle5(self):
        self.stack1.stack.setCurrentIndex(2 + 2)

    def handle6(self,i):
        if i < 9:
            num = '0' + str(i + 1)
        else:
            num = str(i + 1)
        path1 = './imgs/' + num + '.jpg'
        path2='./result1/'+str(i)+'_matting.jpg'
        path3='./result2/'+str(i)+'_matting.jpg'
        w=300
        h=300
        w1=100
        h1 = (self.ui.stack.height() - h) / 2 - 50
        self.label1.move(10, h1)
        self.label1.resize(w,h)
        self.label2.move(w+w1, h1)
        self.label2.resize(w,h)
        self.label3.move(w*2+w1*2, h1)
        self.label3.resize(w,h)
        self.label1.setPixmap(QPixmap(path1))

        if self.ok==1:
            self.label2.setPixmap(QPixmap(path2))
        if self.ok == 1:
           self.label3.setPixmap(QPixmap(path3))

        self.label1.setScaledContents(1)
        self.label2.setScaledContents(1)
        self.label3.setScaledContents(1)
        self.stack1_2.scrollArea.horizontalScrollBar().setValue(0)
        self.stack1.stack.setCurrentIndex(2 + 2)

    def handle7(self):
        self.ui.min.setFixedSize(23, 23)
        self.ui.max.setFixedSize(23, 23)
        self.ui.close1.setFixedSize(23, 23)
        self.ui.close1.setStyleSheet(
            '''QPushButton{background:#F76677;border-radius:5px;}QPushButton:hover{background:red;}''')
        self.ui.max.setStyleSheet(
            '''QPushButton{background:#F7D674;border-radius:5px;}QPushButton:hover{background:yellow;}''')
        self.ui.min.setStyleSheet(
            '''QPushButton{background:#6DDF6D;border-radius:5px;}QPushButton:hover{background:green;}''')

        self.ui.setWindowFlag(Qt.FramelessWindowHint)
        self.ui.setWindowOpacity(0.9)  # 设置窗口透明度
        self.ui.setAttribute(Qt.WA_TranslucentBackground)  # 设置窗口背景透明
        self.ui.horizontalLayout.setSpacing(0)

        self.stack1_2.scrollArea.horizontalScrollBar().setStyleSheet("QScrollBar:horizontal{"
                                             "background:#FFFFFF;"
                                             "padding-top:3px;"
                                             "padd  ing-bottom:3px;"
                                             "padding-left:20px;"
                                             "padding-right:20px;}"
                                             "QScrollBar::handle:horizontal{"
                                             "background:#dbdbdb;"
                                             "border-radius:6px;"
                                             "min-width:80px;}"
                                             "QScrollBar::handle:horizontal:hover{"
                                             "background:#d0d0d0;}"
                                             "QScrollBar::add-line:horizontal{"
                                             "background:url(:/images/right.png) center no-repeat;}"
                                             "QScrollBar::sub-line:horizontal{"
                                             "background:url(:/images/left.png) center no-repeat;}");

        self.stack1.setStyleSheet('''
                QPushButton#fanhui{border-image:url(返回1.png);}
                QPushButton#qianjin{border-image:url(前进1.png);}
                QPushButton#fanhui:hover{border-right:2px solid red;font-weight:700;}
                QPushButton#qianjin:hover{border-left:2px solid red;font-weight:700;}'''
              )
        self.stack1.fanhui.setFixedSize(23, 23)
        self.stack1.qianjin.setFixedSize(23, 23)


if __name__ == '__main__':
    app = QApplication(sys.argv)
    main = Main()
    main.ui.activateWindow()
    main.ui.setWindowState(main.ui.windowState() & Qt.WindowMinimized | Qt.WindowActive)
    main.ui.showNormal()
    sys.exit(app.exec_())