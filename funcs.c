#include <stdio.h>
#include "funcs.h"
#define LAST_FILE "last_resistor.txt"
#include <string.h>

// this removes any trailing newlines from a string, this is needed because fgets() stores the newline character.
static void strip_newline(char *s)
{ if (!s) return;
  s[strcspn(s, "\r\n")]='\0';
}
//converts all uppercase characters in a string to lowercase.
//this allows us to make color inputs to be case insensitive.
static void to_lowercase(char *s)
{
    if(!s) return;
    for(int i=0; s[i]!='\0'; i++)
    {
        if(s[i]>='A' && s[i]<='Z'){
            s[i] = (char)(s[i]+32);
        }
    }
}
// asks the user for a colour input, it also removes the newline characters and converts it to lowercase
static void read_colour(char *buf, int n, const char *prompt )
{
printf("%s", prompt);

if(!fgets(buf,(int)n, stdin)) {
    puts("input error");
    exit(1);
}
strip_newline(buf);
to_lowercase(buf);


}
//saves the most recently decoded resistor value to a text file
//the file gets overwritten each time
static void save_last_resistor(const char *text)
{
    FILE *fp=fopen(LAST_FILE,"w");
    if(!fp) return;
    fprintf(fp,"%s\n",text);
    fclose(fp);
}
//this loads the last saved resistor value from the file
static int load_last_resistor(char *out,size_t out_sz){
    FILE *fp= fopen(LAST_FILE,"r");
    if(!fp) return -1;  //returns 0 on success and -1 if file does not exist or cannot be read

    if(!fgets(out,(int)out_sz, fp)){
        fclose(fp);
        return -1;
    
    }
    fclose(fp);
    strip_newline(out);
    return 0;
}


// ---------------- Colour decoding functions ---------------- 

//converts a colour string to its corresponding digit value
//will return -1 if color is invalid
static int digit_value(const char *c){

    if (!strcmp(c,"black"))  return 0;
    if (!strcmp(c,"brown"))  return 1;
    if (!strcmp(c,"red"))    return 2;
    if (!strcmp(c,"orange")) return 3;
    if (!strcmp(c,"yellow")) return 4;
    if (!strcmp(c,"green"))  return 5;
    if (!strcmp(c,"blue"))   return 6;
    if (!strcmp(c,"violet")) return 7;
    if (!strcmp(c,"grey"))   return 8;
    if (!strcmp(c,"white"))  return 9;
    return -1;

}

//converts colour strings to corresponding multiplier value
//will return -1 if color is invalid
static double multiplier_value(const char *c){
    if(!strcmp(c,"black"))  return 1;
    if (!strcmp(c,"brown")) return 10;
    if (!strcmp(c,"red"))    return 100;
    if (!strcmp(c,"orange")) return 1e3;
    if (!strcmp(c,"yellow")) return 1e4;
    if (!strcmp(c,"green")) return 1e5;
    if (!strcmp(c,"blue"))   return 1e6;
    if (!strcmp(c,"violet")) return 1e7;
    if (!strcmp(c,"grey"))   return 1e8;
    if (!strcmp(c,"white")) return 1e9;
    if (!strcmp(c,"gold"))   return 0.1;
    if (!strcmp(c,"silver")) return 0.01;
    return -1;
}


//converts colour strings to corresponding tolerance value
//will return -1 if color is invalid
static double tolerance_value(const char *c){

    if (!strcmp(c, "brown"))  return 1.0;
    if (!strcmp(c, "red"))    return 2.0;
    if (!strcmp(c, "green"))  return 0.5;
    if (!strcmp(c, "blue"))   return 0.25;
    if (!strcmp(c, "violet")) return 0.1;
    if (!strcmp(c, "grey"))   return 0.05;
    if (!strcmp(c, "gold"))   return 5.0;
    if (!strcmp(c, "silver")) return 10.0;
    return -1;
}

// ---------------- Menu items ---------------- 

//menu option 1 is 4-band resistor
void menu_item_1(void) {
    char b1[32], b2[32], b3[32], b4[32];
    puts("\n>> 4-Band Resistor Decoder");
    puts("Valid digit colours: black|brown|red|orange|yellow|green|blue|violet|grey|white");
    puts("Valid multiplier colours: All the above + gold|silver");
    puts("Valid tolerance colours: brown|red|green|blue|violet|grey|gold|silver");
    
    read_colour(b1, sizeof b1, "Band 1 (digit): ");
    read_colour(b2, sizeof b2, "Band 2 (digit): ");
    read_colour(b3, sizeof b3, "Band 3 (multiplier): ");
    read_colour(b4, sizeof b4, "Band 4 (tolerance): ");
    
    int d1=digit_value(b1);
    int d2=digit_value(b2);
    double mult=multiplier_value(b3);
    double toler=tolerance_value(b4);

     if (d1 < 0 || d2 < 0 || mult < 0 || toler < 0) {
        puts("Invalid colour entered for one or more bands.");
        return;}
    double resistance = (10.0 * d1 + d2) * mult;
    printf("\nResistance=%.2f ohms ±%.2f%%\n",resistance, toler);

    {
        char to_save[200];
        snprintf(to_save, sizeof to_save, "4-band: %.2f ohms ±%.2f%%", resistance, toler);
        save_last_resistor(to_save);
    }
}


//menu option 2 is a 5-band resistor
void menu_item_2(void) {

    char b1[32], b2[32], b3[32], b4[32], b5[32];
    puts("\n>> 5-Band Resistor Decoder");
    puts("Valid digit colours: black|brown|red|orange|yellow|green|blue|violet|grey|white");
    puts("Valid multiplier colours: All the above + gold|silver");
    puts("Valid tolerance colours: brown|red|green|blue|violet|grey|gold|silver");
    
    read_colour(b1, sizeof b1, "Band 1 (digit): ");
    read_colour(b2, sizeof b2, "Band 2 (digit): ");
    read_colour(b3, sizeof b3,"Band 3 (digit): ");
    read_colour(b4, sizeof b4, "Band 4 (multiplier): ");
    read_colour(b5, sizeof b5, "Band 5 (tolerance): ");

    int d1 = digit_value(b1);
    int d2 = digit_value(b2);
    int d3 = digit_value(b3);
    double mult = multiplier_value(b4);
    double toler = tolerance_value(b5);

    if (d1 < 0 || d2 < 0 || d3 < 0 || mult < 0 || toler < 0) {
        puts("Invalid colour entered for one or more bands.");
        return;}
        double resistance = (100.0 * d1 + 10.0 * d2 + d3) * mult;
        printf("\nResistance = %.2f ohms ±%.2f%%\n", resistance, toler);

        {
        char to_save[200];
        snprintf(to_save, sizeof to_save, "5-band: %.2f ohms ±%.2f%%", resistance, toler);
        save_last_resistor(to_save);
    }}


//menu option 3 is to display the last decoded resistor
void menu_item_3(void) {
    char line[256];
    puts("\n>> Last Decoded Resistor");
    if (load_last_resistor(line, sizeof line) != 0 || line[0] == '\0') {
        puts("No resistor saved yet. Decode one first.");
    } else {
        printf("%s\n", line);}
    }
    
//menu option 4 is exit    
void menu_item_4(void) {
    {
    puts("\nExiting program......");
    exit(0);
}
} 