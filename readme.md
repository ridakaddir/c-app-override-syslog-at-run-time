This repo contains two applications to demonstrate the use of LD_PRELOAD to override the syslog method in a simple c app.

## Pre-requisites
- Docker
- Docker dev container
The apps are compiled and run in a docker container. The docker container is based on the debian image and contains the necessary tools to compile and run the apps.

## The Simple app
The simple app is a simple c application that uses syslog to log messages to the syslog server. The app is compiled with the shared library zlog.so to override the syslog method at runtime. The shared library zlog.so intercepts the syslog calls and writes the log messages to the file system using the zlog library.

## The Shared Library
The shared library zlog.so is a shared library that uses the zlog library to write log messages to the file system. The shared library is injected into the simple app at runtime using the LD_PRELOAD environment variable to override the syslog method.

## Install the zlog library
To compile the shared library, you need to install the zlog library. The zlog library is a simple logging library that provides a simple API to write log messages to the file system. The zlog library is used by the shared library to write log messages to the file system. https://github.com/HardySimpson/zlog

1. Download the zlog library from the github repository 
https://github.com/HardySimpson/zlog/releases  

2. Extract and install the zlog library to the /usr/local directory
```
tar -zxvf zlog-latest-stable.tar.gz
cd zlog-latest-stable/
make 
sudo make install
```

3. Refresh the dynamic linker
```
sudo ldconfig
```

## How to compile the apps

1. Compile the simple app
```
gcc src/main.c -o app
```

2. Compile the shared library
```
gcc -fPIC -shared zlog/zlog.c -o zlog.so -L /usr/local/lib -lzlog
```

3. Run the app with the shared library to override the syslog method

The application takes its log configuration from the zlog.conf file. The zlog.conf file is located in `/workspaces/debian/config/zlog.conf`. The zlog.conf file contains the log configuration for the zlog library. The zlog library uses the log configuration to write log messages to the file system.
Make the necessary changes to the location of the zlog.conf file in the zlog/zlog.c file.

```
LD_PRELOAD=./zlog.so ./app
```

you should see the log messages written to the file system in the `/workspaces/debian/logs/simpleapp.log` file.

```
2024-05-01 18:56:12 INFO [42253:zlog/zlog.c:24] zlog initialized
2024-05-01 18:56:12 INFO [42253:zlog/zlog.c:38] Hello 1 from syslog

2024-05-01 18:56:12 INFO [42253:zlog/zlog.c:38] Hello 2 from syslog

2024-05-01 18:56:12 INFO [42253:zlog/zlog.c:30] finishing zlog
```
