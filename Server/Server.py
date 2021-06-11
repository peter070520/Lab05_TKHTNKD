from flask import Flask, render_template, request, jsonify, json
from flask_mqtt import Mqtt
from flask_sqlalchemy import SQLAlchemy
from datetime import date, datetime
app = Flask(__name__, template_folder='templates')

app.config['MQTT_BROKER_URL'] = 'mqtt.flespi.io'
app.config['MQTT_BROKER_PORT'] = 1883
app.config['TEMPLATES_AUTO_RELOAD'] = True
app.config['MQTT_CLIENT_ID'] = 'flask_mqtt'
app.config['MQTT_CLEAN_SESSION'] = True
# change with your Flespi token
app.config['MQTT_USERNAME'] = 'FlespiToken dk6hQ7z9nUjk1S3qATNDb08oULyZ1E82M47s2updezl5fejFYX8XL4btFyhu2fmE'
app.config['MQTT_PASSWORD'] = ''
app.config['MQTT_REFRESH_TIME'] = 1.0  # refresh time in seconds
# create database in https://www.freemysqlhosting.net/          //cho de tao tai khoan free host
# format Url: mysql://username:password@host/databasename
# default port 3306
app.config['SQLALCHEMY_DATABASE_URI'] = 'mysql://root:@127.0.0.1/sensor'
mqtt = Mqtt(app)
db = SQLAlchemy(app)

def insert(value):
    value2 = ["",""]
    value2 = value[:-1].split(" ")
    value2[1] = value2[1].replace("\u0000\u0000\u0000\u0000\u0000", "")
    print(value2)
    today = date.today()
    now = datetime.now()
    current_time = now.strftime("%H:%M:%S")
    sql = "INSERT INTO `Data`(`temp`, `hud`, `date`, `hour`) VALUES (%s, %s, %s, %s)"
    val = (value2[0], value2[1], today, current_time)
    db.engine.execute(sql, val)
    db.session.commit()

@app.route('/')
def index():
    return render_template('./index.html')

@app.route('/data', methods=['GET'])
def data():
    rows = db.engine.execute('SELECT id, temp, date, hour FROM Data ORDER BY id DESC LIMIT 10')
    listdata = []
    for i in rows:
        dictdata = {
            "id" : i.id,
            "temp" : i.temp,
            "date" : i.date.__str__(),
            "hour" : i.hour.__str__()
        }
        listdata.append(dictdata)
    return json.dumps(listdata)

@app.route('/hud', methods=['GET'])
def data2():
    rows = db.engine.execute('SELECT id, hud, date, hour FROM Data ORDER BY id DESC LIMIT 10')
    listdata = []
    for i in rows:
        dictdata = {
            "id" : i.id,
            "hud" : i.hud,
            "date" : i.date.__str__(),
            "hour" : i.hour.__str__()
        }
        listdata.append(dictdata)
    return json.dumps(listdata)

@mqtt.on_connect()
def handle_connect(client, userdata, flags, rc):
    mqtt.subscribe('crawldata')

@mqtt.on_message()
def handle_mqtt_message(client, userdata, message):
    data = dict(
        topic=message.topic,
        payload=message.payload.decode()
    )
    if data["topic"] == "crawldata":
        insert(data["payload"])
if __name__ == '__main__':
   app.run()