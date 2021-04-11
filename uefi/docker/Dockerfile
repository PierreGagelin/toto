FROM debian

RUN apt update && apt install -y \
    #
    # Download and install requirement
    #
    curl \
    unzip \
    # EDK requirements
    build-essential \
    uuid-dev \
    acpica-tools \
    gcc \
    nasm \
    python \
    python3-distutils \
    # QEMU
    qemu-system-x86 \
    #
    && true

CMD ["bash"]
