#include <Adafruit_MLX90614.h>
#include <LiquidCrystal.h>

#define BUZZER_PIN 8 // Change this to the pin number where your buzzer is connected
#define LCD_RS 7     // Change these to match the pins you've connected the LCD to
#define LCD_EN 6
#define LCD_D4 5
#define LCD_D5 4
#define LCD_D6 3
#define LCD_D7 2

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

void setup() {
  Serial.begin(9600);
  mlx.begin();
  lcd.begin(16, 2); // Initialize the LCD with 16 columns and 2 rows
  pinMode(BUZZER_PIN, OUTPUT); // Set buzzer pin as output
}

void loop() {
  float temperature = mlx.readObjectTempC();
  Serial.println(temperature);
  
  lcd.clear(); // Clear the LCD display
  lcd.setCursor(0, 0); // Set cursor to first column of first row
  lcd.print("Temp: "); // Print label
  lcd.print(temperature); // Print temperature
  
  if (temperature > 30) { // Check if temperature is above 30 degrees Celsius
    digitalWrite(BUZZER_PIN, HIGH); // Turn on buzzer
    lcd.setCursor(0, 1); // Set cursor to first column of second row
    lcd.print("Warning!"); // Display warning message on LCD
  } else {
    digitalWrite(BUZZER_PIN, LOW); // Turn off buzzer
  }

  delay(500);
}
