# AutO-RekO



```
     _        _____           ____      _     ___  
    / \  _   |_   _|__       |  _ \ ___| | __/ _ \ 
   / _ \| | | || |/ _ \ _____| |_) / _ \ |/ / | | |
  / ___ \ |_| || | (_) |_____|  _ <  __/   <| |_| |
 /_/   \_\__,_||_|\___/      |_| \_\___|_|\_\\___/ 
                                                   
```

**AutO-RekO** is an automatic enumeration tool designed to accelerate and optimize the reconnaissance phase during penetration tests.

---

## ⚙️ Development Status

AutO-RekO is currently under development and will be available soon. Stay tuned for updates!

---

## ✨ Features

- **Automated Enumeration:** Efficient and quick reconnaissance.
- **Customizable Workflows:** Adapt to your specific testing needs.
- **Multi-Platform Support:** Seamless operation across environments.

---


## 🚀 Usage

To use AutO-RekO, follow these examples:

### Basic Enumeration

Run a standard enumeration with the following command:

```bash
autoreko -t <target_ip> -i <intensity_level> -o <output_file>
```

- `-t` specifies the target IP address (IPv4 or IPv6).
- `-i` specifies the intensity level of the scan, ranging from 1 (low) to 4 (high). Note: Intensity levels 2, levels 3 and 4 require `root` privileges.
- `-u` specifies a target URL for enumeration.
- `-o` specifies the output file (e.g., `results.txt`) where the scan results will be saved.

### Advanced Options

Explore additional capabilities and options:

```bash
autoreko -h
```

### Example Usage

Save results to a text file with detailed logging enabled:

```bash
autoreko -t 192.168.1.1 -i 3 -o /home/results.txt 
```

Alternatively, specify a URL:

```bash
autoreko -u https://example.com -i 2 
```

---

## 👥 Authors

This project is developed and maintained by:

- **@Rattus**
- **@BrB93** 

Feel free to reach out for suggestions, bug reports, or contributions!

