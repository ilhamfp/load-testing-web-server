# load-testing-web-server
Load testing various simple web server.


## Testing Apache Web Server
The test was done in Ubuntu 18.04 using [Apache Benchmark](https://www.tutorialspoint.com/apache_bench/apache_bench_environment_setup.htm)  

Preparation step:
1.  Move the html load test file to `/var/www/html/`
	```
	$ sudo cp resource/500.html /var/www/html/
	$ sudo cp resource/20000.html /var/www/html/
	```

2. Increase max opened files limit in `/etc/security/limits.conf`
	```
	$ sudo cp resource/limits.conf /etc/security/
  $ sudo -i
	$ ulimit -n 20000
	```

### Results

* Apache/2.4.29 
  * 500 bytes file: 
    * Command: `ab -n 10000 -c 10000 http://127.0.0.1:80/500.html`
    * Output available on result/apache_500.out
  * 20000 bytes file
    * Command: `ab -n 10000 -c 10000 http://127.0.0.1:80/20000.html`
    * Output available on result/apache_20000.out
* Nginx/1.14.0
  * 500 bytes file: 
    * Command: `ab -n 10000 -c 10000 http://127.0.0.1:80/500.html`
    * Output available on result/nginx_500.out
  * 20000 bytes file
    * Command: `ab -n 10000 -c 10000 http://127.0.0.1:80/20000.html`
    * Output available on result/nginx_20000.out
