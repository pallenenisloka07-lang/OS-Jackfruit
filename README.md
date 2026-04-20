# Multi-Container Runtime

## 1. Team Information

| Name | SRN |
|------|-----|
| PALLENENI SLOKA | PES1UG24AM183 |
| HARSHITHA SAI  | PES1UG24AM182 |

---

## 2. Build, Load, and Run Instructions

### Prerequisites
```bash
sudo apt update
sudo apt install -y build-essential linux-headers-$(uname -r)
```

### Build
```bash
git clone <your-repo-link>
cd OS-Jackfruit/boilerplate
make
```

### Start Supervisor
```bash
sudo ./engine supervisor ./rootfs-base
```

### Run Containers (New Terminal)
```bash
sudo ./engine start alpha ./rootfs-alpha /bin/sh
sudo ./engine start beta ./rootfs-beta /bin/sh
sudo ./engine ps
```

---

## 3. Usage

### Start Container
```bash
sudo ./engine start <id> <rootfs> <command>
```

### List Containers
```bash
sudo ./engine ps
```

### Stop Container
```bash
sudo ./engine stop <id>
```

---

## 4. Summary

- Implemented container runtime using clone()
- Supervisor manages multiple containers
- Logging using bounded buffer
- Kernel module for memory monitoring
- Scheduling behavior tested using CPU workloads

---

## 5. Technologies Used

- C Programming  
- Linux System Calls  
- Kernel Module  
- Namespaces  

---
