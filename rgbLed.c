#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define PWM_CHIP "/sys/class/pwm/pwmchip0"

typedef struct {
    int red_pin;
    int green_pin;
    int blue_pin;
} RGB_LED;

// Function to set PWM duty cycle
void set_pwm_duty_cycle(int pin, int value) {
    char path[64];
    snprintf(path, sizeof(path), "%s/pwm%d/duty_cycle", PWM_CHIP, pin);
    
    FILE *fp = fopen(path, "w");
    if (fp) {
        fprintf(fp, "%d", value);
        fclose(fp);
    } else {
        perror("Failed to set PWM duty cycle");
    }
}

// Function to set RGB color
void set_rgb_color(RGB_LED *led, int r, int g, int b) {
    set_pwm_duty_cycle(led->red_pin, r);
    set_pwm_duty_cycle(led->green_pin, g);
    set_pwm_duty_cycle(led->blue_pin, b);
}

// Function to initialize PWM channels
void init_pwm(RGB_LED *led) {
    char path[64];

    for (int i = 0; i < 3; i++) {
        snprintf(path, sizeof(path), "%s/pwm%d/enable", PWM_CHIP, i);
        FILE *fp = fopen(path, "w");
        if (fp) {
            fprintf(fp, "1");
            fclose(fp);
        }
    }
}

// Function to disable PWM
void disable_pwm(RGB_LED *led) {
    char path[64];

    for (int i = 0; i < 3; i++) {
        snprintf(path, sizeof(path), "%s/pwm%d/enable", PWM_CHIP, i);
        FILE *fp = fopen(path, "w");
        if (fp) {
            fprintf(fp, "0");
            fclose(fp);
        }
    }
}

int main() {
    RGB_LED led = {0, 1, 2}; // Assign PWM pins for Red, Green, and Blue

    init_pwm(&led);
    
    set_rgb_color(&led, 500000, 250000, 750000); // Example: Purple
    sleep(2);
    
    set_rgb_color(&led, 1000000, 0, 0); // Example: Red
    sleep(2);

    disable_pwm(&led);
    return 0;
}