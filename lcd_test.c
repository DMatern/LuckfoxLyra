#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include "LiquidCrystal_I2C.h"

#define I2C_BUS "/dev/i2c-2"
#define LCD_ADDR 0x27

// // Function to send a command to the LCD
// void lcd_send_command(int i2c_fd, const char *command) {
//   size_t len = strlen(command);
//   for (size_t i = 0; i < len; i++) {
//     char data[2] = {0x80, command[i]}; // 0x80 indicates command mode
//     if (write(i2c_fd, data, 2) != 2) {
//       perror("Failed to send command to LCD");
//       return;
//     }
//     usleep(1000); // Small delay for LCD processing
//   }
// }

// // Function to initialize the LCD
// void lcd_init(int i2c_fd) {
//   const char *init_commands[] = {
//     "\x33", "\x32", "\x28", "\x0C", "\x06", "\x01"
//   };
//   for (int i = 0; i < 6; i++) {
//     lcd_send_command(i2c_fd, init_commands[i]);
//     usleep(5000); // Delay for initialization commands
//   }
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_INPUT_SIZE 256

void setNonBlockingMode(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

int main() {
    char buffer[MAX_INPUT_SIZE] = {0};
    int index = 0;
    int newDataFlag = 0;

    setNonBlockingMode(STDIN_FILENO);  // Set stdin to non-blocking mode

    printf("Enter text (press Enter to submit):\n");

    while (1) {

        usleep(100000);  // Sleep briefly to prevent CPU overuse



    return 0;
}

int main() {
  // int i2c_fd = open(I2C_BUS, O_RDWR);
  // if (i2c_fd < 0) {
  //   perror("Failed to open I2C bus");
  //   return 1;
  // }

  // if (ioctl(i2c_fd, I2C_SLAVE, LCD_ADDR) < 0) {
  //   perror("Failed to set I2C address");
  //   close(i2c_fd);
  //   return 1;
  // }  
  
  setup();
  
  // main loop
  while (1) {
    // Handle CLI Commands
        printf("Enter text for LCD (Press Enter to clear): ");		//print text to CLI
        fgets(input, sizeof(input), stdin);											//listen for input from CLI including \n

        // Remove newline character
        input[strcspn(input, "\n")] = 0;

        if (strlen(input) == 0) {
            lcd_clear(fd);
        } else {
            lcd_print(fd, input);
        }
        
        if (newDataFlag) {
        		printf("Received input: \"%s\"\n", buffer);
    			}
    }

    close(fd);
    retu-rn 0;

  // close(i2c_fd);
  return 0;
}

void setup() {
	
  LiquidCrystal_I2C lcd(0x27, 16, 2, "/dev/i2c-2"); // I2C address 0x27, 16 columns, 2 rows, bus /dev/i2c-2
  lcd.begin(16, 2);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hello, World!");

  lcd.setCursor(0, 1);
  lcd.print(12345); // Print an integer

  sleep(5); // Wait for 5 seconds

  lcd.clear();

}

bool readCLI() {
	char ch;
        ssize_t bytesRead = read(STDIN_FILENO, &ch, 1);

        if (bytesRead > 0) {
            if (ch == '\n') {
                buffer[index] = '\0';  // Null-terminate and remove newline
                newDataFlag = 1;       // Set flag for new data
                break;
            } else if (index < MAX_INPUT_SIZE - 1) {
                buffer[index++] = ch;
            }
        }
}