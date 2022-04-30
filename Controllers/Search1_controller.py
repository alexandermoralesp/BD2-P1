from re import X
import sys
import os
import ctypes
import glob
myDir = os.getcwd()
sys.path.append(myDir)

from PyQt5 import QtWidgets
from Database.Connection import connection
from Models.Select import select

libfile =  glob.glob('build/*/menuSequential*.so')[0]
mylib = ctypes.CDLL(libfile)

libfile2 =  glob.glob('build/*/menuFifa*.so')[0]
mylib2 = ctypes.CDLL(libfile2)

mylib.search_S_Fifa.restype = ctypes.c_char_p
mylib.search_S_Fifa.argtypes = [ctypes.c_char_p,ctypes.c_char_p]

mylib.search_S_Cereal.restype = ctypes.c_char_p
mylib.search_S_Cereal.argtypes = [ctypes.c_char_p,ctypes.c_char_p]


class Search1():
    def __init__(self,tabla,table,din_seq):
        self.dinorseq = din_seq
        self.table = table
        self.tabla_ = tabla
        self.conn = select(connection,tabla)

    def search1(self, valor, close):
        if(self.dinorseq == "Seq"):
            aux = ctypes.create_string_buffer(150)
            if(self.tabla_ == "fifa"):
                x = mylib.search_S_Fifa(str(valor).encode('utf-8'),aux)
            else:
                x = mylib.search_S_Cereal(str(valor).encode('utf-8'),aux)
        x = x.decode('utf-8')
        x = x.split(',')
        tabla = self.table.table
        tabla.setRowCount(1)
        column_number=0
        for data in x:
            tabla.setItem(0,column_number,QtWidgets.QTableWidgetItem(data))
            column_number+=1
        close.hide()