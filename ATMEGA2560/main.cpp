/*===================================================================
 Формирование сигнала ШИМ с коэффициентом заполнения N% 
====================================================================*/

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#define F_CPU 16000000UL
#define TOP 1023 			//Величина амплитуды (значение счетного регистра) (10bit = 1023; 9bit = 511; 8bit = 255;)

float Y =0; 				// переменная, чтоб смотреть значение OCR1A при отладке
const float Percent = 100.0;		// 100% константа
char X =0; 				// переменная хранящая значение порта H

int main(){  
   /* Порт H для подключения dip switch */
   DDRH  = 0b00000000;
   PORTH = 0b11111111; 
    
   /* Настройка ШИМа */
   TCCR1A |=  (1<<COM1A1); 		//включили ШИМ
   TCCR1A &= ~(1<<COM1A0); 		//включили ШИМ
 
   /* Тип ШИМа (ШИМ с точной фазой) */
   TCCR1A |=  (1<<WGM10); 		//PWM, Phase Correct, 10-bit
   TCCR1A |=  (1<<WGM11); 		//PWM, Phase Correct, 10-bit
   TCCR1B &= ~(1<<WGM12); 		//PWM, Phase Correct, 10-bit
   TCCR1B &= ~(1<<WGM13); 		//PWM, Phase Correct, 10-bit
 
   /* Предделитель основной частоты МК */
   TCCR1B &= ~(1<<CS10); //8bit;*** 1bit=1; 64bit=1; 256bit=0; 1024bit=1; External  on falling edge =0; External on rising edge =1
   TCCR1B |=  (1<<CS11); //8bit; ***1bit=0; 64bit=1; 256bit=0; 1024bit=0; External  on falling edge =1; External on rising edge =1
   TCCR1B &= ~(1<<CS12); //8bit; *** 1bit=0; 64bit=0; 256bit=1; 1024bit=1; External  on falling edge =1; External on rising edge =1
     
   /* Настроим вывод 5 на шим */
   DDRB |= (1<<PORTB5);
 
   while(1){
      X =~PINH;
      Y = OCR1A = (X/Percent)*TOP; // Регистр сравнения. Опорное напряжение
   }
   
   return 0;
}
 