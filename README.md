
A simple program that monitors the bandwidth usage of a specified process and triggers a command when the bandwidth moves above or below a custom setpoint.

# compile libnethogs

```
git clone https://github.com/raboof/nethogs
cd nethogs/
git checkout 2acedff5d70db070c17772c7c4611cf742199607

sudo apt install build-essential libpcap-dev libncurses-dev
make libnethogs
cd src/
ln -s libnethogs.so.0.8.5-99-g2acedff libnethogs.so
cd ../../

```

# compile bwtrigger

```
make
```

# usage

```
Usage: ./trigger <pid> <bw> <cmd>
  <pid> is the process id of the process to monitor for bandwidth usage
  <bw> is the bandwidth at which to trigger the command in kilobits per second
  <cmd> is the command to run when the bandwidth usage of <pid> rises above
        or drops below <bw>. The argument 'above' or 'below' is given to <cmd>
```

Only the downstream bandwidth is monitored.

The command is run in a shell and the full path to the command must be specified as a single argument.

bwtrigger must be run as root.

# example

```
sudo ./run.sh 2052 100 $(realpath ./test.sh)
```

# ToDo

* Add adjustable hysteresis
