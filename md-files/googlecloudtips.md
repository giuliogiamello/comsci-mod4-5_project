## Google Cloud tips

> [!WARNING]
> Always remember to shut down the virtual machine on Google Cloud to not waste money!

> **Contents** </br>
> - [VM setup](https://github.com/giuliogiamello/comsci-mod4-5_project/blob/main/md-files/googlecloudtips.md#vm-setup)
> - [ssh generation](https://github.com/giuliogiamello/comsci-mod4-5_project/blob/main/md-files/googlecloudtips.md#ssh-generation)
> - [ssh on Google Cloud](https://github.com/giuliogiamello/comsci-mod4-5_project/blob/main/md-files/googlecloudtips.md#ssh-on-google-cloud)

---
### VM setup
---

- name: `<CHOOSE A NAME>`
- OS: `Rocky Linux 9 optimized for GCP (X86/64, x86_64 built on 20251113)`

Set sudo and user password.
For sudo,

- `sudo -i`
- `passwd`
- enter the new password
- then exit root user: `exit`

For user,

- `sudo passwd <username>`
- enter the new password

---
### ssh setup
---

#### ssh generation

From my laptop I generated a ssh-key with: 

```bash
ssh-keygen -t ed25519 -f ~/.ssh/<NAME OF YOUR SSH KEY> -C $USER
```

- it will ask you to enter a password (if you leave it empty, no password is set)

Now you should have in `~/.ssh/`, two files:

- `<NAME OF YOUR SSH KEY>`, your **private** key (never tell to anyone!)
- `<NAME OF YOUR SSH KEY>.pub`, you public key (the one to be shared)

#### ssh on Google Cloud

Then, in order to add your ssh to Google Cloud, you can proceed in two ways:

1. Add the ssh to the whole project: so you will be able to connect to all the VMs in that project
2. Add the ssh to a specific VM

---

1. <b>Whole project</b>

- From Google Cloud Platform, go into `Settings` and `Metadata`.
- Here go into `SSH Keys` and `Add SSH key`.

Then print (from your laptop) your public key with `cat .ssh/<NAME OF YOUR SSH KEY>.pub` and copy the whole output and put in the Google Cloud Platform `SSH key 1` slot.

---

2. <b>Specific VM</b>

From the Google Cloud computing page,

- so from `https://console.cloud.google.com/welcome?project=<YOUR PROJECT NAME>`
- in the "Quick access" menu --> click on "Computer Engine"
- then, in the left panel, under the "Virtual machines" foldable section --> click on "VM instances".
- click on the name of the VM
- click on "Edit" in top center left
- scroll down to the "Security and access" section
- click on "+ Add item"
- paste your public ssh-key (meaning, the output of `cat .ssh/<NAME OF YOUR SSH KEY>.pub`)
- click on "Save" in the bottom left panel

---

**Now you can connect by `ssh` with:**

```bash
ssh -i <path to your private key on your laptop> <username on your laptop>@<external ip of the remote machine>
```

- It will ask you the password you chose when generating the `ssh-key`.

Done! :)
