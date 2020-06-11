### Install rustup
sudo apt-get update
sudo apt install build-essential curl wget git libboost-all-dev
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
source $HOME/.cargo/env

### Install Docker

# Update the apt package index and install packages to allow apt to use a repository over HTTPS:
sudo apt-get update
sudo apt-get install -y \
	apt-transport-https \
	ca-certificates \
	gnupg-agent \
	software-properties-common

# Add docker GPG key
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -

# Setup the docker apt repository
sudo add-apt-repository \
	"deb [arch=amd64] https://download.docker.com/linux/ubuntu \
	$(lsb_release -cs) \
	stable" -y

# Install docker engine
sudo apt-get update
sudo apt-get install -y docker-ce docker-ce-cli containerd.io

# Create docker group and add your user
sudo groupadd docker
sudo usermod -aG docker $USER

### Install NodeJS
# Install NVM
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.35.3/install.sh | bash

# Load NVM (Will append to your ~/.bashrc after the above installation)
export NVM_DIR="$([ -z "${XDG_CONFIG_HOME-}" ] && printf %s "${HOME}/.nvm" || printf %s "${XDG_CONFIG_HOME}/nvm")"
[ -s "$NVM_DIR/nvm.sh" ] && \. "$NVM_DIR/nvm.sh"

# Install NodeJS v14.3.0
nvm install v14.3.0
nvm use -g v14.3.0

### Install LLVM 10
# Add LLVM GPG key
curl -fsSL https://apt.llvm.org/llvm-snapshot.gpg.key | sudo apt-key add -
# Add LLVM 10 apt repository
sudo apt-add-repository "deb http://apt.llvm.org/bionic/ llvm-toolchain-bionic-10 main" -y # For Ubuntu 18.04
# sudo apt-add-repository "http://apt.llvm.org/focal/ llvm-toolchain-focal-10 main" # For Ubuntu 20.04

# LLVM
sudo apt install -y libllvm-10-ocaml-dev libllvm10 llvm-10 llvm-10-dev llvm-10-doc llvm-10-examples llvm-10-runtime
# Clang and co
sudo apt install -y clang-10 clang-tools-10 clang-10-doc libclang-common-10-dev libclang-10-dev libclang1-10 clang-format-10 clangd-10
# lld (linker)
sudo apt install -y lld-10 liblld-10-dev
# libc++
sudo apt install -y libc++-10-dev libc++abi-10-dev

### Install boost, and zlib
sudo apt update
sudo apt install -y libboost-dev zlib1g-dev

### Install cmake
wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | \
	gpg --dearmor - | \
	sudo tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null
sudo apt-add-repository 'deb https://apt.kitware.com/ubuntu/ bionic main' -y
sudo apt update
sudo apt install -y cmake

### Install binaryen
mkdir -p thirdpartybin
cd thirdpartybin
wget https://github.com/WebAssembly/binaryen/releases/download/version_93/binaryen-version_93-x86_64-linux.tar.gz
tar zxvf binaryen-version_93-x86_64-linux.tar.gz
cd ..
export PATH=$(pwd)/thirdpartybin/binaryen-version_93:$PATH
