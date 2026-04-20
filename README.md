# OS Jackfruit Engine – Tasks Documentation

This repository contains screenshots and execution steps for multiple tasks performed using the custom `engine` tool in the OS Jackfruit boilerplate.

---

## 🔹 Task 2: Metadata Tracking

### Terminal 1
Run supervisor:
```bash
sudo ./engine supervisor ./rootfs-base
```

### Terminal 2
Start containers and check status:
```bash
sudo ./engine start alpha ./rootfs-alpha /bin/sh
sudo ./engine start beta ./rootfs-beta /bin/sh
sudo ./engine ps
```

### Output
- Containers `alpha` and `beta` are started  
- `engine ps` shows running containers  

---

## 🔹 Task 3: Bound Buffer Logging

### Terminal 1
```bash
cd OS-Jackfruit/boilerplate
sudo ./engine supervisor ./rootfs-base
```

### Terminal 2
```bash
cd OS-Jackfruit/boilerplate
sudo touch alpha.log beta.log
sudo chmod 777 alpha.log beta.log

sudo ./engine start alpha ./rootfs-alpha /bin/sh | tee alpha.log
sudo ./engine start beta ./rootfs-beta /bin/sh | tee beta.log

cat alpha.log
cat beta.log
```

### Output
- Logs are written into `alpha.log` and `beta.log`  
- Buffer count increases correctly  

---

## 🔹 Task 4: Start, List, Stop Containers

```bash
cd OS-Jackfruit/boilerplate && \
sudo ./engine start alpha ./rootfs-alpha /bin/sh && \
sudo ./engine start beta ./rootfs-beta /bin/sh && \
sudo ./engine ps && \
sudo ./engine stop alpha
```

### Output
- Containers started successfully  
- `alpha` container stopped  

---

## 🔹 Task 5 & 6: Kernel Monitoring

### Terminal 1
```bash
sudo ./engine supervisor ./rootfs-base
```

### Terminal 2
```bash
sudo sysctl -w kernel.dmesg_restrict=0
sudo insmod monitor.ko

sudo ./engine start alpha ./rootfs-alpha ./memory_hog

dmesg | tail
```

### Output
- Kernel logs show memory limit exceeded  
- Process killed by kernel (OOM condition)  

---

## 🔹 Task 7: CPU Monitoring

```bash
sudo ./engine start alpha ./rootfs-alpha ./cpu_hog
sudo ./engine start beta ./rootfs-beta ./io_pulse
```

### Output
- CPU usage and load average increase observed  

---

## 🔹 Task 8: Process Cleanup (Defunct Processes)

### Terminal 1
```bash
sudo ./engine supervisor ./rootfs-base
```

### Terminal 2
```bash
sudo ./engine start alpha ./rootfs-alpha /bin/sh
sudo ./engine start beta ./rootfs-beta /bin/sh
sudo ./engine stop alpha
sudo ./engine stop beta

ps aux | grep defunct
```

### Output
- Containers stopped successfully  
- Checked for defunct (zombie) processes  

---

## ✅ Summary

- Implemented container lifecycle management using `engine`  
- Verified logging, monitoring, and cleanup  
- Observed kernel-level behaviors (OOM, CPU load)  

---

## 📌 Notes

- Ensure `sudo` privileges are enabled  
- Run supervisor before starting containers  
- Use `dmesg` for kernel debugging  

---

## 📷 Screenshots

Refer to the uploaded images in this repository for execution proof of each task.

---

## 🚀 How to Run

```bash
git clone <your-repo-link>
cd OS-Jackfruit/boilerplate
make
```

Then follow the commands listed in each task.

---

## 👨‍💻 Author

- Your Name  
- Course / Lab Details  
