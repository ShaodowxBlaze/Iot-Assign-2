CREATE TABLE sensor_data (
    id INT AUTO_INCREMENT PRIMARY KEY,
    temperature FLOAT,
    heart_rate INT,
    fall_detect TINYINT(1),
    timestamp DATETIME
);

CREATE TABLE led_state (
    id INT AUTO_INCREMENT PRIMARY KEY,
    red_LED TINYINT(1),
    yellow_LED TINYINT(1),
    green_LED TINYINT(1),
    timestamp DATETIME
);
