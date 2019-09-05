# Load Testing Web-Server
Load testing various simple web server for IF4031 Pengembangan Aplikasi Terdistribusi.


## Setup
The test was done in Ubuntu 18.04 using [Apache Benchmark](https://www.tutorialspoint.com/apache_bench/apache_bench_environment_setup.htm).

Step:
1. Install [Apache Benchmark](https://www.tutorialspoint.com/apache_bench/apache_bench_environment_setup.htm).

2. Move the html load test file to `/var/www/html/`
	```
	$ sudo cp resource/500.html /var/www/html/
	$ sudo cp resource/20000.html /var/www/html/
	```

3. Increase max opened files limit in `/etc/security/limits.conf` and run the terminal as root
	```
	$ sudo cp resource/limits.conf /etc/security/  
  $ sudo -i  
	$ ulimit -n 20000  
	```

## Results

* Apache/2.4.29 
  Step:
  1. Install [Apache2](https://www.digitalocean.com/community/tutorials/how-to-install-the-apache-web-server-on-ubuntu-18-04-quickstart)
  2. Run it
  ```
  $ sudo service apache2 start
  ```
  * 500 bytes file: 
    * Command: `ab -n 10000 -c 10000 http://127.0.0.1:80/500.html`
    * Output available on result/apache_500.out
  * 20000 bytes file
    * Command: `ab -n 10000 -c 10000 http://127.0.0.1:80/20000.html`
    * Output available on result/apache_20000.out
* Nginx/1.14.0
  Step:
  1. Install [Nginx](https://www.digitalocean.com/community/tutorials/how-to-install-nginx-on-ubuntu-18-04)
  2. Run it
  ```
  $ sudo service nginx start
  ```
  * 500 bytes file: 
    * Command: `ab -n 10000 -c 10000 http://127.0.0.1:80/500.html`
    * Output available on result/nginx_500.out
  * 20000 bytes file
    * Command: `ab -n 10000 -c 10000 http://127.0.0.1:80/20000.html`
    * Output available on result/nginx_20000.out
* socket
  Step:
  1. Navigate to `socket` directory
  ```
  $ cd socket/
  ```
  2. Run make 
  ```
  $ make
  ```
  3. Run socket 
  ```
  $ sudo ./socket
  ```
  * 500 bytes file:
    * Command: `ab -n 10000 -c 10000 http://127.0.0.1:8080/500.html`
    * Output available on result/socket_500.out
  * 20000 bytes file:
    * Command: `ab -n 10000 -c 10000 http://127.0.0.1:8080/20000.html`
    * Failed. Only 8703 requests completed.
* tornado/3.2.1
  Step:
  1. Install tornado
  ```
  $ pip install tornado
  ```
  2. Navigate to `socket` directory
  ```
  $ cd tornado/
  ```
  3. Run index.py 
  ```
  $ python3 index.py
  ```
  * 500 bytes file:
    * Command: `ab -n 10000 -c 10000 http://127.0.0.1:8081/500.html`
    * Output available on result/tornado_500.out
  * 20000 bytes file:
    * Command: `ab -n 10000 -c 10000 http://127.0.0.1:8081/20000.html`
    * Failed. Only 7618 requests completed.
* Node.js/v8.10.0
  Step:
  1. Install [Node.js](https://nodejs.org/en/download/)
  2. Navigate to `node` directory
  ```
  $ cd node/
  ```
  3. Install dependencies
  ```
  $ npm install
  ```
  4. Run index.js
  ```
  $ node index.js
  ```
  * 500 bytes file:
    * Command: `ab -n 10000 -c 10000 http://127.0.0.1:8082/500.html`
    * Output available on result/node_500.out
  * 20000 bytes file:
    * Command: `ab -n 10000 -c 10000 http://127.0.0.1:8082/20000.html`
    * Output available on result/node_20000.out

## Conclusion