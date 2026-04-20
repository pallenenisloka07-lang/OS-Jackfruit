# Multi-Container Runtime – Project Guide

---

## Project Summary

In this project, we implemented a simple container runtime using C and Linux system calls. The aim was to understand how multiple containers can be managed using a single supervisor process and how operating system concepts like process isolation, scheduling, and memory management work.

The project has two main parts:
- User-space runtime (engine.c)
- Kernel module (monitor.c)

---

## System Overview

The system consists of a supervisor process and CLI commands.

The supervisor is started once and keeps running. It is responsible for managing containers, tracking their details, and handling user commands.

Command to start supervisor:
```bash
sudo ./engine supervisor ./rootfs-base
```

Commands like start, stop, and ps act as clients and communicate with the supervisor.

---

## Container Creation

Containers are created using the clone() system call with namespace flags:

- CLONE_NEWPID
- CLONE_NEWUTS
- CLONE_NEWNS

This provides isolation for process IDs, hostname, and filesystem.

---

## Filesystem Isolation

Each container uses its own root filesystem such as:
- rootfs-alpha
- rootfs-beta

We used chroot() to restrict the container to its own filesystem.

Inside the container, /proc is mounted so that commands like ps work correctly.

---

## Communication

There are two communication paths:

1. CLI to Supervisor  
   Uses UNIX domain sockets to send commands like start, stop, and ps.

2. Container to Supervisor  
   Uses pipes to send output from containers to the supervisor for logging.

---

## Logging

Container output is captured and stored in log files.

Commands like:
```bash
tee alpha.log
```

are used to save output for later observation.

---

## Memory Monitoring

A kernel module (monitor.ko) is used to observe memory behavior.

Load the module:
```bash
sudo insmod monitor.ko
```

Check logs:
```bash
dmesg | tail
```

Soft limit generates a warning, while hard limit results in terminating the process.

---

## Scheduling

Scheduling behavior was observed using CPU-intensive programs.

It was noticed that different processes get different CPU time depending on scheduling and priority.

---

## Process Management

The supervisor tracks container ID and PID.

It also handles stopping containers and ensures that no zombie processes remain.

