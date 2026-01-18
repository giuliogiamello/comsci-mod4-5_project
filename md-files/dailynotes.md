## Daily notes

> **Contents** </br>
> - [Setting up everything (2026/01/03)](https://github.com/giuliogiamello/comsci-mod4-5_project/blob/main/md-files/dailynotes.md#setting-up-everything-20260103)
> - [Work locally (2026/01/10)](https://github.com/giuliogiamello/comsci-mod4-5_project/blob/main/md-files/dailynotes.md#work-locally-20260110)
> - [VSCode setup (2026/01/10)](https://github.com/giuliogiamello/comsci-mod4-5_project/blob/main/md-files/dailynotes.md#vscode-setup-20260110)
> - [Release version (2026/01/17)](https://github.com/giuliogiamello/comsci-mod4-5_project/blob/main/md-files/dailynotes.md#release-version-20260117)
> - [How to add the professor ssh (2026/01/17)](https://github.com/giuliogiamello/comsci-mod4-5_project/blob/main/md-files/dailynotes.md#how-to-add-the-professor-ssh-20260117)

> [!TIP]
> To see <u>running</u> containers:
> 
> ```bash
> docker ps
> ```
> 
> to see <u>all</u> containers:
> 
> ```bash
> docker ps -a
> ```
>
> to stop a container:
>
> ```bash
> docker stop <CONTAINER ID or NAME>
> ```
> 
> to remove a container:
>
> ```bash
> docker rm -f <CONTAINER ID or NAME>
> ```

---
### Setting up everything (2026/01/03)
---

> [!NOTE]
> **VM creation** </br>
> From `https://console.cloud.google.com/welcome?project=<YOUR PROJECT NAME>`,
> in the "Quick access" menu --> click on "Computer Engine".
> Then, in the left panel, under the "Virtual machines" foldable section --> click on "VM instances".
> Click on the top blue button "Create instance". Here:
> 
> - In the "Machine configuration" section, configure the "Name" of your machine
> - Check that the "Provisioning model" is set to `Standard`
> - Move to the "OS and storage" section, click on "Change" to change the operating system of the VM
> - Select "Operating system": `Rocky Linux`
> - Select "Version": `Rocky Linux 9 optimized for GCP (x86/64, x86_64 built on 20251215)`
> - Select "Size (GB)": `30`
> - Click `Select` to confirm your selection
> 
> Click on the bottom blue button "Create". Done :D 

> [!WARNING]
> **SSH: allow professor access** </br>
> In the instruction "Project description" file (the one in Virtuale) it says:
> 
> Under “SSH keys”, add the following key: `ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIO3dlLZU37NgQofgLnxoQAYS/EnC8XS7BCd5oYGNpIwW chierici@infn.it`
> 
> I won't do that now, but only once the project has been completed.
> So, **REMEMBER to add the professor's SSH!**

> [!NOTE]
> **VM run** </br>
> Run your VM clicking on "SSH" under the "Connect" column in the "VM instances" table.
> A sort of login menu access should appear and after that you should be able to see (and use) the shell of the VM.

> [!TIP]
> **Install and enable Docker** </br>
> From the shell of the VM,
> 
> ```bash title:'# become superuser'
> sudo -i
> ```
> 
> ```bash title:'# installing useful tools'
> dnf -y install nano wget curl git vim
> ```
>
>```bash title:'# install the docker repo'
>curl https://download.docker.com/linux/centos/docker-ce.repo -o /etc/yum.repos.d/docker-ce.repo 
>sed -i -e "s/enabled=1/enabled=0/g" /etc/yum.repos.d/docker-ce.repo
>``` 
>
>```bash title:'# install docker'
>dnf --enablerepo=docker-ce-stable -y install docker-ce
>``` 
>
>```bash title:'# start docker'
>systemctl enable --now docker
>systemctl status docker
>``` 

> [!TIP]
> **Create directory and Docker image** </br>
> 
> ```bash title:'# exit superuser'
> exit
> ```
> 
> Now your `pwd` should be something like: `~`, `/home/<YOUR USERNAME>`.
> 
> ```bash title:'# create the (permanent storage) directory'
> mkdir -p comsci-mod4-5_project/containers/IMAPP25
> ```
> 
> Move to `comsci-mod4-5_project/containers/` and here create the `Dockerfile`
> 
> ```bash
> cd containers/
> ```
> 
> ```bash
> vim Dockerfile
> ```
> 
> The content of the `Dockerfile` is:
> 
> ```docker
> FROM ubuntu:24.04
> ENV DEBIAN_FRONTEND=noninteractive
> RUN apt update && DEBIAN_FRONTEND=noninteractive apt install -y \
> 		build-essential \
> 		g++ \
> 		cmake \
> 		libsfml-dev \
> 		libtbb-dev \
> 		git \
> 		vim \
> 		&& rm -rf /var/lib/apt/lists/*
> WORKDIR /workspace
> CMD ["bash"]
> ```
> 
> `rm -rf /var/lib/apt/lists/*` clean the list of all available software downloaded when running `apt update`,
> `WORKDIR /workspace` set the working folder (the one is opened when running the container).
> 
> Then, from inside `containers/` directory, build the image with:
> 
> ```bash
> sudo docker build -t imapp25-dev .
> ```
> 
> The `.` tells Docker to look for the `Dockerfile` in the current directory.

> [!NOTE]
> **Container run** </br>
> To run your container use the following command:
>
> - you can choose if you want to run the container <u>with the same user you have locally</u>: this allows you to have the same read/write permissions over the files both inside and outside the container. On the other hand, you can't install packages since your are not root user.
>
> ```bash
> docker run -it --rm -u $(id -u):$(id -g) \
> 	-v ~/comsci-mod4-5_project/containers/IMAPP25:/workspace \
> 	--name imapp25-container \
> 	imapp25-dev
> ```
> 
> - if you run the container <u>as root user</u> (e.g. to update/install packages), you won't be able to edit locally the files you created in the container with root user.
> 
> ```bash
> docker run -it --rm \
> 	-v ~/comsci-mod4-5_project/containers/IMAPP25:/workspace \
> 	--name imapp25-container \
> 	imapp25-dev
> ```
> 
> - `imapp25-dev` is the image
> - `imapp25-container` is the container
> - The option `--rm` remove/delete the container every time you exit: so it will clean up all temporary files, while keeping your data stored in `~/containers/IMAPP25`. (It will delete only the container, but not the image; so that you can run again just from the image).
> 
> Use `exit` to leave the container.

---
### Work locally (2026/01/10)
---

Run your VM and then click on the top right button "DOWNLOAD FILE", it will ask to write the path to the file you want to download (in my case: `/home/<YOUR USERNAME>/containers`).

On my PC, I created the folder `comsci-mod4-5_project` and inside that `containers/IMAPP25`, to mirror the same structure of the Google Cloud VM.
Then I moved the downloaded `Dockerfile` inside the `containers` folder and build the image in the same way I explained in "Create directory and Docker image" below.

> [!CAUTION]
If in the building step you get an error like:
>
> ```bash
> ERROR: failed to build: failed to solve: error getting credentials - err: exit status 1, out: `Failed to execute child process “dbus launch” (No such file or directory)`
> ```
> 
> Try to install `dbus-x11`
> 
> ```bash
> sudo apt update && sudo apt install -y dbus-x11
> ```

Then

> [!NOTE]
> **Container run locally** </br>
> To run your container use the following command:
> 
> - you can choose if you want to run the container <u>with the same user you have locally</u>: this allows you to have the same read/write permissions over the files both inside and outside the container. On the other hand, you can't install packages since your are not root user.
> 
> ```bash
> docker run -it --rm -u $(id -u):$(id -g) \
> 	-v "$HOME/giulioDATA/Link to IMAPP-Bologna/IMAPP-03-03_Computer science for High energy physics/comsci-mod4-5/comsci-mod4-5_project/containers/IMAPP25:/workspace" \
> 	--name imapp25-container \
> 	imapp25-dev
> ```
> 
> - if you run the container <u>as root user</u> (e.g. to update/install packages), you won't be able to edit locally the files you created in the container with root user.
> 
> ```bash
> docker run -it --rm \
> 	-v "$HOME/giulioDATA/Link to IMAPP-Bologna/IMAPP-03-03_Computer science for High energy physics/comsci-mod4-5/comsci-mod4-5_project/containers/IMAPP25:/workspace" \
> 	--name imapp25-container \
> 	imapp25-dev
> ```

>[!WARNING]
> NOTE: if you want to install a package in the container, you have to `apt update` before <u>every time</u>, because in the `Dockerfile` is explicitly set `rm -rf /var/lib/apt/lists/*` to delete the "index" of all available packages. 

Once the project has been completed,

> [!IMPORTANT]
> **How to clean your local Docker?** </br>
> Stop running containers (if there are):
> 
> ```bash
> sudo docker stop imapp25-container
> ```
> 
> and remove it:
> 
> ```bash
> sudo docker rm imapp25-container
> ```
> 
> Then remove the images:
> 
> ```bash
> sudo docker rmi imapp25-dev
> ```
> 
> and the one downloaded while building:
> 
> ```bash
> sudo docker rmi ubuntu:24.04
> ```
> 
> Don't forget to remove also your source code from `../comsci-mod4-5_project/containers/IMAPP25`.

---
### VSCode setup (2026/01/10)
---

- Run your container with one of the two previous commands (from "Container run **locally**")
- Install the extension "Dev Containers"
- Then open VSCode and press `Ctrl+Shift+P`
- Type and select: `Dev Containers: Attach to Running Container...`
- VS Code will now open a new window
- It might take a minute the first time to install the "VS Code Server" inside the container
- Look at the bottom left corner of the blue bar. It should say: `>< Container imapp25-dev`

<u>Install Extensions "Inside"</u>

1. Click the Extensions icon (blocks on the left)
2. Search for C++ `ms-vscode.cpptools` (by Microsoft)
3. You will see a blue button that says `Install in Container: imapp25-dev`. Click it.
4. (Repeat, if you need, for CMake `twxs.cmake` and Auto-Save on Window Change `mcright.auto-save` extensions)

(If you hover over `#include <tbb/tbb.h>` now, VS Code will actually find it (because it is looking inside `/usr/include` of the container). If you were just editing locally without attaching, VS Code would show red errors saying "Cannot find TBB" because TBB isn't installed on your main computer).

<u>How to build & run</u>

- In VSCode, open the integrated terminal
- This terminal is already inside the container, so run your build commands directly here:

```bash
cmake -S . -B build-d -DCMAKE_BUILD_TYPE=Debug
cmake --build build-d
./build-d/mandelbrot_par
```

---
### Release version (2026/01/17)
---

Once the code has been completed and it's ready to be released,

- from inside `workspace` (in the container)

```bash
cmake -S . -B build-o -DCMAKE_BUILD_TYPE=Release
cmake --build build-o
```

- then exit the container with `exit` or `Ctrl + d`
- from inside `containers` (out of the container)

```bash
sudo vim Dockerfile_release
```

The content of the file `Dockerfile_release` is:

```bash
FROM ubuntu:24.04
ENV DEBIAN_FRONTEND=noninteractive
RUN apt update && DEBIAN_FRONTEND=noninteractive apt install -y \
        libtbb12 \
        libsfml-graphics2.6
WORKDIR /workspace
CMD ["bash"]
```

- Build it (`-t` stands for tag, you can change it)

```bash
sudo docker build -f Dockerfile_release -t imapp25-rel .
```

Then run the new container and test the compiled program inside,

- run the container `imapp25-rel`:

```bash
docker run -it --rm \
	-v ~/comsci-mod4-5_project/containers/IMAPP25:/workspace \
	--name imapp25-container \
	imapp25-rel
```

- run the `mandelbrot_par` executable (in release mode, so from `build-o`):

```bash
./build-o/mandelbrot_par
```

---
### How to add the professor ssh (2026/01/17)
---

From the Google Cloud computing page,

- so from `https://console.cloud.google.com/welcome?project=<YOUR PROJECT NAME>`
- in the "Quick access" menu --> click on "Computer Engine"
- then, in the left panel, under the "Virtual machines" foldable section --> click on "VM instances".
- click on the name of the VM
- click on "Edit" in top center left
- scroll down to the "Security and access" section
- click on "+ Add item"
- paste the professor ssh

```bash
ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIO3dlLZU37NgQofgLnxoQAYS/EnC8XS7BCd5oYGNpIwW chierici@infn.it
```

- click on "Save" in the bottom left panel
- Done :)
