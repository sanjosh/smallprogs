# download and untar zookeeper 
http://zookeeper.apache.org/releases.html#download
tar xvf zookeeper-3.4.9.tar.gz

# create config file to be used by zkCreate
cat > conf/zoo.cfg
tickTime=2000
dataDir=/home/sandeep/zookeeper
clientPort=2181

# run zookeeper
bin/zkCreate.sh start

# start client
bin/zkCli.sh -server localhost:2181

# install C library to build zookeeper client
sudo apt install libzookeeper-mt-dev

# run C program
cmake .
./locker


