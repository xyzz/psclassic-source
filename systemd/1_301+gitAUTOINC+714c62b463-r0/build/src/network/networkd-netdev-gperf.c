/* ANSI-C code produced by gperf version 3.0.4 */
/* Command-line: gperf  */
/* Computed positions: -k'2,5,8-9,23' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gnu-gperf@gnu.org>."
#endif


#include <stddef.h>
#include "conf-parser.h"
#include "networkd-netdev.h"
#include "networkd-netdev-tunnel.h"
#include "networkd-netdev-bond.h"
#include "networkd-netdev-macvlan.h"
#include "network-internal.h"
#include <string.h>

#define TOTAL_KEYWORDS 74
#define MIN_WORD_LENGTH 7
#define MAX_WORD_LENGTH 27
#define MIN_HASH_VALUE 9
#define MAX_HASH_VALUE 104
/* maximum key range = 96, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
network_netdev_gperf_hash (register const char *str, register unsigned int len)
{
  static const unsigned char asso_values[] =
    {
      105, 105, 105, 105, 105, 105, 105, 105, 105, 105,
      105, 105, 105, 105, 105, 105, 105, 105, 105, 105,
      105, 105, 105, 105, 105, 105, 105, 105, 105, 105,
      105, 105, 105, 105, 105, 105, 105, 105, 105, 105,
      105, 105, 105, 105, 105, 105,   0, 105, 105, 105,
       35,   0, 105, 105, 105, 105, 105, 105, 105, 105,
      105, 105, 105, 105, 105,   5,  40,  35,  20,  35,
       45,  45,  35,   0, 105,   0,  25,   0,   5,  50,
        0,  10,  35,  15,  10,  40,  30, 105,   5, 105,
      105, 105, 105, 105, 105, 105, 105,   5, 105,  30,
       40,   0, 105,   5,  30,  15, 105,  10,  30,   0,
       15,   0,  45, 105,  15,   0,  10,   0, 105,  50,
       45,  35, 105, 105, 105, 105, 105, 105, 105, 105,
      105, 105, 105, 105, 105, 105, 105, 105, 105, 105,
      105, 105, 105, 105, 105, 105, 105, 105, 105, 105,
      105, 105, 105, 105, 105, 105, 105, 105, 105, 105,
      105, 105, 105, 105, 105, 105, 105, 105, 105, 105,
      105, 105, 105, 105, 105, 105, 105, 105, 105, 105,
      105, 105, 105, 105, 105, 105, 105, 105, 105, 105,
      105, 105, 105, 105, 105, 105, 105, 105, 105, 105,
      105, 105, 105, 105, 105, 105, 105, 105, 105, 105,
      105, 105, 105, 105, 105, 105, 105, 105, 105, 105,
      105, 105, 105, 105, 105, 105, 105, 105, 105, 105,
      105, 105, 105, 105, 105, 105, 105, 105, 105, 105,
      105, 105, 105, 105, 105, 105, 105, 105, 105, 105,
      105, 105, 105, 105, 105, 105
    };
  register int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[22]];
      /*FALLTHROUGH*/
      case 22:
      case 21:
      case 20:
      case 19:
      case 18:
      case 17:
      case 16:
      case 15:
      case 14:
      case 13:
      case 12:
      case 11:
      case 10:
      case 9:
        hval += asso_values[(unsigned char)str[8]];
      /*FALLTHROUGH*/
      case 8:
        hval += asso_values[(unsigned char)str[7]];
      /*FALLTHROUGH*/
      case 7:
      case 6:
      case 5:
        hval += asso_values[(unsigned char)str[4]];
      /*FALLTHROUGH*/
      case 4:
      case 3:
      case 2:
        hval += asso_values[(unsigned char)str[1]];
        break;
    }
  return hval;
}

#ifdef __GNUC__
__inline
#if defined __GNUC_STDC_INLINE__ || defined __GNUC_GNU_INLINE__
__attribute__ ((__gnu_inline__))
#endif
#endif
const struct ConfigPerfItem *
network_netdev_gperf_lookup (register const char *str, register unsigned int len)
{
  static const struct ConfigPerfItem wordlist[] =
    {
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
      {"Peer.Name",                   config_parse_ifname,                0,                             offsetof(Veth, ifname_peer)},
      {(char*)0},
      {"Tunnel.Mode",                 config_parse_ip6tnl_mode,           0,                             offsetof(Tunnel, ip6tnl_mode)},
      {(char*)0}, {(char*)0}, {(char*)0},
      {"Bond.ResendIGMP",             config_parse_unsigned,              0,                             offsetof(Bond, resend_igmp)},
      {"IPVLAN.Mode",                 config_parse_ipvlan_mode,           0,                             offsetof(IPVlan, mode)},
      {"Bond.ARPIPTargets",           config_parse_arp_ip_target_address, 0,                             0},
      {"Bond.MIIMonitorSec",          config_parse_sec,                   0,                             offsetof(Bond, miimon)},
      {"Bond.ARPIntervalSec",         config_parse_sec,                   0,                             offsetof(Bond, arp_interval)},
      {"Tunnel.IPv6FlowLabel",        config_parse_ipv6_flowlabel,        0,                             offsetof(Tunnel, ipv6_flowlabel)},
      {"NetDev.Name",                 config_parse_ifname,                0,                             offsetof(NetDev, ifname)},
      {"NetDev.MACAddress",           config_parse_hwaddr,                0,                             offsetof(NetDev, mac)},
      {"Bond.ARPAllTargets",          config_parse_bond_arp_all_targets,  0,                             offsetof(Bond, arp_all_targets)},
      {"Tun.PacketInfo",              config_parse_bool,                  0,                             offsetof(TunTap, packet_info)},
      {"NetDev.MTUBytes",             config_parse_iec_size,              0,                             offsetof(NetDev, mtu)},
      {"NetDev.Kind",                 config_parse_netdev_kind,           0,                             offsetof(NetDev, kind)},
      {"MACVTAP.Mode",                config_parse_macvlan_mode,          0,                             offsetof(MacVlan, mode)},
      {"Bond.AdSelect",               config_parse_bond_ad_select,        0,                             offsetof(Bond, ad_select)},
      {"Tap.PacketInfo",              config_parse_bool,                  0,                             offsetof(TunTap, packet_info)},
      {"Tunnel.TTL",                  config_parse_unsigned,              0,                             offsetof(Tunnel, ttl)},
      {"VXLAN.DestinationPort",       config_parse_destination_port,      0,                             offsetof(VxLan, dest_port)},
      {"VLAN.Id",                     config_parse_uint64,                0,                             offsetof(VLan, id)},
      {"Bond.GratuitousARP",          config_parse_unsigned,              0,                             offsetof(Bond, num_grat_arp)},
      {"VXLAN.L3MissNotification",    config_parse_bool,                  0,                             offsetof(VxLan, l3miss)},
      {"Bond.UpDelaySec",             config_parse_sec,                   0,                             offsetof(Bond, updelay)},
      {"VXLAN.Group",                 config_parse_vxlan_group_address,   0,                             offsetof(VxLan, group)},
      {"Tunnel.Local",                config_parse_tunnel_address,        0,                             offsetof(Tunnel, local)},
      {"NetDev.Description",          config_parse_string,                0,                             offsetof(NetDev, description)},
      {"Tun.MultiQueue",              config_parse_bool,                  0,                             offsetof(TunTap, multi_queue)},
      {"VXLAN.PortRange",             config_parse_port_range,            0,                             0},
      {"Bridge.MaxAgeSec",            config_parse_sec,                   0,                             offsetof(Bridge, max_age)},
      {"MACVLAN.Mode",                config_parse_macvlan_mode,          0,                             offsetof(MacVlan, mode)},
      {"VXLAN.RouteShortCircuit",     config_parse_bool,                  0,                             offsetof(VxLan, route_short_circuit)},
      {"Tap.MultiQueue",              config_parse_bool,                  0,                             offsetof(TunTap, multi_queue)},
      {"Match.Host",                  config_parse_net_condition,         CONDITION_HOST,                offsetof(NetDev, match_host)},
      {"Bond.ARPValidate",            config_parse_bond_arp_validate,     0,                             offsetof(Bond, arp_validate)},
      {"VXLAN.UDPCheckSum",           config_parse_bool,                  0,                             offsetof(VxLan, udpcsum)},
      {"Tunnel.Remote",               config_parse_tunnel_address,        0,                             offsetof(Tunnel, remote)},
      {"Bond.Mode",                   config_parse_bond_mode,             0,                             offsetof(Bond, mode)},
      {"Tunnel.CopyDSCP",             config_parse_bool,                  0,                             offsetof(Tunnel, copy_dscp)},
      {"VXLAN.GroupPolicyExtension",  config_parse_bool,                  0,                             offsetof(VxLan, group_policy)},
      {"Bond.LearnPacketIntervalSec", config_parse_sec,                   0,                             offsetof(Bond, lp_interval)},
      {"Bond.MinLinks",               config_parse_unsigned,              0,                             offsetof(Bond, min_links)},
      {"VXLAN.TTL",                   config_parse_unsigned,              0,                             offsetof(VxLan, ttl)},
      {"Peer.MACAddress",             config_parse_hwaddr,                0,                             offsetof(Veth, mac_peer)},
      {"Bond.LACPTransmitRate",       config_parse_bond_lacp_rate,        0,                             offsetof(Bond, lacp_rate)},
      {"Tunnel.DiscoverPathMTU",      config_parse_bool,                  0,                             offsetof(Tunnel, pmtudisc)},
      {"VXLAN.Id",                    config_parse_uint64,                0,                             offsetof(VxLan, id)},
      {"VXLAN.ARPProxy",              config_parse_bool,                  0,                             offsetof(VxLan, arp_proxy)},
      {"Bond.PacketsPerSlave",        config_parse_unsigned,              0,                             offsetof(Bond, packets_per_slave)},
      {(char*)0},
      {"VXLAN.MacLearning",           config_parse_bool,                  0,                             offsetof(VxLan, learning)},
      {"Tun.User",                    config_parse_string,                0,                             offsetof(TunTap, user_name)},
      {"VXLAN.UDP6ZeroCheckSumTx",    config_parse_bool,                  0,                             offsetof(VxLan, udp6zerocsumtx)},
      {"Bond.AllSlavesActive",        config_parse_unsigned,              0,                             offsetof(Bond, all_slaves_active)},
      {(char*)0},
      {"Bond.FailOverMACPolicy",      config_parse_bond_fail_over_mac,    0,                             offsetof(Bond, fail_over_mac)},
      {"Tap.User",                    config_parse_string,                0,                             offsetof(TunTap, user_name)},
      {"VXLAN.L2MissNotification",    config_parse_bool,                  0,                             offsetof(VxLan, l2miss)},
      {"Tunnel.TOS",                  config_parse_unsigned,              0,                             offsetof(Tunnel, tos)},
      {"Bond.PrimaryReselectPolicy",  config_parse_bond_primary_reselect, 0,                             offsetof(Bond, primary_reselect)},
      {"Tun.OneQueue",                config_parse_bool,                  0,                             offsetof(TunTap, one_queue)},
      {"Match.KernelCommandLine",     config_parse_net_condition,         CONDITION_KERNEL_COMMAND_LINE, offsetof(NetDev, match_kernel)},
      {"Bridge.HelloTimeSec",         config_parse_sec,                   0,                             offsetof(Bridge, hello_time)},
      {"Tunnel.EncapsulationLimit",   config_parse_encap_limit,           0,                             offsetof(Tunnel, encap_limit)},
      {(char*)0},
      {"Tap.OneQueue",                config_parse_bool,                  0,                             offsetof(TunTap, one_queue)},
      {"Bond.TransmitHashPolicy",     config_parse_bond_xmit_hash_policy, 0,                             offsetof(Bond, xmit_hash_policy)},
      {(char*)0}, {(char*)0}, {(char*)0},
      {"Bond.DownDelaySec",           config_parse_sec,                   0,                             offsetof(Bond, downdelay)},
      {"VXLAN.MaximumFDBEntries",     config_parse_unsigned,              0,                             offsetof(VxLan, max_fdb)},
      {"VXLAN.TOS",                   config_parse_unsigned,              0,                             offsetof(VxLan, tos)},
      {"Match.Virtualization",        config_parse_net_condition,         CONDITION_VIRTUALIZATION,      offsetof(NetDev, match_virt)},
      {(char*)0},
      {"Bridge.ForwardDelaySec",      config_parse_sec,                   0,                             offsetof(Bridge, forward_delay)},
      {"VXLAN.FDBAgeingSec",          config_parse_sec,                   0,                             offsetof(VxLan, fdb_ageing)},
      {"VXLAN.UDP6ZeroCheckSumRx",    config_parse_bool,                  0,                             offsetof(VxLan, udp6zerocsumrx)},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {"Tap.VNetHeader",              config_parse_bool,                  0,                             offsetof(TunTap, vnet_hdr)},
      {(char*)0}, {(char*)0}, {(char*)0},
      {"Match.Architecture",          config_parse_net_condition,         CONDITION_ARCHITECTURE,        offsetof(NetDev, match_arch)},
      {"Tun.Group",                   config_parse_string,                0,                             offsetof(TunTap, group_name)},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {"Tap.Group",                   config_parse_string,                0,                             offsetof(TunTap, group_name)}
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = network_netdev_gperf_hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          register const char *s = wordlist[key].section_and_lvalue;

          if (s && *str == *s && !strcmp (str + 1, s + 1))
            return &wordlist[key];
        }
    }
  return 0;
}
