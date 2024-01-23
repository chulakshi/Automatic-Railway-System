 // LCD module connections
sbit LCD_RS at RD0_bit;
sbit LCD_EN at RD1_bit;
sbit LCD_D4 at RD2_bit;
sbit LCD_D5 at RD3_bit;
sbit LCD_D6 at RD4_bit;
sbit LCD_D7 at RD5_bit;

sbit LCD_RS_Direction at TRISD0_bit;
sbit LCD_EN_Direction at TRISD1_bit;
sbit LCD_D4_Direction at TRISD2_bit;
sbit LCD_D5_Direction at TRISD3_bit;
sbit LCD_D6_Direction at TRISD4_bit;
sbit LCD_D7_Direction at TRISD5_bit;
// End LCD module connections
int x=0;
int i=0;
char y=11;
unsigned char number1[20];
unsigned char number2[15];
void main() {
TRISC=0X00;
PORTC=0X00;
TRISD.RD6=1;   //sensor 02
TRISD.RD7=1;  //sensor 01
UART1_Init(9600);   // Initialize UART module at 9600 bps
Delay_ms(100);   // Wait for UART module to stabilize
Lcd_Init();      // Initialize LCD
Lcd_Cmd(_LCD_CLEAR);  // Clear display
Lcd_Cmd(_LCD_CURSOR_OFF); // Cursor off
Lcd_Out(1,1,"No Trains"); // Write text in first row
Lcd_Out(2,1," Go Ahead!");// Write text in Second row
PORTC.RC0=0;//Red LED
PORTC.RC1=1;//Green LED
while(1)
                   {
                               if(portd.rd7==0)//sensing firest sensor trains until detect
                                                  {
                               x=0;  
                               portc.rc0=1; //RED LED
                               portc.rc1=0; //GREEN LED

                        UART1_Write_Text("Train Detected ");
                        UART1_Write_Text("Attention Train ");
                        UART1_Write_Text("Near to Crossing ");
                          Delay_ms(1000);
                          Lcd_Init();  // Initialize LCD

                        for(i=10;i>=0;i--)
      {
      Lcd_Cmd(_LCD_CLEAR); // Clear display
      Lcd_Cmd(_LCD_CURSOR_OFF);
      Lcd_Out(1,2,"Time Left =   S");
     y--; 
     byteToStr(y,number1);
        byteToStr(y,number2);
       number1 [1] = 0;
       Lcd_Out(1,13,number1);
         UART1_Write_Text(" Time Left =");
        UART1_Write_Text(number2);
         Delay_ms(1000);
      }
         y=11;
                        PWM1_Init(5000);
                        PWM1_Start();
                        portc.rc3=1;  //rotate left
                        portc.rc4=0;  //rotate left
                        PWM1_Set_Duty(100);//motor speed control by using PWM
                        Lcd_Cmd(_LCD_CLEAR);
                        Lcd_Out(1,1,"Gate Closed");
                        UART1_Write_Text(" Gate Closed ");
                        delay_ms(2000);
                        PWM1_Stop();
                        portc.rc3=0;  //stop the motor
                        portc.rc4=0;  //stop the motor
                               while(x==0){ if(portd.rd6==0)
                                                       {
                                                            x=1;
                                                            portc.rc0=0; //RED LED
                                                            portc.rc1=1; //GREEN LED
                                                            PWM1_Start();
                                                            portc.rc3=0;  //rotate right
                                                            portc.rc4=1;  //rotate right
                                                            PWM1_Set_Duty(100); //motor speed control by using PWM
                                                            Lcd_Cmd(_LCD_CLEAR); // Clear display
                                                            Lcd_Out(1,1,"Gate Opening");
                                                            delay_ms(2000);
                                                            PWM1_Stop();
                                                            portc.rc3=0; //stop the motor
                                                            portc.rc4=0; //stop the motor
                                                            Lcd_Cmd(_LCD_CLEAR);  // Clear display
                                                            Lcd_Out(2,1,"Go Ahead!");// Write text in Second row
                                                        }
                                         }
                                                           }

                    }
}