# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'Insertar_cereal.ui'
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
from Controllers.Insertar_cereal_controller import Insertar_cereal


class Ui_insertar_cereal(object):
    def __init__(self,tabla):
        self.connect = Insertar_cereal(tabla)
    def setupUi(self, insertar_cereal):
        insertar_cereal.setObjectName("insertar_cereal")
        insertar_cereal.resize(395, 648)
        self.titulo = QtWidgets.QTextBrowser(insertar_cereal)
        self.titulo.setGeometry(QtCore.QRect(0, 10, 391, 641))
        self.titulo.setStyleSheet("background: rgba(6,187,176,1)")
        self.titulo.setObjectName("titulo")
        self.layoutWidget = QtWidgets.QWidget(insertar_cereal)
        self.layoutWidget.setGeometry(QtCore.QRect(10, 70, 374, 566))
        self.layoutWidget.setObjectName("layoutWidget")
        self.gridLayout = QtWidgets.QGridLayout(self.layoutWidget)
        self.gridLayout.setContentsMargins(0, 0, 0, 0)
        self.gridLayout.setObjectName("gridLayout")
        self.inp_carbohidratos = QtWidgets.QLineEdit(self.layoutWidget)
        self.inp_carbohidratos.setObjectName("inp_carbohidratos")
        self.gridLayout.addWidget(self.inp_carbohidratos, 8, 1, 1, 1)
        self.inp_nombre = QtWidgets.QLineEdit(self.layoutWidget)
        self.inp_nombre.setObjectName("inp_nombre")
        self.gridLayout.addWidget(self.inp_nombre, 0, 1, 1, 1)
        self.inp_sodio = QtWidgets.QLineEdit(self.layoutWidget)
        self.inp_sodio.setObjectName("inp_sodio")
        self.gridLayout.addWidget(self.inp_sodio, 6, 1, 1, 1)
        self.Carbohidratos = QtWidgets.QLabel(self.layoutWidget)
        self.Carbohidratos.setObjectName("Carbohidratos")
        self.gridLayout.addWidget(self.Carbohidratos, 8, 0, 1, 1)
        self.inp_proteinas = QtWidgets.QLineEdit(self.layoutWidget)
        self.inp_proteinas.setObjectName("inp_proteinas")
        self.gridLayout.addWidget(self.inp_proteinas, 4, 1, 1, 1)
        self.inp_fibra = QtWidgets.QLineEdit(self.layoutWidget)
        self.inp_fibra.setObjectName("inp_fibra")
        self.gridLayout.addWidget(self.inp_fibra, 7, 1, 1, 1)
        self.Peso = QtWidgets.QLabel(self.layoutWidget)
        self.Peso.setObjectName("Peso")
        self.gridLayout.addWidget(self.Peso, 13, 0, 1, 1)
        self.Proteinas = QtWidgets.QLabel(self.layoutWidget)
        self.Proteinas.setObjectName("Proteinas")
        self.gridLayout.addWidget(self.Proteinas, 4, 0, 1, 1)
        self.inp_calorias = QtWidgets.QLineEdit(self.layoutWidget)
        self.inp_calorias.setObjectName("inp_calorias")
        self.gridLayout.addWidget(self.inp_calorias, 3, 1, 1, 1)
        self.Potasio = QtWidgets.QLabel(self.layoutWidget)
        self.Potasio.setObjectName("Potasio")
        self.gridLayout.addWidget(self.Potasio, 10, 0, 1, 1)
        self.inp_tipo = QtWidgets.QComboBox(self.layoutWidget)
        self.inp_tipo.setObjectName("inp_tipo")
        self.inp_tipo.addItem("")
        self.inp_tipo.addItem("")
        self.inp_tipo.addItem("")
        self.gridLayout.addWidget(self.inp_tipo, 2, 1, 1, 1)
        self.Nombre = QtWidgets.QLabel(self.layoutWidget)
        self.Nombre.setObjectName("Nombre")
        self.gridLayout.addWidget(self.Nombre, 0, 0, 1, 1)
        self.inp_azucares = QtWidgets.QLineEdit(self.layoutWidget)
        self.inp_azucares.setObjectName("inp_azucares")
        self.gridLayout.addWidget(self.inp_azucares, 9, 1, 1, 1)
        self.Sodio = QtWidgets.QLabel(self.layoutWidget)
        self.Sodio.setObjectName("Sodio")
        self.gridLayout.addWidget(self.Sodio, 6, 0, 1, 1)
        self.Fibra = QtWidgets.QLabel(self.layoutWidget)
        self.Fibra.setObjectName("Fibra")
        self.gridLayout.addWidget(self.Fibra, 7, 0, 1, 1)
        self.Calorias = QtWidgets.QLabel(self.layoutWidget)
        self.Calorias.setObjectName("Calorias")
        self.gridLayout.addWidget(self.Calorias, 3, 0, 1, 1)
        self.Azucares = QtWidgets.QLabel(self.layoutWidget)
        self.Azucares.setObjectName("Azucares")
        self.gridLayout.addWidget(self.Azucares, 9, 0, 1, 1)
        self.Tipo = QtWidgets.QLabel(self.layoutWidget)
        self.Tipo.setObjectName("Tipo")
        self.gridLayout.addWidget(self.Tipo, 2, 0, 1, 1)
        self.inp_moc = QtWidgets.QComboBox(self.layoutWidget)
        self.inp_moc.setObjectName("inp_moc")
        self.inp_moc.addItem("")
        self.inp_moc.addItem("")
        self.inp_moc.addItem("")
        self.inp_moc.addItem("")
        self.inp_moc.addItem("")
        self.inp_moc.addItem("")
        self.inp_moc.addItem("")
        self.inp_moc.addItem("")
        self.gridLayout.addWidget(self.inp_moc, 1, 1, 1, 1)
        self.Disposicion_estante = QtWidgets.QLabel(self.layoutWidget)
        self.Disposicion_estante.setObjectName("Disposicion_estante")
        self.gridLayout.addWidget(self.Disposicion_estante, 12, 0, 1, 1)
        self.btn_insertar = QtWidgets.QPushButton(self.layoutWidget)
        self.btn_insertar.setObjectName("btn_insertar")
        self.gridLayout.addWidget(self.btn_insertar, 16, 0, 1, 2)
        self.inp_grasa = QtWidgets.QLineEdit(self.layoutWidget)
        self.inp_grasa.setObjectName("inp_grasa")
        self.gridLayout.addWidget(self.inp_grasa, 5, 1, 1, 1)
        self.Tazas_por_porcion = QtWidgets.QLabel(self.layoutWidget)
        self.Tazas_por_porcion.setObjectName("Tazas_por_porcion")
        self.gridLayout.addWidget(self.Tazas_por_porcion, 14, 0, 1, 1)
        self.Grasa = QtWidgets.QLabel(self.layoutWidget)
        self.Grasa.setObjectName("Grasa")
        self.gridLayout.addWidget(self.Grasa, 5, 0, 1, 1)
        self.Vitaminas = QtWidgets.QLabel(self.layoutWidget)
        self.Vitaminas.setObjectName("Vitaminas")
        self.gridLayout.addWidget(self.Vitaminas, 11, 0, 1, 1)
        self.Manufacturer_of_cereal = QtWidgets.QLabel(self.layoutWidget)
        self.Manufacturer_of_cereal.setObjectName("Manufacturer_of_cereal")
        self.gridLayout.addWidget(self.Manufacturer_of_cereal, 1, 0, 1, 1)
        self.Rating_cereal = QtWidgets.QLabel(self.layoutWidget)
        self.Rating_cereal.setObjectName("Rating_cereal")
        self.gridLayout.addWidget(self.Rating_cereal, 15, 0, 1, 1)
        self.inp_potasio = QtWidgets.QLineEdit(self.layoutWidget)
        self.inp_potasio.setObjectName("inp_potasio")
        self.gridLayout.addWidget(self.inp_potasio, 10, 1, 1, 1)
        self.inp_vitaminas = QtWidgets.QLineEdit(self.layoutWidget)
        self.inp_vitaminas.setObjectName("inp_vitaminas")
        self.gridLayout.addWidget(self.inp_vitaminas, 11, 1, 1, 1)
        self.inp_disposicion = QtWidgets.QLineEdit(self.layoutWidget)
        self.inp_disposicion.setObjectName("inp_disposicion")
        self.gridLayout.addWidget(self.inp_disposicion, 12, 1, 1, 1)
        self.inp_peso = QtWidgets.QLineEdit(self.layoutWidget)
        self.inp_peso.setObjectName("inp_peso")
        self.gridLayout.addWidget(self.inp_peso, 13, 1, 1, 1)
        self.inp_taza = QtWidgets.QLineEdit(self.layoutWidget)
        self.inp_taza.setObjectName("inp_taza")
        self.gridLayout.addWidget(self.inp_taza, 14, 1, 1, 1)
        self.inp_rating = QtWidgets.QLineEdit(self.layoutWidget)
        self.inp_rating.setObjectName("inp_rating")
        self.gridLayout.addWidget(self.inp_rating, 15, 1, 1, 1)
#-----------------------------------------------EVENT-----------------------------------------------------------------------#
        self.x = self.btn_insertar.clicked.connect(lambda: self.connect.Insertar(self.inp_nombre.text(),self.inp_moc.currentText(),
                                                    self.inp_tipo.currentText(),self.inp_calorias.text(),self.inp_proteinas.text(),
                                                    self.inp_grasa.text(),self.inp_sodio.text(),self.inp_fibra.text(),self.inp_carbohidratos.text(),
                                                    self.inp_azucares.text(),self.inp_potasio.text(),self.inp_vitaminas.text(),self.inp_disposicion.text(),
                                                    self.inp_peso.text(),self.inp_taza.text(),self.Rating_cereal.text(),insertar_cereal))
#---------------------------------------------END_EVENT---------------------------------------------------------------------#
 
        self.retranslateUi(insertar_cereal)
        QtCore.QMetaObject.connectSlotsByName(insertar_cereal)

    def retranslateUi(self, insertar_cereal):
        _translate = QtCore.QCoreApplication.translate
        insertar_cereal.setWindowTitle(_translate("insertar_cereal", "Form"))
        self.titulo.setHtml(_translate("insertar_cereal", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:\'Ubuntu\'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:26pt; font-weight:600;\">UTEC</span></p></body></html>"))
        self.inp_carbohidratos.setPlaceholderText(_translate("insertar_cereal", "Carbohidratos"))
        self.inp_nombre.setPlaceholderText(_translate("insertar_cereal", "Nombre"))
        self.inp_sodio.setPlaceholderText(_translate("insertar_cereal", "Sodio"))
        self.Carbohidratos.setText(_translate("insertar_cereal", "Carbohidratos"))
        self.inp_proteinas.setPlaceholderText(_translate("insertar_cereal", "Proteinas"))
        self.inp_fibra.setPlaceholderText(_translate("insertar_cereal", "Fibra"))
        self.Peso.setText(_translate("insertar_cereal", "Peso"))
        self.Proteinas.setText(_translate("insertar_cereal", "Proteinas"))
        self.inp_calorias.setPlaceholderText(_translate("insertar_cereal", "Calorias"))
        self.Potasio.setText(_translate("insertar_cereal", "Potasio"))
        self.inp_tipo.setItemText(0, _translate("insertar_cereal", "seleccionar opcion"))
        self.inp_tipo.setItemText(1, _translate("insertar_cereal", "H (Caliente)"))
        self.inp_tipo.setItemText(2, _translate("insertar_cereal", "C (Frio)"))
        self.Nombre.setText(_translate("insertar_cereal", "Nombre"))
        self.inp_azucares.setPlaceholderText(_translate("insertar_cereal", "Azucares"))
        self.Sodio.setText(_translate("insertar_cereal", "Sodio"))
        self.Fibra.setText(_translate("insertar_cereal", "Fibra"))
        self.Calorias.setText(_translate("insertar_cereal", "Calorias"))
        self.Azucares.setText(_translate("insertar_cereal", "Azucares"))
        self.Tipo.setText(_translate("insertar_cereal", "Tipo"))
        self.inp_moc.setItemText(0, _translate("insertar_cereal", "seleccionar opcion"))
        self.inp_moc.setItemText(1, _translate("insertar_cereal", "A (American Home Food Products)"))
        self.inp_moc.setItemText(2, _translate("insertar_cereal", "G (General Mills)"))
        self.inp_moc.setItemText(3, _translate("insertar_cereal", "K (Kellogs)"))
        self.inp_moc.setItemText(4, _translate("insertar_cereal", "N (Nabisco)"))
        self.inp_moc.setItemText(5, _translate("insertar_cereal", "P (Post)"))
        self.inp_moc.setItemText(6, _translate("insertar_cereal", "Q (Quacker Oats)"))
        self.inp_moc.setItemText(7, _translate("insertar_cereal", "R (Raison Purina)"))
        self.Disposicion_estante.setText(_translate("insertar_cereal", "Disposicion en estante"))
        self.btn_insertar.setText(_translate("insertar_cereal", "Insertar"))
        self.inp_grasa.setPlaceholderText(_translate("insertar_cereal", "Grasa"))
        self.Tazas_por_porcion.setText(_translate("insertar_cereal", "Tazas por porcion"))
        self.Grasa.setText(_translate("insertar_cereal", "Grasa"))
        self.Vitaminas.setText(_translate("insertar_cereal", "Vitaminas"))
        self.Manufacturer_of_cereal.setText(_translate("insertar_cereal", "Manufacturer of cereal"))
        self.Rating_cereal.setText(_translate("insertar_cereal", "Rating del cereal"))
        self.inp_potasio.setPlaceholderText(_translate("insertar_cereal", "Potasio"))
        self.inp_vitaminas.setPlaceholderText(_translate("insertar_cereal", "Vitaminas"))
        self.inp_disposicion.setPlaceholderText(_translate("insertar_cereal", "Altura en estante"))
        self.inp_peso.setPlaceholderText(_translate("insertar_cereal", "Peso en kg"))
        self.inp_taza.setPlaceholderText(_translate("insertar_cereal", "Tazas por porcion"))
        self.inp_rating.setPlaceholderText(_translate("insertar_cereal", "Valoracion del cereal"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    insertar_cereal = QtWidgets.QWidget()
    ui = Ui_insertar_cereal()
    ui.setupUi(insertar_cereal)
    insertar_cereal.show()
    sys.exit(app.exec_())
