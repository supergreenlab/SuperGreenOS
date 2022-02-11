/*
 * Copyright (C) 2022  SuperGreenLab <towelie@supergreenlab.com>
 * Author: Constantin Clauzel <constantin.clauzel@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "../log/log.h"
#include "../wifi/wifi.h"

#include "wireguardif.h"
#include "wireguard.h"

#define WG_LOCAL_ADDRESS        IPADDR4_INIT_BYTES(10, 0, 2, 2)
#define WG_LOCAL_NETMASK        IPADDR4_INIT_BYTES(255, 255, 255, 0)
#define WG_GATEWAY_ADDRESS      IPADDR4_INIT_BYTES(10, 0, 2, 1)

#define WG_CLIENT_PORT          51820

#define WG_PEER_PORT            55820
#define WG_PEER_ADDRESS         IPADDR4_INIT_BYTES(192, 168, 0, 5)

#define WG_CLIENT_PRIVATE_KEY ""
#define WG_PEER_PUBLIC_KEY ""

static struct netif wg_netif_struct = {0};
static struct netif *wg_netif = NULL;
static uint8_t wireguard_peer_index_local = WIREGUARDIF_INVALID_INDEX;

void init_vpn() {
	ESP_LOGI(SGO_LOG_EVENT, "@VPN Starting");
	struct wireguardif_init_data wg;
	struct wireguardif_peer peer;
	const ip_addr_t ipaddr = WG_LOCAL_ADDRESS;
	const ip_addr_t netmask = WG_LOCAL_NETMASK;
	const ip_addr_t gateway = WG_GATEWAY_ADDRESS;
	const ip_addr_t peer_address = WG_PEER_ADDRESS;

	// Setup the WireGuard device structure
	wg.private_key = WG_CLIENT_PRIVATE_KEY;
	wg.listen_port = WG_CLIENT_PORT;
	wg.bind_netif = NULL; // NB! not working on ESP32 even if set!

	// Register the new WireGuard network interface with lwIP
	wg_netif = netif_add(&wg_netif_struct, ip_2_ip4(&ipaddr), ip_2_ip4(&netmask), ip_2_ip4(&gateway), &wg, &wireguardif_init, &ip_input);

	// Mark the interface as administratively up, link up flag is set automatically when peer connects
	netif_set_up(wg_netif);

	// Initialise the first WireGuard peer structure
	wireguardif_peer_init(&peer);
	peer.public_key = WG_PEER_PUBLIC_KEY;
	peer.preshared_key = NULL;
	// Allow all IPs through tunnel
	//peer.allowed_ip = IPADDR4_INIT_BYTES(0, 0, 0, 0);
	IP_ADDR4(&peer.allowed_ip, 0, 0, 0, 0);
	IP_ADDR4(&peer.allowed_mask, 0, 0, 0, 0);

	// If we know the endpoint's address can add here
	ip_addr_set(&peer.endpoint_ip, &peer_address);
	peer.endport_port = WG_PEER_PORT;

	// Register the new WireGuard peer with the netwok interface
	wireguardif_add_peer(wg_netif, &peer, &wireguard_peer_index_local);

	if ((wireguard_peer_index_local != WIREGUARDIF_INVALID_INDEX) && !ip_addr_isany(&peer.endpoint_ip))
	{
		// Start outbound connection to peer
		wireguardif_connect(wg_netif, wireguard_peer_index_local);
	}
}
