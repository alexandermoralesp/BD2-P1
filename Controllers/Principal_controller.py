import sys
import os
myDir = os.getcwd()
sys.path.append(myDir)

from PyQt5 import QtWidgets
from Database.Connection import connection
from Views.Bplus_cereal import Ui_Bplus_cereales
from Views.Bplus_titanic import Ui_Bplus_titanic
from Views.Dinamyc_cereal import Ui_DInamy_titanic
from Views.Dinamyc_titanic import Ui_Dinamyc_titanic
from Views.sequential_cereal import Ui_sequential_cereal
from Views.sequential_titanic import Ui_sequential_titanic

class Principal_controller():
    def __init__(self, connect) :
        self.connect = connect


    def change(self, tabla, close, formato,parent):
        if(tabla == "btn_titanic"):
            if(formato == "b"):
                open = Ui_Bplus_titanic
            elif(formato == "seq"):
                open = Ui_sequential_titanic
            else:
                open = Ui_Dinamyc_titanic
        elif(tabla == "btn_cereal"):
            if(formato == "b"):
                open = Ui_Bplus_cereales
            elif(formato == "seq"):
                open = Ui_sequential_cereal
            else:
                open = Ui_DInamy_titanic

        close.hide()
        self.connect.Form = QtWidgets.QMainWindow()
        self.connect.ui = open(parent)
        self.connect.ui.setupUi(self.connect.Form)
        self.connect.Form.show()