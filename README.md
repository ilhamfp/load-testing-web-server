# load-testing-web-server
Load testing various simple web server.


## Testing Apache Web Server
The test was done in Ubuntu 18.04 with Apache/2.4.29 using [Apache Benchmark]([https://www.tutorialspoint.com/apache_bench/apache_bench_environment_setup.htm].(https://www.tutorialspoint.com/apache_bench/apache_bench_environment_setup.htm))  

Preparation step:
1.  Move the html load test file to `/var/www/html/`
	```
	$ sudo cp resource/500.html /var/www/html/
	$ sudo cp resource/20000.html /var/www/html/
	```

2. Increase max opened files limit in `/etc/security/limits.conf`
	```
	$ sudo cp resource/limits.conf /etc/security/
	$ ulimit -n 20000
	```
### Results
#### 500 bytes file: 
Command: `ab -n 10000 -c 10000 http://127.0.0.1/500.html`
Output:
```
This is ApacheBench, Version 2.3 <$Revision: 1807734 $>
Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
Licensed to The Apache Software Foundation, http://www.apache.org/

Benchmarking 127.0.0.1 (be patient)
Completed 1000 requests
Completed 2000 requests
Completed 3000 requests
Completed 4000 requests
Completed 5000 requests
Completed 6000 requests
Completed 7000 requests
Completed 8000 requests
Completed 9000 requests
Completed 10000 requests
Finished 10000 requests


Server Software:        Apache/2.4.29
Server Hostname:        127.0.0.1
Server Port:            80

Document Path:          /500.html
Document Length:        500 bytes

Concurrency Level:      10000
Time taken for tests:   21.112 seconds
Complete requests:      10000
Failed requests:        4
   (Connect: 0, Receive: 0, Length: 4, Exceptions: 0)
Total transferred:      7706916 bytes
HTML transferred:       4998000 bytes
Requests per second:    473.67 [#/sec] (mean)
Time per request:       21111.871 [ms] (mean)
Time per request:       2.111 [ms] (mean, across all concurrent requests)
Transfer rate:          356.50 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0   57 222.6      0    1038
Processing:     2  766 3031.4     11   21024
Waiting:        0  757 3006.2     11   13726
Total:          9  823 3241.2     11   21024

Percentage of the requests served within a certain time (ms)
  50%     11
  66%     12
  75%     12
  80%     12
  90%     14
  95%   8844
  98%  14733
  99%  14737
 100%  21024 (longest request)
 ```
 
#### 20000 bytes file
Command: `ab -n 10000 -c 10000 http://127.0.0.1/20000.html`
```
This is ApacheBench, Version 2.3 <$Revision: 1807734 $>
Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
Licensed to The Apache Software Foundation, http://www.apache.org/

Benchmarking 127.0.0.1 (be patient)
Completed 1000 requests
Completed 2000 requests
Completed 3000 requests
Completed 4000 requests
Completed 5000 requests
Completed 6000 requests
Completed 7000 requests
Completed 8000 requests
Completed 9000 requests
Completed 10000 requests
Finished 10000 requests


Server Software:        Apache/2.4.29
Server Hostname:        127.0.0.1
Server Port:            80

Document Path:          /20000.html
Document Length:        20000 bytes

Concurrency Level:      10000
Time taken for tests:   51.668 seconds
Complete requests:      10000
Failed requests:        294
   (Connect: 0, Receive: 0, Length: 294, Exceptions: 0)
Total transferred:      197225472 bytes
HTML transferred:       194560000 bytes
Requests per second:    193.55 [#/sec] (mean)
Time per request:       51667.564 [ms] (mean)
Time per request:       5.167 [ms] (mean, across all concurrent requests)
Transfer rate:          3727.74 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0   55 220.4      0    1043
Processing:     3 2354 8253.6     12   51460
Waiting:        0 1406 5967.8     11   28473
Total:         10 2409 8398.9     12   51460

Percentage of the requests served within a certain time (ms)
  50%     12
  66%     13
  75%     13
  80%     13
  90%     23
  95%  27484
  98%  28763
  99%  43213
 100%  51460 (longest request)
 ```
