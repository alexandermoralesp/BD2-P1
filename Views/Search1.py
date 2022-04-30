# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'Search1.ui'
#
# Created by: PyQt5 UI code generator 5.15.4
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


import sys
import os
myDir = os.getcwd()
sys.path.append(myDir)

from PyQt5 import QtCore, QtGui, QtWidgets
from Controllers.Search1_controller import Search1


class Ui_search1(object):
    def __init__(self, table, rep,din_seq):
        
        self.connect = Search1(table,rep,din_seq)
    def setupUi(self, search1):
        search1.setObjectName("search1")
        search1.resize(217, 188)
        self.layoutWidget = QtWidgets.QWidget(search1)
        self.layoutWidget.setGeometry(QtCore.QRect(10, 70, 191, 64))
        self.layoutWidget.setObjectName("layoutWidget")
        self.gridLayout = QtWidgets.QGridLayout(self.layoutWidget)
        self.gridLayout.setContentsMargins(0, 0, 0, 0)
        self.gridLayout.setObjectName("gridLayout")
        self.input_valor = QtWidgets.QLineEdit(self.layoutWidget)
        self.input_valor.setStyleSheet("")
        self.input_valor.setText("")
        self.input_valor.setObjectName("input_valor")
        self.gridLayout.addWidget(self.input_valor, 0, 1, 1, 1)
        self.btn_search = QtWidgets.QPushButton(self.layoutWidget)
        self.btn_search.setObjectName("btn_search")
        self.gridLayout.addWidget(self.btn_search, 1, 0, 1, 2)
        self.btn_valor = QtWidgets.QPushButton(self.layoutWidget)
        self.btn_valor.setObjectName("btn_valor")
        self.gridLayout.addWidget(self.btn_valor, 0, 0, 1, 1)
        self.titulo = QtWidgets.QTextBrowser(search1)
        self.titulo.setGeometry(QtCore.QRect(0, 10, 211, 171))
        self.titulo.setStyleSheet("background: rgba(6,187,176,1)")
        self.titulo.setObjectName("titulo")
        self.titulo.raise_()
        self.layoutWidget.raise_()
#-----------------------------------------------EVENT-----------------------------------------------------------------------#
        self.x = self.btn_search.clicked.connect(lambda: self.connect.search1(self.input_valor.text(), search1))
#---------------------------------------------END_EVENT---------------------------------------------------------------------#

        self.retranslateUi(search1)
        QtCore.QMetaObject.connectSlotsByName(search1)

    def retranslateUi(self, search1):
        _translate = QtCore.QCoreApplication.translate
        search1.setWindowTitle(_translate("search1", "Form"))
        self.input_valor.setPlaceholderText(_translate("search1", "valor"))
        self.btn_search.setText(_translate("search1", "Search"))
        self.btn_valor.setText(_translate("search1", "Valor"))
        self.titulo.setHtml(_translate("search1", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:\'Ubuntu\'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:36pt; font-weight:600;\">UTEC</span></p></body></html>"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    search1 = QtWidgets.QWidget()
    ui = Ui_search1()
    ui.setupUi(search1)
    search1.show()
    sys.exit(app.exec_())
