/* SPDX-License-Identifier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2012-2014, 2018-2019, 2021-2022 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#ifndef __iwl_fw_api_mac_cfg_h__
#define __iwl_fw_api_mac_cfg_h__

#include "mac.h"

/**
 * enum iwl_mac_conf_subcmd_ids - mac configuration command IDs
 */
enum iwl_mac_conf_subcmd_ids {
	/**
	 * @LOW_LATENCY_CMD: &struct iwl_mac_low_latency_cmd
	 */
	LOW_LATENCY_CMD = 0x3,
	/**
	 * @CHANNEL_SWITCH_TIME_EVENT_CMD: &struct iwl_chan_switch_te_cmd
	 */
	CHANNEL_SWITCH_TIME_EVENT_CMD = 0x4,
	/**
	 * @MISSED_VAP_NOTIF: &struct iwl_missed_vap_notif
	 */
	MISSED_VAP_NOTIF = 0xFA,
	/**
	 * @SESSION_PROTECTION_CMD: &struct iwl_mvm_session_prot_cmd
	 */
	SESSION_PROTECTION_CMD = 0x5,
	/**
	 * @CANCEL_CHANNEL_SWITCH_CMD: &struct iwl_cancel_channel_switch_cmd
	 */
	CANCEL_CHANNEL_SWITCH_CMD = 0x6,
	/**
	 * @MAC_CONFIG_CMD: &struct iwl_mac_config_cmd
	 */
	MAC_CONFIG_CMD = 0x8,
	/**
	 * @SESSION_PROTECTION_NOTIF: &struct iwl_mvm_session_prot_notif
	 */
	SESSION_PROTECTION_NOTIF = 0xFB,

	/**
	 * @PROBE_RESPONSE_DATA_NOTIF: &struct iwl_probe_resp_data_notif
	 */
	PROBE_RESPONSE_DATA_NOTIF = 0xFC,

	/**
	 * @CHANNEL_SWITCH_START_NOTIF: &struct iwl_channel_switch_start_notif
	 */
	CHANNEL_SWITCH_START_NOTIF = 0xFF,

	/**
	 *@CHANNEL_SWITCH_ERROR_NOTIF: &struct iwl_channel_switch_error_notif
	 */
	CHANNEL_SWITCH_ERROR_NOTIF = 0xF9,
};

#define IWL_P2P_NOA_DESC_COUNT	(2)

/**
 * struct iwl_p2p_noa_attr - NOA attr contained in probe resp FW notification
 *
 * @id: attribute id
 * @len_low: length low half
 * @len_high: length high half
 * @idx: instance of NoA timing
 * @ctwin: GO's ct window and pwer save capability
 * @desc: NoA descriptor
 * @reserved: reserved for alignment purposes
 */
struct iwl_p2p_noa_attr {
	u8 id;
	u8 len_low;
	u8 len_high;
	u8 idx;
	u8 ctwin;
	struct ieee80211_p2p_noa_desc desc[IWL_P2P_NOA_DESC_COUNT];
	u8 reserved;
} __packed;

#define IWL_PROBE_RESP_DATA_NO_CSA (0xff)

/**
 * struct iwl_probe_resp_data_notif - notification with NOA and CSA counter
 *
 * @mac_id: the mac which should send the probe response
 * @noa_active: notifies if the noa attribute should be handled
 * @noa_attr: P2P NOA attribute
 * @csa_counter: current csa counter
 * @reserved: reserved for alignment purposes
 */
struct iwl_probe_resp_data_notif {
	__le32 mac_id;
	__le32 noa_active;
	struct iwl_p2p_noa_attr noa_attr;
	u8 csa_counter;
	u8 reserved[3];
} __packed; /* PROBE_RESPONSE_DATA_NTFY_API_S_VER_1 */

/**
 * struct iwl_missed_vap_notif - notification of missing vap detection
 *
 * @mac_id: the mac for which the ucode sends the notification for
 * @num_beacon_intervals_elapsed: beacons elpased with no vap profile inside
 * @profile_periodicity: beacons period to have our profile inside
 * @reserved: reserved for alignment purposes
 */
struct iwl_missed_vap_notif {
	__le32 mac_id;
	u8 num_beacon_intervals_elapsed;
	u8 profile_periodicity;
	u8 reserved[2];
} __packed; /* MISSED_VAP_NTFY_API_S_VER_1 */

/**
 * struct iwl_channel_switch_start_notif - Channel switch start notification
 *
 * @id_and_color: ID and color of the MAC
 */
struct iwl_channel_switch_start_notif {
	__le32 id_and_color;
} __packed; /* CHANNEL_SWITCH_START_NTFY_API_S_VER_1 */

#define CS_ERR_COUNT_ERROR BIT(0)
#define CS_ERR_LONG_DELAY_AFTER_CS BIT(1)
#define CS_ERR_LONG_TX_BLOCK BIT(2)
#define CS_ERR_TX_BLOCK_TIMER_EXPIRED BIT(3)

/**
 * struct iwl_channel_switch_error_notif - Channel switch error notification
 *
 * @mac_id: the mac for which the ucode sends the notification for
 * @csa_err_mask: mask of channel switch error that can occur
 */
struct iwl_channel_switch_error_notif {
	__le32 mac_id;
	__le32 csa_err_mask;
} __packed; /* CHANNEL_SWITCH_ERROR_NTFY_API_S_VER_1 */

/**
 * struct iwl_cancel_channel_switch_cmd - Cancel Channel Switch command
 *
 * @mac_id: the mac that should cancel the channel switch
 */
struct iwl_cancel_channel_switch_cmd {
	__le32 mac_id;
} __packed; /* MAC_CANCEL_CHANNEL_SWITCH_S_VER_1 */

/**
 * struct iwl_chan_switch_te_cmd - Channel Switch Time Event command
 *
 * @mac_id: MAC ID for channel switch
 * @action: action to perform, one of FW_CTXT_ACTION_*
 * @tsf: beacon tsf
 * @cs_count: channel switch count from CSA/eCSA IE
 * @cs_delayed_bcn_count: if set to N (!= 0) GO/AP can delay N beacon intervals
 *	at the new channel after the channel switch, otherwise (N == 0) expect
 *	beacon right after the channel switch.
 * @cs_mode: 1 - quiet, 0 - otherwise
 * @reserved: reserved for alignment purposes
 */
struct iwl_chan_switch_te_cmd {
	__le32 mac_id;
	__le32 action;
	__le32 tsf;
	u8 cs_count;
	u8 cs_delayed_bcn_count;
	u8 cs_mode;
	u8 reserved;
} __packed; /* MAC_CHANNEL_SWITCH_TIME_EVENT_S_VER_2 */

/**
 * struct iwl_mac_low_latency_cmd - set/clear mac to 'low-latency mode'
 *
 * @mac_id: MAC ID to whom to apply the low-latency configurations
 * @low_latency_rx: 1/0 to set/clear Rx low latency direction
 * @low_latency_tx: 1/0 to set/clear Tx low latency direction
 * @reserved: reserved for alignment purposes
 */
struct iwl_mac_low_latency_cmd {
	__le32 mac_id;
	u8 low_latency_rx;
	u8 low_latency_tx;
	__le16 reserved;
} __packed; /* MAC_LOW_LATENCY_API_S_VER_1 */

/**
 * struct iwl_mac_client_data - configuration data for client MAC context
 *
 * @is_assoc: 1 for associated state, 0 otherwise
 * @assoc_id: unique ID assigned by the AP during association
 * @data_policy: see &enum iwl_mac_data_policy
 * @ctwin: client traffic window in TU (period after TBTT when GO is present).
 *	0 indicates that there is no CT window.
 */
struct iwl_mac_client_data {
	__le32 is_assoc;
	__le32 assoc_id;
	__le32 data_policy;
	__le32 ctwin;
} __packed; /* MAC_CONTEXT_CONFIG_CLIENT_DATA_API_S_VER_1 */

/**
 * struct iwl_mac_go_ibss_data - configuration data for GO and IBSS MAC context
 *
 * @beacon_template: beacon template ID
 */
struct iwl_mac_go_ibss_data {
	__le32 beacon_template;
} __packed; /* MAC_CONTEXT_CONFIG_GO_IBSS_DATA_API_S_VER_1 */

/**
 * struct iwl_mac_p2p_dev_data  - configuration data for P2P device MAC context
 *
 * @is_disc_extended: if set to true, P2P Device discoverability is enabled on
 *	other channels as well. This should be to true only in case that the
 *	device is discoverable and there is an active GO. Note that setting this
 *	field when not needed, will increase the number of interrupts and have
 *	effect on the platform power, as this setting opens the Rx filters on
 *	all macs.
 */
struct iwl_mac_p2p_dev_data {
	__le32 is_disc_extended;
} __packed; /* MAC_CONTEXT_CONFIG_P2P_DEV_DATA_API_S_VER_1 */

/**
 * enum iwl_mac_config_filter_flags - MAC context configuration filter flags
 *
 * @MAC_CFG_FILTER_PROMISC: accept all data frames
 * @MAC_CFG_FILTER_ACCEPT_CONTROL_AND_MGMT: pass all management and
 *	control frames to the host
 * @MAC_CFG_FILTER_ACCEPT_GRP: accept multicast frames
 * @MAC_CFG_FILTER_ACCEPT_BEACON: accept beacon frames
 * @MAC_CFG_FILTER_ACCEPT_BCAST_PROBE_RESP: accept broadcast probe response
 * @MAC_CFG_FILTER_ACCEPT_PROBE_REQ: accept probe requests
 */
enum iwl_mac_config_filter_flags {
	MAC_CFG_FILTER_PROMISC			= BIT(0),
	MAC_CFG_FILTER_ACCEPT_CONTROL_AND_MGMT	= BIT(1),
	MAC_CFG_FILTER_ACCEPT_GRP		= BIT(2),
	MAC_CFG_FILTER_ACCEPT_BEACON		= BIT(3),
	MAC_CFG_FILTER_ACCEPT_BCAST_PROBE_RESP	= BIT(4),
	MAC_CFG_FILTER_ACCEPT_PROBE_REQ		= BIT(5),
}; /* MAC_FILTER_FLAGS_MASK_E_VER_1 */

/**
 * struct iwl_mac_config_cmd - command structure to configure MAC contexts in
 *	MLD API
 * ( MAC_CONTEXT_CONFIG_CMD = 0x8 )
 *
 * @id_and_color: ID and color of the MAC
 * @action: action to perform, one of FW_CTXT_ACTION_*
 * @mac_type: one of &enum iwl_mac_types
 * @local_mld_addr: mld address
 * @reserved_for_local_mld_addr: reserved
 * @filter_flags: combination of &enum iwl_mac_config_filter_flags
 * @he_support: does this MAC support HE
 * @eht_support: does this MAC support EHT. Requires he_support
 * @nic_not_ack_enabled: mark that the NIC doesn't support receiving
 *	ACK-enabled AGG, (i.e. both BACK and non-BACK frames in single AGG).
 *	If the NIC is not ACK_ENABLED it may use the EOF-bit in first non-0
 *	len delim to determine if AGG or single.
 */
struct iwl_mac_config_cmd {
	/* COMMON_INDEX_HDR_API_S_VER_1 */
	__le32 id_and_color;
	__le32 action;
	/* MAC_CONTEXT_TYPE_API_E */
	__le32 mac_type;
	u8 local_mld_addr[6];
	__le16 reserved_for_local_mld_addr;
	__le32 filter_flags;
	__le32 he_support;
	__le32 eht_support;
	__le32 nic_not_ack_enabled;
	/* MAC_CONTEXT_CONFIG_SPECIFIC_DATA_API_U_VER_1 */
	union {
		struct iwl_mac_client_data client;
		struct iwl_mac_go_ibss_data go_ibss;
		struct iwl_mac_p2p_dev_data p2p_dev;
	};
} __packed; /* MAC_CONTEXT_CONFIG_CMD_API_S_VER_1 */

#endif /* __iwl_fw_api_mac_cfg_h__ */
