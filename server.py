from flask import Flask, render_template
import serial
import os

app = Flask(__name__)

# Define the path to the templates directory
template_dir = os.path.abspath(os.path.dirname(__file__))
app.template_folder = template_dir

@app.route('/')
def index():
    try:
        return render_template('index.html')
    except Exception as e:
        return f"Error rendering template: {str(e)}", 500

@app.route('/data')
def data():
    try:
        ser = serial.Serial('/dev/ttyACM0', 9600)  # Adjust serial port as needed
        temperature = ser.readline().decode().strip()
        ser.close()
        return temperature
    except serial.SerialException as e:
        return str(e), 500

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
