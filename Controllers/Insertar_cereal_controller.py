import sys
import os
myDir = os.getcwd()
sys.path.append(myDir)

from PyQt5 import QtWidgets
from Database.Connection import connection
from Models.Select import select

class Insertar_cereal():
    def __init__(self,tabla):
        self.conn = select(connection,tabla)

    def Insertar(self, nombre, manufacturer, tipo, calorias, proteinas, grasa, sodio, fibra, carbohidratos, azucares, potasio, 
                vitaminas, disposicion, peso, taza, rating, close):
        
        close.hide()