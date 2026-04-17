Here’s a **clean README.txt** you can directly use for your project 👇



# README – Container Engine Tasks

## Overview

This project demonstrates the working of a custom container engine (`engine.c`) including container creation, supervision, logging, limits, and process management.



# Task 1: Running Containers

* Compiled engine using:

  
  gcc engine.c -o engine

* Started containers:


  sudo ./engine run alpha ./rootfs-alpha /bin/sh
  sudo ./engine run beta ./rootfs-beta /bin/sh
 
* Verified container execution and PID inside namespace.



#  Task 2: Supervisor Mode

* Ran engine in supervisor mode:

  
  sudo ./engine supervisor ./rootfs-base

* Supervisor handles container lifecycle.
* Client commands used:

 
  sudo ./engine start alpha ./rootfs-alpha /bin/sh
  sudo ./engine start beta ./rootfs-beta /bin/sh
  sudo ./engine ps
 
* Output shows running containers and their status.



#  Task 3: Logging

* Enabled logging of container activity.
* Logs stored in:

  
  log.txt
  
* Verified logs using:

  
  cat log.txt
  
* Logs include container start events and PIDs.



#  Task 4: Stopping Containers

* Stopped running container:

  
  sudo ./engine stop alpha
  
* Verified using:


  sudo ./engine ps
  
* Container successfully terminated.



#  Task 5: Soft Limit Handling

* Supervisor enforces soft limits.
* When limit exceeded:

  * Warning message generated
  * Logged in `log.txt`
* Example:

  
  WARNING: alpha exceeded soft limit
 



#  Task 6: Hard Limit Handling

* If container exceeds hard limit:

  * It is forcefully terminated
* Output:

 
  Killed container alpha
  LOG: alpha exceeded hard limit
  



#  Task 7: Process Monitoring

* Checked running processes:

  
  ps -ef | grep sleep
  
* Used `nice` command:

  
  nice -n 10 sleep 1000 &
  
* Verified process priority and execution.



#  Task 8: Killing Processes

* Stopped containers:

 
  sudo ./engine stop alpha
  sudo ./engine stop beta

* Killed background processes:


  kill -9 <PID>
  
* Verified using:

 
  ps aux | grep engine
  ps aux | grep sleep
  


#  Key Concepts Covered

* Container creation & execution
* Namespace isolation
* Supervisor-based management
* Logging mechanism
* Resource limits (soft & hard)
* Process monitoring & control



#  Conclusion

The implementation successfully demonstrates a basic container runtime with process isolation, supervision, logging, and resource control similar to real-world container systems.

