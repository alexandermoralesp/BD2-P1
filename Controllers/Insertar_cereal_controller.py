from glob import glob
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

mylib.insert_S_Cereal.restype = ctypes.c_bool
mylib.insert_S_Cereal.argtypes = [ctypes.c_char_p]

class Insertar_cereal():
    def __init__(self,tabla):
        self.conn = select(connection,tabla)

    def Insertar(self, nombre, manufacturer, tipo, calorias, proteinas, grasa, sodio, fibra, carbohidratos, azucares, potasio, 
                vitaminas, disposicion, peso, taza, rating, close):
        cadena = nombre + ',' + manufacturer +',' + tipo +',' + calorias + ',' + proteinas + ',' + grasa +',' + sodio +',' + fibra + ',' + carbohidratos + ',' + azucares + ',' + potasio + ',' + vitaminas + ',' + disposicion + ',' + peso + ',' + taza + ',' + rating
        x = mylib.insert_S_Cereal(str(cadena).encode('utf-8'))
        close.hide()