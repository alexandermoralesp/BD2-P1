from cgitb import handler
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

mylib.insert_S_Fifa.restype = ctypes.c_bool
mylib.insert_S_Fifa.argtypes = [ctypes.c_char_p]

class Insertar_fifa():
    def __init__(self,tabla):
        self.conn = select(connection,tabla)

    def Insertar(self, _id, _foot, _position, _awr, _dwr, _ovr, _pac, _sho, _pas,
                _dri, _def, _phy, _sm, _div, _pos, _han, _ref, _kic, _spd, close):
        cadena = _id + ',' + _foot + ',' + _position +',' + _awr + ',' + _dwr + ',' + _ovr + ',' + _pac +',' + _sho +',' + _pas + ',' + _dri + ',' + _def + ',' + _phy + ',' + _sm + ',' + _div + ',' + _pos +',' + _han + ',' + _ref + ',' + _kic + ',' + _spd
        
        x = mylib.insert_S_Fifa(str(cadena).encode('utf-8'))
        print(x)
        close.hide()