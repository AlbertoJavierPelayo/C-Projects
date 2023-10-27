
unsigned char secuencia=0;
unsigned char arreglo[4]={0x0000000E, 0x0000000D, 0x0000000B, 0x00000007};
unsigned char temp;
unsigned char valor=0;
unsigned char numero_recibido=0;


void UART0_IRQHandler()
{
	temp=UART0_D;
	if ((temp>='0') && (temp<='9')) valor=valor*10+temp-0x30;
	
	if ((temp==0x0D) && (valor>=0) && (valor<=100))
	{
		PIT_LDVAL0=(valor*100000)/25; //Configuración ms contra referencia de 250 nanosegundos (500 ms)
		numero_recibido=1;
		valor=0;
	}
	
				
}


void PIT_IRQHandler()		//ISR PIT Settings
{
	if (PIT_TFLG0==1)				//Checar qué PIT está en funcionamiento
		{
			PIT_TFLG0=1;				//Apagar bandera
			//Lo que quiero que haga mi código
			GPIOB_PDOR=arreglo[secuencia++%4];	//Configuración de lógica de salida
		}	
}


void clk_init (void)
{
	//Configuración de reloj para 4 MHz (código dado)
	MCG_C1|=(1<<6) + (1<<1);
	MCG_C2|=1;
	MCG_SC=0;
	SIM_CLKDIV1=0;
	SIM_SOPT2|=15<<24;
	
}


int main (void)
{
	clk_init();
	//Habilitación relojes de interfaz
	SIM_SCGC6|=(1<<23);			//Habilitar reloj de interfaz del modulo PIT | pag 207
	SIM_SCGC5=(1<<10)+(1<<9); 	//Habilitar Reloj 206
	SIM_SCGC4=(1<<10);			//Habilita reloj de interfaz de UART0

	//Configuración de función de puertos
	PORTB_PCR0=(1<<8);     	//Habilitar Función de Puerto (GPIO) 183
	PORTB_PCR1=(1<<8);		//Estos 4 puertos están configurados como salidas
	PORTB_PCR2=(1<<8);
	PORTB_PCR3=(1<<8);
	
	PORTA_PCR1=(2<<8);		//Configura pin A para Recepción
	PORTA_PCR2=(2<<8);		//Configura pin A para Transmisión
	
	// PORTE_PCR30=(1<<8);			//Este puerto está configurado como entrada
	
	GPIOB_PDDR=(1<<0)+(1<<1)+(1<<2)+(1<<3);		//Configuración de Pin para Salida (GPIO) 778
	
	UART0_BDL=26;		//Configura Baud Rate a 9600 bps
	
	
	
	//Configuración Pit
	PIT_MCR=0;					//Habilita los PITS | pag 576
	PIT_TCTRL0=3;				//Habilita interrupciones y timer | pag 579
	
	
	UART0_S1|=0x1F;		//Limpiar valor de UART para transmisión (dado)
		do{
			UART0_S1|=0x1F;
			if ((UART0_S1 & (1<<5))!=0) temp=UART0_D;
		}while ((UART0_S1)!=0xC0);
	
	//espacio	
	
	NVIC_ISER=(1<<12);		//Configuración de interrupción de UART
	UART0_C2=(1<<2)+(1<<5);	//Configura UART para transmisión e interrupción
	NVIC_ISER=(1<<22);		//Habilitador de interrupción de PIT | pag 53
	
	valor=0;
	while(1)
	{
	}
	return 0;

}
	