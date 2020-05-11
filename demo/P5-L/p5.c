#include <16F887.h>
#device ADC=8
#fuses INTRC_IO,NOWDT,NOPROTECT,NOLVP, NOMCLR, NOCPD, NOBROWNOUT, NODEBUG, NOLVP, NOIESO, NOFCMEN
#use delay(clock=4000000)

void main(){
	int8 valor; 
	
	setup_ccp1(CCP_PWM);				//Se configura el modulo CCP1 en modo PWM
	setup_ccp2(CCP_PWM);				//Se configura el modulo CCP2 en modo PWM

	setup_timer_2(T2_DIV_BY_16, 250, 1);

	set_pwm1_duty(0);					//Se fija el ciclo de trabajo de 0% en CCP1 y CCP2
	set_pwm2_duty(0);

	setup_adc_ports(sAN0,sAN1);			//Configuración del ADC
	setup_adc(ADC_CLOCK_INTERNAL);

	while( TRUE ){
		//Control de velocidad y sentido del Motor 1
		set_adc_channel(0); 			//Seleccionar AN0 como entrada del ADC
		delay_ms(10);					//Retardo necesario para la conversión
		valor = read_adc();				//Iniciar lectura del ADC

		if(valor > 127){
			valor = (valor-128)*2;		//Calcular el ciclo de trabajo
			set_pwm1_duty(valor);		//Fijar el ciclo del trabajo
			output_high(PIN_C0);		//Girar en sentido horario
			output_low(PIN_C3);
		}else{
			valor*=2;
			valor= 254-valor;			//Calcular el ciclo de trabajo
			set_pwm1_duty(valor);		//Fijar el ciclo del trabajo
			output_low(PIN_C0);		    //Girar en sentido antihorario
			output_high(PIN_C3);
		}	

		//Control de velocidad y sentido del Motor 2
		set_adc_channel(1); 			//Seleccionar AN1 como entrada del ADC
		delay_ms(10);					//Retardo necesario para la conversión
		valor = read_adc();				//Iniciar lectura del ADC
		
		if(valor > 127){
			valor = (valor-128)*2;		//Calcular el ciclo de trabajo
			set_pwm2_duty(valor);		//Fijar el ciclo del trabajo
			output_high(PIN_C4);		//Girar en sentido horario
			output_low(PIN_C5);
		}else{
			valor*=2;
			valor= 254-valor;			//Calcular el ciclo de trabajo
			set_pwm2_duty(valor);		//Fijar el ciclo del trabajo
			output_low(PIN_C4);		//Girar en sentido antihorario
			output_high(PIN_C5);
		}
	}
}