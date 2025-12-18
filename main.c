// ELEC2645 Unit 2 Project 
// Command Line Application Menu Handling Code
//this file is responsible for user interaction, menu display, and program flow control

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "funcs.h"

// -------------------- Function Prototypes -------------------- 

/* Prototypes mirroring the C++ version */
static void main_menu(void);            /* runs in the main loop */
static void print_main_menu(void);      /* output the main menu description */
static int  get_user_input(void);       /* get a valid integer menu choice */
static void select_menu_item(int input);/* run code based on user's choice */
static void go_back_to_main(void);      /* wait for 'b'/'B' to continue */
static int  is_integer(const char *s);  /* validate integer string */

// -------------------- Main Function -------------------- 

int main(void)
{
    /* this will run forever until we call exit(0) in select_menu_item() */
    for(;;) {
        main_menu();
    }
    /* not reached */
    return 0;
}

// -------------------- Menu Control Functions -------------------- 
//Displays main menu, gets user input and calls the selected options
static void main_menu(void)
{
    print_main_menu(); // show menu option
    {
        int input = get_user_input(); //get valid menu selection
        select_menu_item(input); //run selected menu item
    }
}

static int get_user_input(void)
{
    char buf[64]; //buffer to store user input as a string
    int value;

    while (1) {
        printf("\nSelect item: ");

        if (!fgets(buf, sizeof buf, stdin)) { //reads user input safely using fgets
            puts("Input error. Exiting.");
            exit(1);
        }

        // strip newline 
        buf[strcspn(buf, "\r\n")] = '\0';

        //convert string to number 
        value = (int)strtol(buf, NULL, 10);

        // check valid menu range 
        if (value >= 1 && value <= 4) {
            return value;
        }

        puts("Invalid menu selection. Please enter 1–4.");
    }
}

// Calls appropriate function based on user selection
static void select_menu_item(int input)
{
    switch (input) {
        case 1:            //Decode 4-band resistor
            menu_item_1();
            go_back_to_main();
            break;
        case 2:           //Decode 5-band resistor
            menu_item_2();
            go_back_to_main();
            break;
        case 3:           //View last decoded resistor
            menu_item_3();
            go_back_to_main();
            break;
        case 4:           //Exit program
            menu_item_4();
            go_back_to_main();
            break;
        default: // this will never occur due to input validation
            printf("Bye!\n");
            exit(0);
    }
}

static void print_main_menu(void)
{
    printf("\n----------- Resistor Decoder Menu -----------\n");
    printf("\n"
           "\t\t\t\t\t\t\n"
           "\t1. Decode 4-band resistor\t\t\n"
           "\t2. Decode 5-band resistor\t\t\n"
           "\t3. View last decoded resistor\t\t\n"
           "\t4. Exit\t\t\t\t\n"
           "\t\t\t\t\t\t\n");
    printf("---------------------------------------------\n");
}

static void go_back_to_main(void) //pauses execution until user types b or B
{
    char buf[64];
    do {   
        printf("\nEnter 'b' or 'B' to go back to main menu: ");
        if (!fgets(buf, sizeof(buf), stdin)) {
            puts("\nInput error. Exiting.");
            exit(1);
        }
        buf[strcspn(buf, "\r\n")] = '\0'; /* strip newline */
    } while (!(buf[0] == 'b' || buf[0] == 'B') || buf[1] != '\0');
}
