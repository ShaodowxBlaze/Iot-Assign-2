from flask import Flask, render_template, request
import serial
import mysql.connector

app = Flask(__name__)

# MySQL Configuration
db = mysql.connector.connect(
    host="localhost",
    user="pi",
    password="admin1234",
    database="sensor_db"
)
cursor = db.cursor()

# Routes
@app.route('/display_data')
def display_data():
    # Fetch data from MySQL
    cursor.execute("SELECT * FROM sensor_data LIMIT 10")
    sensor_data = cursor.fetchall()
    
    # Fetch LED statuses from MySQL
    cursor.execute("SELECT * FROM led_status LIMIT 10")
    led_status = cursor.fetchall()
    
    return render_template('health_data.html', sensor_data=sensor_data, led_status=led_status)

@app.route('/add_data', methods=['POST'])
def add_data():
    fall_detection = request.form['fall_detection']
    heart_rate = request.form['heart_rate']
    temperature = request.form['temperature']
    cursor.execute("INSERT INTO sensor_data (fall_detection, heart_rate, temperature) VALUES (%s, %s, %s)", (fall_detection, heart_rate, temperature))
    
    red_led_status = request.form['red_led_status']
    yellow_led_status = request.form['yellow_led_status']
    green_led_status = request.form['green_led_status']
    cursor.execute("INSERT INTO led_status (red_led_status, yellow_led_status, green_led_status) VALUES (%s, %s, %s)", (red_led_status, yellow_led_status, green_led_status))
    
    db.commit()
    return 'Data added successfully'

if __name__ == '__main__':
    app.run(debug=True)
