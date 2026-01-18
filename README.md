# comsci-mod4-5_project
> Project for the exam of "Computer Science for High-Energy Physics" 2025/2026, University of Bologna.
> - https://github.com/giacomini/cshep2025/

---

Project of: [Giulio Giamello](https://github.com/giuliogiamello), [Andrea Kutufà](https://github.com/andreakutufa), [Veronica Mungai](https://github.com/vero-dav-vero).

---

> [!NOTE]
> _"We chose to use grain values corresponding to all integers less than or equal to 800 that divide 800 evenly. All other grain values produce the same grid spacing, as the grid relies on integer values."_ </br>
> {1, 2, 4, 5, 8, 10, 16, 20, 25, 32, 40, 50, 80, 100, 160, 200, 400, 800}

- The code is [`containers/IMAPP25/main_par.cpp`](https://github.com/giuliogiamello/comsci-mod4-5_project/blob/main/containers/IMAPP25/main_par.cpp)
- The executable (_release mode_) is [`containers/IMAPP25/build-o/mandelbrot_par`](https://github.com/giuliogiamello/comsci-mod4-5_project/blob/main/containers/IMAPP25/build-o/mandelbrot_par) 
- The image of the Mandelbrot set in PNG format is [`containers/IMAPP25/output/mandelbrot.png`](https://github.com/giuliogiamello/comsci-mod4-5_project/blob/main/containers/IMAPP25/output/mandelbrot.png)
- The text file with three columns: the grain size, the execution time obtained with that grain size and the number of tasks is [`containers/IMAPP25/output/results.txt`](https://github.com/giuliogiamello/comsci-mod4-5_project/blob/main/containers/IMAPP25/output/results.txt)
- In [`containers/IMAPP25/output`](https://github.com/giuliogiamello/comsci-mod4-5_project/tree/main/containers/IMAPP25/output) there are the grid PNG images, named `grid_grain_k.png`, where k=grain
- In [`containers/IMAPP25/plots`](https://github.com/giuliogiamello/comsci-mod4-5_project/tree/main/containers/IMAPP25/plots) there are the plots of "Time VS Grain" and "Tasks VS Grain". The plots have been produced in Python (with matplotplib and pandas), the code is [`containers/IMAPP25/plots/mandelbrot_par.ipynbp`](https://github.com/giuliogiamello/comsci-mod4-5_project/tree/main/containers/IMAPP25/plots/mandelbrot_par.ipynb) 

Click on the section titles below to open them.

## [Project description](https://github.com/giuliogiamello/comsci-mod4-5_project/blob/main/md-files/projectdescription.md)

## [Daily notes](https://github.com/giuliogiamello/comsci-mod4-5_project/blob/main/md-files/dailynotes.md)

## [Google Cloud tips](https://github.com/giuliogiamello/comsci-mod4-5_project/blob/main/md-files/googlecloudtips.md)

## System info

<details>
<summary>
  <tt><b>cat /etc/os-release</b></tt>
</summary>


```bash 
NAME="Rocky Linux"
VERSION="9.7 (Blue Onyx)"
ID="rocky"
ID_LIKE="rhel centos fedora"
VERSION_ID="9.7"
PLATFORM_ID="platform:el9"
PRETTY_NAME="Rocky Linux 9.7 (Blue Onyx)"
ANSI_COLOR="0;32"
LOGO="fedora-logo-icon"
CPE_NAME="cpe:/o:rocky:rocky:9::baseos"
HOME_URL="https://rockylinux.org/"
VENDOR_NAME="RESF"
VENDOR_URL="https://resf.org/"
BUG_REPORT_URL="https://bugs.rockylinux.org/"
SUPPORT_END="2032-05-31"
ROCKY_SUPPORT_PRODUCT="Rocky-Linux-9"
ROCKY_SUPPORT_PRODUCT_VERSION="9.7"
REDHAT_SUPPORT_PRODUCT="Rocky Linux"
REDHAT_SUPPORT_PRODUCT_VERSION="9.7"
```

</details>

---

<details>
<summary>
  <tt><b>lscpu</b></tt>
</summary>


```bash 
Architecture:                x86_64
  CPU op-mode(s):            32-bit, 64-bit
  Address sizes:             46 bits physical, 48 bits virtual
  Byte Order:                Little Endian
CPU(s):                      2
  On-line CPU(s) list:       0,1
Vendor ID:                   GenuineIntel
  Model name:                Intel(R) Xeon(R) CPU @ 2.20GHz
    CPU family:              6
    Model:                   79
    Thread(s) per core:      2
    Core(s) per socket:      1
    Socket(s):               1
    Stepping:                0
    BogoMIPS:                4400.36
    Flags:                   fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush mm
                             x fxsr sse sse2 ss ht syscall nx pdpe1gb rdtscp lm constant_tsc rep_good nopl xtop
                             ology nonstop_tsc cpuid tsc_known_freq pni pclmulqdq ssse3 fma cx16 pcid sse4_1 ss
                             e4_2 x2apic movbe popcnt aes xsave avx f16c rdrand hypervisor lahf_lm abm 3dnowpre
                             fetch pti ssbd ibrs ibpb stibp fsgsbase tsc_adjust bmi1 hle avx2 smep bmi2 erms in
                             vpcid rtm rdseed adx smap xsaveopt arat md_clear arch_capabilities
Virtualization features:     
  Hypervisor vendor:         KVM
  Virtualization type:       full
Caches (sum of all):         
  L1d:                       32 KiB (1 instance)
  L1i:                       32 KiB (1 instance)
  L2:                        256 KiB (1 instance)
  L3:                        55 MiB (1 instance)
NUMA:                        
  NUMA node(s):              1
  NUMA node0 CPU(s):         0,1
Vulnerabilities:             
  Gather data sampling:      Not affected
  Indirect target selection: Mitigation; Aligned branch/return thunks
  Itlb multihit:             Not affected
  L1tf:                      Mitigation; PTE Inversion
  Mds:                       Mitigation; Clear CPU buffers; SMT Host state unknown
  Meltdown:                  Mitigation; PTI
  Mmio stale data:           Vulnerable: Clear CPU buffers attempted, no microcode; SMT Host state unknown
  Reg file data sampling:    Not affected
  Retbleed:                  Not affected
  Spec rstack overflow:      Not affected
  Spec store bypass:         Mitigation; Speculative Store Bypass disabled via prctl
  Spectre v1:                Mitigation; usercopy/swapgs barriers and __user pointer sanitization
  Spectre v2:                Mitigation; Retpolines; IBPB conditional; IBRS_FW; STIBP conditional; RSB filling;
                              PBRSB-eIBRS Not affected; BHI Retpoline
  Srbds:                     Not affected
  Tsa:                       Not affected
  Tsx async abort:           Mitigation; Clear CPU buffers; SMT Host state unknown
  Vmscape:                   Not affected
```

</details>

---
