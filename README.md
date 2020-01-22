# esp-idf project

## Structure

	- Project-ESP-IDF/
	            - CMakeLists.txt
	            - sdkconfig
	            - Makefile
	            - components/	-esp_idf_lib_helpers/	                         
	            - main/	- src/	- modules/	
	            			- ota/	
	            			- states/						
					- main.c               		
	   			- html/	
	   			- include/
		   		- server_certs/
	            - build/
	            - example/

## Test
	$ cd /NBIOT-Arduino-master/Project-ESP-IDF
	$ add esp-idf to the path env
	$ idf.py build && idf.py -p /dev/ttyUSB0 -b 115200 flash monitor

## WEB SERVER
	$ Go to the ip: 192.168.4.1
<img src="./example/example.jpg" align="center" height="400" width="300"><br>
	
	$ Set your own wifi ssid 
	$ Set your own wifi password (if not password leave the blank space)
	$ Press submit button

## Output example

		
		*** MAIN PROGRAM ***
		
		-> wakeup caused: user button
		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
		STATE 1: user button = yes
		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 

		~~~~~~~~~~~~~~~~~
		     AP MODE     
		~~~~~~~~~~~~~~~~~
		-> setting event loop
		-> setting wifi config options
		-> setting mode: AP
		-> starting wifi access point
		-> parameters:
		-> ipv4: 192.168.4.1 
		-> mask: 192.168.4.1 
		-> gw: 192.168.4.1 
		*** OK ***

		~~~~~~~~~~~~~~~~~
		    WEB SERVER   
		~~~~~~~~~~~~~~~~~
		-> setting http default config
		-> setting server on port 80
		-> setting http get method
		-> setting http post method
		*** OK ***
		-> waiting for the user input on web server ***
		-> please go to the web server IP: 192.168.4.1 
		-> waiting...

		-> reading data from web server

		-> data received: 
		 ssid: New_Frontiers 
		 password: none 

		~~~~~~~~~~~~~~~~~
		     STA MODE    
		~~~~~~~~~~~~~~~~~
		-> setting event loop
		-> setting wifi config options
		-> Configuring wifi without user password...
		-> setting mode: STA
		-> starting wifi station mode
		-> connecting to wifi host...
		-> ssid: New_Frontiers 
		-> ipv4: 10.15.61.142
		*** OK ***

		~~~~~~~~~~~~~~~~~
		  INTERNET TIME  
		~~~~~~~~~~~~~~~~~
		-> setting sntp servers
		-> setting sntp server: pool.ntp.org 
		-> setting sntp server: ie.pool.ntp.org 
		-> setting sntp server: pool.ntp.org 
		-> getting time...
		It not was possible update date/time, server: pool.ntp.org is not working!

		datetime epoch format: 1571674679 
		date-time: 2019-10-21 16:17:59 
		check date-time on: https://www.epochconverter.com 
		*** OK ***

		~~~~~~~~~~~~~~~~~
		    DUMMY DATA   
		~~~~~~~~~~~~~~~~~
		-> setting a random number...
		-> random number: 14 
		-> generating json string

		json string: {
			"sensor_id":	"test-idf",
			"properties":	{
				"random_number":	14
			}
		} 

		~~~~~~~~~~~~~~~~~
		  POST TO CLOUD  
		~~~~~~~~~~~~~~~~~

		--- DEBUG SHIT ---
		<!DOCTYPE html><!--


		Symfony\Component\HttpKernel\Exception\MethodNotAllowedHttpException: The GET method is not supported for this route. Supported methods: POST. in file /var/www/html/vendor/laravel/framework/src/Illuminate/Routing/RouteCollection.php on line 256
		Stack tra
		--- DEBUG SHIT ---

		-> url: http://46.22.138.171/api/PostData 
		-> Sending data to cloud
		*** OK ***
		-> cleaning buffer for next data
		*** OK ***

		~~~~~~~~~~~~~~~~~
		TIME FOR DEEPSLEEP
		~~~~~~~~~~~~~~~~~

		datetime epoch format: 1571674732 
		date-time: 2019-10-21 16:18:52 
		check date-time on: https://www.epochconverter.com 
		*** OK ***

		-> actual time epoch format: 1571674732 
		-> time at night epoch format: 1571684400 
		-> difference time in (sec): 9668 
		2 hours - 41 minutes - 8 seconds 

		time is still at the morning, go to sleep for 4 hours 

		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
		STATE 1: END
		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 

		*** Entering deep sleep for 10 seconds ***
		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

## How to compile
	idf.py build && idf.py -p /dev/ttyUSB0 -b 115200 flash monitor
