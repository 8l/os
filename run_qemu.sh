ISO=${ISO-out/grub.iso}
make -j4 || exit $?
VGA="-vga std"
NETDEV="user,id=vmnet0 -redir tcp:5555::80"
#NETDEV=${NETDEV-tap,id=vmnet0,script=no,ifname=tap0,downscript=no}
${KVM-kvm} -m 32M $VGA "$@" -cdrom $ISO -netdev $NETDEV -device e1000,netdev=vmnet0
