require recipes-core/images/core-image-base.bb

IMAGE_INSTALL:append = " libstdc++ mtd-utils" 
IMAGE_INSTALL:append = " openssh openssl openssh-sftp-server"
ENABLE_UART = "1"

DISTRO_FEATURES:append = " bluetooth virtualization x11 systemd"

IMAGE_FEATURES:append = " splash package-management x11-base x11-sato hwcodecs"

IMAGE_INSTALL:append = " \
    qtbase \
    qtbase-dev \
    qtbase-mkspecs \
    qtbase-plugins \
    qtbase-tools \
    qt3d \
    qt3d-dev \
    qt3d-mkspecs \
    qtcharts \
    qtcharts-dev \
    qtcharts-mkspecs \
    qtconnectivity-dev \
    qtconnectivity-mkspecs \
    qtquickcontrols2 \
    qtquickcontrols2-dev \
    qtquickcontrols2-mkspecs \
    qtdeclarative \
    qtdeclarative-dev \
    qtdeclarative-mkspecs \
    qtgraphicaleffects \
    qtgraphicaleffects-dev \
    linux-firmware-bcm43430 \
    bluez5 \
    bridge-utils \
    hostapd \
    iptables \
    wpa-supplicant \
    packagegroup-core-x11-sato \
"