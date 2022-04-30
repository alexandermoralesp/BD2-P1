import sys
import os
myDir = os.getcwd()
sys.path.append(myDir)

class select():
    def __init__(self, conn, tabla, create = 1):
        self.conn = conn
        self.tabla = tabla
        if(tabla == "btn_fifa" and create == 0):
            with self.conn.cursor() as cursor:
                sql = """DROP TABLE IF EXISTS proyectotable;"""
                cursor.execute(sql)
                self.conn.commit()
                sql = """CREATE TABLE IF NOT EXISTS proyectotable
                            (ID VARCHAR(10), Foot VARCHAR(2), Position VARCHAR(2), Awr_ VARCHAR(2), Dwr_ VARCHAR(2), Ovr_ VARCHAR(2),
                            Pac_ VARCHAR(2), Sho_ VARCHAR(2), Pas_ VARCHAR(2), Dri_ VARCHAR(2), Def_ VARCHAR(2), Phy_ VARCHAR(2), Sm_ VARCHAR(2),
                            Div_ VARCHAR(2), Pos_ VARCHAR(2), Han_ VARCHAR(2), Ref_ VARCHAR(2), Kic_ VARCHAR(2), Spd_ VARCHAR(2));"""
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