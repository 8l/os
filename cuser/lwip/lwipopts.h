#define NO_SYS 1

// options, options, options!
#define MEMP_OVERFLOW_CHECK 1
#define MEMP_SANITY_CHECK 1
#define LWIP_DHCP 0
#define LWIP_AUTOIP 0
#define LWIP_DNS 1
#define LWIP_NETIF_LOOPBACK_MULTITHREADING 0
#define LWIP_HAVE_LOOPIF 1
//#define LWIP_IPV6 1
#define LWIP_PROVIDE_ERRNO
#define LWIP_SOCKET 0
#define LWIP_NETCONN 0

#define LWIP_DEBUG
#define ETHARP_DEBUG LWIP_DBG_ON
#define AUTOIP_DEBUG LWIP_DBG_ON
#define DHCP_DEBUG   LWIP_DBG_ON
