import sys
import os
import glob
import ctypes
myDir = os.getcwd()
sys.path.append(myDir)

from PyQt5 import QtWidgets
from Database.Connection import connection
from Models.Select import select

libfile =  glob.glob('build/*/menuSequential*.so')[0]
mylib = ctypes.CDLL(libfile)

mylib.remove_S_Fifa.restype = ctypes.c_bool
mylib.remove_S_Fifa.argtypes = [ctypes.c_char_p]

mylib.remove_S_Cereal.restype = ctypes.c_bool
mylib.remove_S_Cereal.argtypes = [ctypes.c_char_p]

class Eliminar():
    def __init__(self,tabla, din_seq):
        self.dinorseq = din_seq
        self.tabla_ = tabla
        self.conn = select(connection,tabla)
        
    def Eliminar(self, valor, close):
        if(self.dinorseq == "Seq"):
            if(self.tabla_ == "fifa"):
                x = mylib.remove_S_Fifa(valor)
            else:
                x = mylib.remove_S_Cereal(valor)
        close.hide()