from dataclasses import dataclass

import pymysql

def connection():
    conn = pymysql.connect(
        host="localhost", port=3306, user="root",
        password="",db = "proyecto"
    )
    print("database connected")
    return conn