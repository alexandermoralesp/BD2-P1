import sys
import os
myDir = os.getcwd()
sys.path.append(myDir)

from PyQt5 import QtWidgets
from Database.Connection import connection
from Views.Dinamyc_cereal import Ui_DInamyc_cereal
from Views.Dinamyc_fifa import Ui_Dinamyc_fifa
from Views.sequential_cereal import Ui_sequential_cereal
from Views.sequential_fifa import Ui_sequential_fifa

class Principal_controller():
    def __init__(self, connect) :
        self.connect = connect


    def change(self, tabla, close, formato,parent):
        if(tabla == "btn_fifa"):
            if(formato == "seq"):
                open = Ui_sequential_fifa
            else:
                open = Ui_Dinamyc_fifa
        elif(tabla == "btn_cereal"):
            if(formato == "seq"):
                open = Ui_sequential_cereal
            else:
                open = Ui_DInamyc_cereal

        close.hide()
        self.connect.Form = QtWidgets.QMainWindow()
        self.connect.ui = open(parent)
        self.connect.ui.setupUi(self.connect.Form)
        self.connect.Form.show()