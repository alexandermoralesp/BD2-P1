import sys
import os
myDir = os.getcwd()
sys.path.append(myDir)

class select():
    def __init__(self, conn, tabla, create = 1):
        self.conn = conn
        if(tabla == "btn_titanic" and create == 0):
            with self.conn.cursor() as cursor:
                sql = """DROP TABLE IF EXISTS proyectotable;"""
                cursor.execute(sql)
                self.conn.commit()
                sql = """CREATE TABLE IF NOT EXISTS proyectotable
                            (ID VARCHAR(10), Sobrevivio VARCHAR(2), Clase VARCHAR(2), Nombre_y_Apellido VARCHAR(90), Sexo VARCHAR(1), Edad INT, Sibsp VARCHAR(2), Parch VARCHAR(2));"""
                cursor.execute(sql)
                self.conn.commit()
        elif (tabla == "btn_cereal" and create == 0):
            with self.conn.cursor() as cursor:
                sql = """DROP TABLE IF EXISTS proyectotable;"""
                cursor.execute(sql)
                self.conn.commit()
                sql = """CREATE TABLE IF NOT EXISTS proyectotable
                            (Nombre VARCHAR(15), Manufacturer VARCHAR(2), Tipo VARCHAR(2), Calorias INT, Proteinas INT, Grasa INT, Sodio INT, Fibra INT, Carbohidratos INT,
                            Azucares INT, Potasio INT, Vitaminas INT, Disposicion INT, Peso FLOAT, Tazas FLOAT, Rating FLOAT);"""
                cursor.execute(sql)
                self.conn.commit()
       