import sys
import os
myDir = os.getcwd()
sys.path.append(myDir)

from PyQt5 import QtWidgets
from Database.Connection import connection
from Models.Select import select


class Select_csv_controller():
    def __init__(self, connect) :
        
        self.connect = connect
        
    
    def change(self, tabla, open, close,parent):
        self.user = select(connection(),tabla,0)
        close.hide()
        self.connect.Form = QtWidgets.QMainWindow()
        self.connect.ui = open(tabla,parent)
        self.connect.ui.setupUi(self.connect.Form)
        self.connect.Form.show()