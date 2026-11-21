# List of the ChibiOS generic i.MX23 startup files.
STARTUPSRC = $(CHIBIOS)/os/common/startup/ARM/compilers/GCC/crt1.c \
             $(CHIBIOS)/os/common/startup/ARM/devices/IMX23/imx23_early.c

STARTUPASM = $(CHIBIOS)/os/common/startup/ARM/compilers/GCC/vectors.S \
             $(CHIBIOS)/os/common/startup/ARM/compilers/GCC/crt0.S

STARTUPINC = $(CHIBIOS)/os/common/portability/GCC \
             ${CHIBIOS}/os/common/startup/ARM/devices/IMX23

STARTUPLD  = ${CHIBIOS}/os/common/startup/ARM/compilers/GCC/ld

# Shared variables
ALLXASMSRC += $(STARTUPASM)
ALLCSRC    += $(STARTUPSRC)
ALLINC     += $(STARTUPINC)
