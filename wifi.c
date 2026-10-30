#include<lpc21xx.h>
#include"header.h"
void wifi_connect(void)
{
uart_string("AT\r\n");
delay_ms(2000);
uart_string("AT+CWMODE=1\r\n");
delay_ms(2000);

uart_string("AT+CWJAP=\"Samsung\",\"91919191\"\r\n");
delay_ms(2000);
uart_string("AT+CIFSR\r\n");
delay_ms(2000);

uart_string("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");
delay_ms(5000);

uart_string("AT+CIPSEND=122\r\n");
delay_ms(2000);


uart_string("GET/ update? api_key=KOKJ86VB538JT2WJ&filed1=50&field2=120&field3=28&filed4=1 HTTP/1.1\r\n");
delay_ms(5000);


uart_string("Host:api.thingspeak.com\r\n\r\n");
delay_ms(5000);
uart_string("Connect:close\r\n\r\n");
delay_ms(8000);
}
void esp_read(void)
{
unsigned char ch;
while(1)
{
ch=uart_rx();
uart_tx(ch);
}
}

