# Import Flask and other necessary modules
from flask import Flask, render_template
import mysql.connector

# Initialize Flask application
app = Flask(_name_)

# Establish MySQL connection
mydb = mysql.connector.connect(
    host="localhost",
    user="pi",
    password="admin1234",
    database="sensor_db"
)

# Create cursor object
mycursor = mydb.cursor()

# Route to display combined SensorData and Actuator data
@app.route('/display_data')
def display_data():
    # Fetch data from sensor_data table
    mycursor.execute("SELECT * FROM sensor_data")
    sensor_data = mycursor.fetchall()
    
    return render_template('HealthData.html', sensor_data=sensor_data)

# Run Flask application
if _name_ == '_main_':
    app.run(debug=True)