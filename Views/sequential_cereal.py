# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'sequential_cereal.ui'
#
# Created by: PyQt5 UI code generator 5.14.1
#
# WARNING! All changes made in this file will be lost!


import sys
import os
myDir = os.getcwd()
sys.path.append(myDir)

from PyQt5 import QtCore, QtGui, QtWidgets
from Controllers.Seq_cereal_controller import Seq_cereal
from Views.Insertar_cereal import Ui_insertar_cereal
from Views.Search1 import Ui_search1
from Views.Search2 import Ui_search2
from Views.Eliminar import Ui_Delete
#from Views.Select_csv import Ui_Form


class Ui_sequential_cereal(object):
    def __init__(self,parent):
        self.parent = parent
        self.connect = Seq_cereal(self,"cereal")
    def setupUi(self, sequential_cereal):
        sequential_cereal.setObjectName("sequential_cereal")
        sequential_cereal.resize(562, 371)
        self.centralwidget = QtWidgets.QWidget(sequential_cereal)
        self.centralwidget.setObjectName("centralwidget")
        self.layoutWidget_2 = QtWidgets.QWidget(self.centralwidget)
        self.layoutWidget_2.setGeometry(QtCore.QRect(10, 100, 116, 241))
        self.layoutWidget_2.setObjectName("layoutWidget_2")
        self.gridLayout_4 = QtWidgets.QGridLayout(self.layoutWidget_2)
        self.gridLayout_4.setContentsMargins(0, 0, 0, 0)
        self.gridLayout_4.setObjectName("gridLayout_4")
        self.btn_insert = QtWidgets.QPushButton(self.layoutWidget_2)
        self.btn_insert.setObjectName("btn_insert")
        self.gridLayout_4.addWidget(self.btn_insert, 0, 0, 1, 1)
        self.btn_back = QtWidgets.QPushButton(self.layoutWidget_2)
        self.btn_back.setObjectName("btn_back")
        self.gridLayout_4.addWidget(self.btn_back, 4, 0, 1, 1)
        self.btn_delete = QtWidgets.QPushButton(self.layoutWidget_2)
        self.btn_delete.setObjectName("btn_delete")
        self.gridLayout_4.addWidget(self.btn_delete, 3, 0, 1, 1)
        self.btn_search1 = QtWidgets.QPushButton(self.layoutWidget_2)
        self.btn_search1.setObjectName("btn_search1")
        self.gridLayout_4.addWidget(self.btn_search1, 1, 0, 1, 1)
        self.btn_search2 = QtWidgets.QPushButton(self.layoutWidget_2)
        self.btn_search2.setObjectName("btn_search2")
        self.gridLayout_4.addWidget(self.btn_search2, 2, 0, 1, 1)
        self.textBrowser = QtWidgets.QTextBrowser(self.centralwidget)
        self.textBrowser.setGeometry(QtCore.QRect(0, 10, 141, 341))
        self.textBrowser.setStyleSheet("background: rgba(6,187,176,1)")
        self.textBrowser.setOverwriteMode(False)
        self.textBrowser.setObjectName("textBrowser")
        self.titulo = QtWidgets.QTextBrowser(self.centralwidget)
        self.titulo.setGeometry(QtCore.QRect(140, 10, 411, 81))
        self.titulo.setObjectName("titulo")
        self.table = QtWidgets.QTableWidget(self.centralwidget)
        self.table.setGeometry(QtCore.QRect(150, 100, 401, 251))
        self.table.setObjectName("table")
        self.table.setColumnCount(16)
        self.table.setRowCount(0)
        item = QtWidgets.QTableWidgetItem()
        self.table.setHorizontalHeaderItem(0, item)
        item = QtWidgets.QTableWidgetItem()
        self.table.setHorizontalHeaderItem(1, item)
        item = QtWidgets.QTableWidgetItem()
        self.table.setHorizontalHeaderItem(2, item)
        item = QtWidgets.QTableWidgetItem()
        self.table.setHorizontalHeaderItem(3, item)
        item = QtWidgets.QTableWidgetItem()
        self.table.setHorizontalHeaderItem(4, item)
        item = QtWidgets.QTableWidgetItem()
        self.table.setHorizontalHeaderItem(5, item)
        item = QtWidgets.QTableWidgetItem()
        self.table.setHorizontalHeaderItem(6, item)
        item = QtWidgets.QTableWidgetItem()
        self.table.setHorizontalHeaderItem(7, item)
        item = QtWidgets.QTableWidgetItem()
        self.table.setHorizontalHeaderItem(8, item)
        item = QtWidgets.QTableWidgetItem()
        self.table.setHorizontalHeaderItem(9, item)
        item = QtWidgets.QTableWidgetItem()
        self.table.setHorizontalHeaderItem(10, item)
        item = QtWidgets.QTableWidgetItem()
        self.table.setHorizontalHeaderItem(11, item)
        item = QtWidgets.QTableWidgetItem()
        self.table.setHorizontalHeaderItem(12, item)
        item = QtWidgets.QTableWidgetItem()
        self.table.setHorizontalHeaderItem(13, item)
        item = QtWidgets.QTableWidgetItem()
        self.table.setHorizontalHeaderItem(14, item)
        item = QtWidgets.QTableWidgetItem()
        self.table.setHorizontalHeaderItem(15, item)
        self.textBrowser.raise_()
        self.layoutWidget_2.raise_()
        self.titulo.raise_()
        self.table.raise_()
        sequential_cereal.setCentralWidget(self.centralwidget)
        self.statusbar = QtWidgets.QStatusBar(sequential_cereal)
        self.statusbar.setObjectName("statusbar")
        sequential_cereal.setStatusBar(self.statusbar)
#-------------------------------------------------EVENT---------------------------------------------------------------------------------------------#
        self.x = self.btn_insert.clicked.connect(lambda:self.connect.call_insert(Ui_insertar_cereal))
        self.x = self.btn_search1.clicked.connect(lambda:self.connect.call_search1(self,Ui_search1))
        self.x = self.btn_search2.clicked.connect(lambda:self.connect.call_search2(self,Ui_search2))
        self.x = self.btn_delete.clicked.connect(lambda:self.connect.call_eliminar(Ui_Delete))
        self.x = self.btn_back.clicked.connect(lambda:self.connect.call_back(self.parent, sequential_cereal))
        self.retranslateUi(sequential_cereal)
        QtCore.QMetaObject.connectSlotsByName(sequential_cereal)
#-------------------------------------------------EVENT---------------------------------------------------------------------------------------------#
        self.retranslateUi(sequential_cereal)
        QtCore.QMetaObject.connectSlotsByName(sequential_cereal)

    def retranslateUi(self, sequential_cereal):
        _translate = QtCore.QCoreApplication.translate
        sequential_cereal.setWindowTitle(_translate("sequential_cereal", "MainWindow"))
        self.btn_insert.setText(_translate("sequential_cereal", "Insert"))
        self.btn_back.setText(_translate("sequential_cereal", "Back"))
        self.btn_delete.setText(_translate("sequential_cereal", "Delete"))
        self.btn_search1.setText(_translate("sequential_cereal", "Search value"))
        self.btn_search2.setText(_translate("sequential_cereal", "Search by range"))
        self.textBrowser.setHtml(_translate("sequential_cereal", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:\'Ubuntu\'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:28pt;\">UTEC</span></p></body></html>"))
        self.titulo.setHtml(_translate("sequential_cereal", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:\'Ubuntu\'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:20pt; font-weight:600; font-style:italic; text-decoration: underline;\">PROYECTO BASE DE DATOS 2</span></p></body></html>"))
        item = self.table.horizontalHeaderItem(0)
        item.setText(_translate("sequential_cereal", "Nombre"))
        item = self.table.horizontalHeaderItem(1)
        item.setText(_translate("sequential_cereal", "Manufacturer"))
        item = self.table.horizontalHeaderItem(2)
        item.setText(_translate("sequential_cereal", "Tipo"))
        item = self.table.horizontalHeaderItem(3)
        item.setText(_translate("sequential_cereal", "Calorias"))
        item = self.table.horizontalHeaderItem(4)
        item.setText(_translate("sequential_cereal", "Proteinas"))
        item = self.table.horizontalHeaderItem(5)
        item.setText(_translate("sequential_cereal", "Grasa"))
        item = self.table.horizontalHeaderItem(6)
        item.setText(_translate("sequential_cereal", "Sodio"))
        item = self.table.horizontalHeaderItem(7)
        item.setText(_translate("sequential_cereal", "Fibra"))
        item = self.table.horizontalHeaderItem(8)
        item.setText(_translate("sequential_cereal", "Carbohidratos"))
        item = self.table.horizontalHeaderItem(9)
        item.setText(_translate("sequential_cereal", "Azucares"))
        item = self.table.horizontalHeaderItem(10)
        item.setText(_translate("sequential_cereal", "Potasio"))
        item = self.table.horizontalHeaderItem(11)
        item.setText(_translate("sequential_cereal", "Vitaminas"))
        item = self.table.horizontalHeaderItem(12)
        item.setText(_translate("sequential_cereal", "Disp. estanteria"))
        item = self.table.horizontalHeaderItem(13)
        item.setText(_translate("sequential_cereal", "Peso"))
        item = self.table.horizontalHeaderItem(14)
        item.setText(_translate("sequential_cereal", "Tazas/porcion"))
        item = self.table.horizontalHeaderItem(15)
        item.setText(_translate("sequential_cereal", "Rating"))

if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    sequential_cereal = QtWidgets.QMainWindow()
    ui = Ui_sequential_cereal()
    ui.setupUi(sequential_cereal)
    sequential_cereal.show()
    sys.exit(app.exec_())
