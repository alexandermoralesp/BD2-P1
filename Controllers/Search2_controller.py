import ctypes
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

mylib.rangeSearch_S_Fifa.restype = ctypes.c_char_p
mylib.rangeSearch_S_Fifa.argtypes = [ctypes.c_char_p,ctypes.c_char_p,ctypes.c_char_p,ctypes.c_char_p]

mylib.rangeSearch_S_Cereal.restype = ctypes.c_char_p
mylib.rangeSearch_S_Cereal.argtypes = [ctypes.c_char_p,ctypes.c_char_p,ctypes.c_char_p,ctypes.c_char_p]

result = ctypes.create_string_buffer(10000)
aux = ctypes.create_string_buffer(150)
       
x = mylib.rangeSearch_S_Cereal(str("Apple Cinnamon Cheerios").encode('utf-8'),str("Double Chex").encode('utf-8'),result,aux)
print(result.value.decode())

class Search2():
    def __init__(self,tabla,table):
        self.table = table
        self.tabla_ = tabla
        self.conn = select(connection,tabla)


    def search2(self, inicio, final, close):
        result = ctypes.create_string_buffer(10000)
        aux = ctypes.create_string_buffer(150)
        
        x = mylib.rangeSearch_S_Cereal(str(inicio).encode('utf-8'),str(final).encode('utf-8'),result,aux)
        
        x = x.decode('utf-8')
        x = x.split('|')
        tabla = self.table.table
        tabla.setRowCount(len(x))
        column_number=0
        row_number = 0
        for data in x:
           
            y = data.split(',')
            for data in range(len(y)):
                print(y[data])
                if column_number< len(y):
                    tabla.setItem(row_number,column_number,QtWidgets.QTableWidgetItem(y[data]))

                column_number+=1
            row_number += 1
            column_number = 0
            print("1linea")
        close.hide()