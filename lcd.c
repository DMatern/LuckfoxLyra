#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>

#define I2C_BUS "/dev/i2c-2"  // Luckfox Lyra I2C-2 bus
#define LCD_ADDR 0x27         // PCF8574 I2C address

// Function to send a command to the LCD
void lcd_send_command(int fd, unsigned char cmd) {
    unsigned char data[2] = {0x00, cmd};
    write(fd, data, sizeof(data));
    usleep(2000);
}

// Function to send data (characters) to the LCD
void lcd_send_data(int fd, unsigned char data) {
    unsigned char buffer[2] = {0x40, data};
    write(fd, buffer, sizeof(buffer));
    usleep(2000);
}

// Function to initialize the LCD
void lcd_init(int fd) {
    lcd_send_command(fd, 0x38); // Function set: 2-line mode
    lcd_send_command(fd, 0x0C); // Display ON, Cursor OFF
    lcd_send_command(fd, 0x01); // Clear display
    usleep(2000);
}

// Function to clear the LCD screen
void lcd_clear(int fd) {
    lcd_send_command(fd, 0x01);
}

// Function to print text to the LCD
void lcd_print(int fd, const char *text) {
    lcd_clear(fd);
    for (int i = 0; text[i] != '\0'; i++) {
        lcd_send_data(fd, text[i]);
    }
}

// Main function to watch CLI input and update LCD
int main() {
    int fd = open(I2C_BUS, O_RDWR);
    if (fd < 0) {
        perror("Failed to open I2C bus");
        return 1;
    }

    if (ioctl(fd, I2C_SLAVE, LCD_ADDR) < 0) {
        perror("Failed to connect to LCD");
        close(fd);
        return 1;
    }

    lcd_init(fd);
    char input[40];

    while (1) {
        printf("Enter text for LCD (Press Enter to clear): ");
        fgets(input, sizeof(input), stdin);

        // Remove newline character
        input[strcspn(input, "\n")] = 0;

        if (strlen(input) == 0) {
            lcd_clear(fd);
        } else {
            lcd_print(fd, input);
        }
    }

    close(fd);
    return 0;
}