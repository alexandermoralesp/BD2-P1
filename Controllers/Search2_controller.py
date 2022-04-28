import sys
import os
myDir = os.getcwd()
sys.path.append(myDir)

from PyQt5 import QtWidgets
from Database.Connection import connection
from Models.Select import select

class Search2():
    def __init__(self,tabla):
        self.conn = select(connection,tabla)
    def search2(self, inicio, final, close):
        close.hide()