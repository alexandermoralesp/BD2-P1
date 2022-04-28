import sys
import os
myDir = os.getcwd()
sys.path.append(myDir)

from PyQt5 import QtWidgets
from Database.Connection import connection
from Models.Select import select

class Seq_cereal():
    def __init__(self,conn,tabla):
        self.principal = conn
        self.conn = select(connection,tabla)

    def call_insert(self, Insert):
        self.principal.Form = QtWidgets.QWidget()
        self.principal.ui = Insert("cereal")
        self.principal.ui.setupUi(self.principal.Form)
        self.principal.Form.show()
        

    def call_search1(self, search1):
        self.principal.Form = QtWidgets.QWidget()
        self.principal.ui = search1("cereal")
        self.principal.ui.setupUi(self.principal.Form)
        self.principal.Form.show()
    
    def call_eliminar(self, eliminar):
        self.principal.Form = QtWidgets.QWidget()
        self.principal.ui = eliminar("cereal")
        self.principal.ui.setupUi(self.principal.Form)
        self.principal.Form.show()

    def call_back(self, back, close):
        close.hide()
        self.principal.Form = QtWidgets.QWidget()
        self.principal.ui = back()
        self.principal.ui.setupUi(self.principal.Form)
        self.principal.Form.show()