# Chameleon 

## installation for Ubuntu 16.04


First,
```shell
# Update the packages.
$ sudo apt-get update

# install cmake
$ sudo apt-get install -y cmake 

# Install a few utility tools.
$ sudo apt-get install -y tar wget git

# Install autotools
$ sudo apt-get install -y autoconf libtool automake

# Install the dependencies for libprocess.
$ sudo apt-get -y install build-essential libcurl4-nss-dev libsasl2-dev libsasl2-modules  libapr1-dev libsvn-dev zlib1g-dev iputils-ping
# Install the dependencies for hardware resources collection
$ sudo apt-get -y install dmidecode lshw hdparm cpuid
```

Second,
```shell
# How to run the program

#submitter
$.example
  ./submitter  --minfo=172.20.110.228:6060  --port=6062 --path=/home/XXX/spark-2.3.0-bin-hadoop2.7.tgz

$.explain
  --port      the port used by the program 
  --minfo     the master ip and port,example:127.0.0.1:8080 
  --path      the path where the spark package exists


#slave
$.example
 ./slave  --minfo=172.20.110.228:6060 --port=6061

$.explain
 --port      the port used by the program 
 --minfo     the master ip and port,example:127.0.0.1:8080

#master
$.example
 ./master --port=6060

$.explain
  --port     the port used by the program

