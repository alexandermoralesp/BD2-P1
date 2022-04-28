import sys
import os
myDir = os.getcwd()
sys.path.append(myDir)

from PyQt5 import QtWidgets
from Database.Connection import connection
from Models.Select import select

class Insertar_titanic():
    def __init__(self,tabla):
        self.conn = select(connection,tabla)

    def Insertar(self, id, sobrevivio, clase, apellido, nombre,sexo, edad, sibsp, parch, close):
        nombre_completo = apellido + ', ' + nombre
        close.hide()