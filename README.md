# Multi-Container Runtime (OS Jackfruit) ## 📌 Overview This project implements a lightweight container runtime using Linux namespaces, process isolation, and a supervisor-client architecture. It supports multiple containers, logging, monitoring, and scheduling experiments. --- ## ⚙️ Build & Run
bash
git clone <your-repo-link>
cd OS-Jackfruit/boilerplate
make
Start supervisor:
bash
sudo ./engine supervisor ./rootfs-base
--- ## 📷 Demo Screenshots & Tasks --- ### 🔹 Task 1 — Multi-Container Supervision Two containers (alpha, beta) are started and managed by a single supervisor.
bash
sudo ./engine start alpha ./rootfs-alpha /bin/sh
sudo ./engine start beta ./rootfs-beta /bin/sh
 ### 🔹 Task 2 — Metadata Tracking Displays container metadata such as ID and PID.
bash
sudo ./engine ps
### 🔹 Task 3 — Bounded-Buffer Logging Logs container output using pipe + bounded buffer.
bash
sudo touch alpha.log beta.log
sudo chmod 777 alpha.log beta.log

sudo ./engine start alpha ./rootfs-alpha /bin/sh | tee alpha.log
sudo ./engine start beta ./rootfs-beta /bin/sh | tee beta.log
 ### 🔹 Task 4 — CLI and IPC Client sends commands to supervisor via UNIX socket.
bash
sudo ./engine ps
sudo ./engine stop alpha
### 🔹 Task 5 — Soft-Limit Warning Kernel module logs warning when memory crosses soft limit.
bash
sudo sysctl -w kernel.dmesg_restrict=0
sudo insmod monitor.ko
 ### 🔹 Task 6 — Hard-Limit Enforcement Container is killed when memory exceeds hard limit.
bash
sudo ./engine start alpha ./rootfs-alpha ./memory_hog
dmesg | tail
### 🔹 Task 7 — Scheduling Experiment Different nice values affect CPU allocation.
bash
sudo ./engine start alpha ./rootfs-alpha ./cpu_hog
sudo ./engine start beta ./rootfs-beta ./io_pulse
 ### 🔹 Task 8 — Clean Teardown All containers are stopped and checked for zombie processes.
bash
sudo ./engine stop alpha
sudo ./engine stop beta
ps aux | grep defunct
