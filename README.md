# 🚀 BareMetalOS - A Minimalist System Execution Environment
### **Low-Level System Calls | ELF Loader | Context Switching | Process Execution**

![OS](https://img.shields.io/badge/OS-Linux-blue) ![Arch](https://img.shields.io/badge/Arch-x86_64-orange) ![Lang](https://img.shields.io/badge/Language-C%20&%20Assembly-red)  

---

## 📌 Overview
This project implements a **minimalist system execution environment**, focusing on **direct system calls, ELF file loading, and manual context switching**. It demonstrates how modern operating systems invoke system calls, manage processes, and switch execution contexts without relying on standard libraries.

The project is built in **C and GNU Assembly (AT&T syntax)** and operates on **x86_64 Linux**, making it a perfect learning experience for low-level systems programming.

---

## 🔧 Features
- **Raw System Calls**: Implements `read()`, `write()`, and `exit()` without the standard C library.  
- **ELF File Loader**: Parses and loads executable binaries into memory.  
- **Minimalist Shell**: Reads user input and executes micro-programs in a controlled environment.  
- **Manual Context Switching**: Implements basic threading using direct stack manipulation and function pointers.  
- **Process Execution**: Simulates a microkernel-style execution model for user-defined programs.  

---
