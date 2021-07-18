/* Automatically generated by p4c-wp4 from openwifi_wp4.p4 on Sun Jul 18 15:20:24 2021
 */
#include <linux/module.h>    // included for all kernel modules
#include <linux/kernel.h>    // included for KERN_INFO
#include <linux/init.h>      // included for __init and __exit macros
#include <linux/fs.h>
#include <linux/debugfs.h>
#include <linux/timekeeping.h>
#include <linux/time.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/skbuff.h>
#include <linux/netdevice.h>
#include "wp4_runtime.h"


#include "wp4-p4.h"

#define WP4_MASK(t, w) ((((t)(1)) << (w)) - (t)1)
#define BYTES(w) ((w) / 8)
#define MAX_VALUE(x) ( ~ 0)

int wp4_table_lookup(struct swtch_lookup_tbl_key *key);

struct wp4_output wp4out;
extern struct wp4_map_def *flow_table;

static int __init wp4_init(void) {
    printk(KERN_INFO "WP4: Loading WP4 LKM!\n");
    table_init();
    flow_table->key_size = sizeof(struct swtch_lookup_tbl_key);
    flow_table->value_size = sizeof(enum lookup_tbl_0_actions);
    flow_table->max_entries = 256;
    flow_table->last_entry = 0;
    return 0;
}

static void __exit wp4_exit(void) {
   printk(KERN_INFO "WP4: Removing WP4 LKM!\n");
   table_exit();
}

int wp4_packet_in(u8 *p_uc_data, u16 wp4_ul_size, u8 port){

    struct Headers_t headers = {
        .rfFeatures = {
            .wp4_valid = 0
        },
        .frameCtrl = {
            .wp4_valid = 0
        },
        .mac80211 = {
            .wp4_valid = 0
        },
    };

    u16 wp4_packetOffsetInBits = 0;
    u8 *wp4_packetStart = p_uc_data;

    dump_rx_packet(wp4_packetStart);
    printk("** WP4: Packet Received, size = %d **\n", wp4_ul_size);

    goto start;

// Start of Parser
    start: {
/* extract(headers.rfFeatures)*/
        if (wp4_ul_size < BYTES(wp4_packetOffsetInBits + 256)) {
            goto reject;
        }
        
        memcpy(&headers.rfFeatures.timestamp, wp4_packetStart + BYTES(wp4_packetOffsetInBits), BYTES(64));
        headers.rfFeatures.timestamp = (headers.rfFeatures.timestamp);     // ** 64 - 0 - 64 - s **
        wp4_packetOffsetInBits += 64;

        memcpy(&headers.rfFeatures.rssi, wp4_packetStart + BYTES(wp4_packetOffsetInBits), BYTES(16));
        headers.rfFeatures.rssi = (headers.rfFeatures.rssi);     // ** 16 - 0 - 16 - s **
        wp4_packetOffsetInBits += 16;

        memcpy(&headers.rfFeatures.blank, wp4_packetStart + BYTES(wp4_packetOffsetInBits), BYTES(16));
        headers.rfFeatures.blank = (headers.rfFeatures.blank);     // ** 16 - 0 - 16 - s **
        wp4_packetOffsetInBits += 16;

        memcpy(&headers.rfFeatures.len, wp4_packetStart + BYTES(wp4_packetOffsetInBits), BYTES(16));
        headers.rfFeatures.len = (headers.rfFeatures.len);     // ** 16 - 0 - 16 - s **
        wp4_packetOffsetInBits += 16;

        memcpy(&headers.rfFeatures.rate_idx, wp4_packetStart + BYTES(wp4_packetOffsetInBits), BYTES(16));
        headers.rfFeatures.rate_idx = (headers.rfFeatures.rate_idx);     // ** 16 - 0 - 16 - s **
        wp4_packetOffsetInBits += 16;

        memcpy(&headers.rfFeatures.phaseOffset, wp4_packetStart + BYTES(wp4_packetOffsetInBits), BYTES(32));
        headers.rfFeatures.phaseOffset = (headers.rfFeatures.phaseOffset);     // ** 32 - 0 - 32 - s **
        wp4_packetOffsetInBits += 32;

        memcpy(&headers.rfFeatures.pilotOffset, wp4_packetStart + BYTES(wp4_packetOffsetInBits), BYTES(32));
        headers.rfFeatures.pilotOffset = (headers.rfFeatures.pilotOffset);     // ** 32 - 0 - 32 - s **
        wp4_packetOffsetInBits += 32;

        memcpy(&headers.rfFeatures.magSq, wp4_packetStart + BYTES(wp4_packetOffsetInBits), BYTES(32));
        headers.rfFeatures.magSq = (headers.rfFeatures.magSq);     // ** 32 - 0 - 32 - s **
        wp4_packetOffsetInBits += 32;

        memcpy(&headers.rfFeatures.aux_4, wp4_packetStart + BYTES(wp4_packetOffsetInBits), BYTES(32));
        headers.rfFeatures.aux_4 = (headers.rfFeatures.aux_4);     // ** 32 - 0 - 32 - s **
        wp4_packetOffsetInBits += 32;

        headers.rfFeatures.wp4_valid = 1;
/* extract(headers.frameCtrl)*/
        if (wp4_ul_size < BYTES(wp4_packetOffsetInBits + 16)) {
            goto reject;
        }
        
        memcpy(&headers.frameCtrl.protoVer, wp4_packetStart + BYTES(wp4_packetOffsetInBits), BYTES(8));     // ** 8 - 0 - 2 - u **
        headers.frameCtrl.protoVer &= WP4_MASK(u8, 2);
        wp4_packetOffsetInBits += 2;
        printk("** WP4: protoVer = %d **\n", headers.frameCtrl.protoVer);

        memcpy(&headers.frameCtrl.frameType, wp4_packetStart + BYTES(wp4_packetOffsetInBits), BYTES(8));     // ** 8 - 2 - 2 - u **
        headers.frameCtrl.frameType >>= 2;
        headers.frameCtrl.frameType &= WP4_MASK(u8, 2);
        wp4_packetOffsetInBits += 2;
        printk("** WP4: frameType = %d **\n", headers.frameCtrl.frameType);

        memcpy(&headers.frameCtrl.subType, wp4_packetStart + BYTES(wp4_packetOffsetInBits), BYTES(8));     // ** 8 - 4 - 4 - u **
        headers.frameCtrl.subType >>= 4;
        headers.frameCtrl.subType &= WP4_MASK(u8, 4);
        wp4_packetOffsetInBits += 4;
        printk("** WP4: subType = %d **\n", headers.frameCtrl.subType);

        memcpy(&headers.frameCtrl.toDS, wp4_packetStart + BYTES(wp4_packetOffsetInBits), BYTES(8));     // ** 8 - 0 - 1 - u **
        headers.frameCtrl.toDS &= WP4_MASK(u8, 1);
        wp4_packetOffsetInBits += 1;
        printk("** WP4: toDS = %d **\n", headers.frameCtrl.toDS);

        memcpy(&headers.frameCtrl.fromDS, wp4_packetStart + BYTES(wp4_packetOffsetInBits), BYTES(8));     // ** 8 - 1 - 1 - u **
        headers.frameCtrl.fromDS >>= 1;
        headers.frameCtrl.fromDS &= WP4_MASK(u8, 1);
        wp4_packetOffsetInBits += 1;
        printk("** WP4: fromDS = %d **\n", headers.frameCtrl.fromDS);

        memcpy(&headers.frameCtrl.moreFrag, wp4_packetStart + BYTES(wp4_packetOffsetInBits), BYTES(8));     // ** 8 - 2 - 1 - u **
        headers.frameCtrl.moreFrag >>= 2;
        headers.frameCtrl.moreFrag &= WP4_MASK(u8, 1);
        wp4_packetOffsetInBits += 1;
        printk("** WP4: moreFrag = %d **\n", headers.frameCtrl.moreFrag);

        memcpy(&headers.frameCtrl.retry, wp4_packetStart + BYTES(wp4_packetOffsetInBits), BYTES(8));     // ** 8 - 3 - 1 - u **
        headers.frameCtrl.retry >>= 3;
        headers.frameCtrl.retry &= WP4_MASK(u8, 1);
        wp4_packetOffsetInBits += 1;
        printk("** WP4: retry = %d **\n", headers.frameCtrl.retry);

        memcpy(&headers.frameCtrl.pwrMgmt, wp4_packetStart + BYTES(wp4_packetOffsetInBits), BYTES(8));     // ** 8 - 4 - 1 - u **
        headers.frameCtrl.pwrMgmt >>= 4;
        headers.frameCtrl.pwrMgmt &= WP4_MASK(u8, 1);
        wp4_packetOffsetInBits += 1;
        printk("** WP4: pwrMgmt = %d **\n", headers.frameCtrl.pwrMgmt);

        memcpy(&headers.frameCtrl.moreData, wp4_packetStart + BYTES(wp4_packetOffsetInBits), BYTES(8));     // ** 8 - 5 - 1 - u **
        headers.frameCtrl.moreData >>= 5;
        headers.frameCtrl.moreData &= WP4_MASK(u8, 1);
        wp4_packetOffsetInBits += 1;
        printk("** WP4: moreData = %d **\n", headers.frameCtrl.moreData);

        memcpy(&headers.frameCtrl.protFrame, wp4_packetStart + BYTES(wp4_packetOffsetInBits), BYTES(8));     // ** 8 - 6 - 1 - u **
        headers.frameCtrl.protFrame >>= 6;
        headers.frameCtrl.protFrame &= WP4_MASK(u8, 1);
        wp4_packetOffsetInBits += 1;
        printk("** WP4: protFrame = %d **\n", headers.frameCtrl.protFrame);

        memcpy(&headers.frameCtrl.order, wp4_packetStart + BYTES(wp4_packetOffsetInBits), BYTES(8));     // ** 8 - 7 - 1 - u **
        headers.frameCtrl.order >>= 7;
        headers.frameCtrl.order &= WP4_MASK(u8, 1);
        wp4_packetOffsetInBits += 1;
        printk("** WP4: order = %d **\n", headers.frameCtrl.order);

        headers.frameCtrl.wp4_valid = 1;
        switch (headers.frameCtrl.protoVer) {
            case 0x0: goto mac80211;
            default: goto reject;
        }
    }
    mac80211: {
/* extract(headers.mac80211)*/
        if (wp4_ul_size < BYTES(wp4_packetOffsetInBits + 224)) {
            goto reject;
        }
        
        memcpy(&headers.mac80211.durID, wp4_packetStart + BYTES(wp4_packetOffsetInBits), BYTES(16));
        headers.mac80211.durID = htons(headers.mac80211.durID);     // ** 16 - 0 - 16 - u **
        wp4_packetOffsetInBits += 16;

        memcpy(&headers.mac80211.Addr1, wp4_packetStart + BYTES(wp4_packetOffsetInBits), BYTES(64));
        headers.mac80211.Addr1 = htonll(headers.mac80211.Addr1);     // ** 64 - 0 - 48 - u **
        headers.mac80211.Addr1 >>= 16;
        headers.mac80211.Addr1 &= WP4_MASK(u64, 48);
        wp4_packetOffsetInBits += 48;

        memcpy(&headers.mac80211.Addr2, wp4_packetStart + BYTES(wp4_packetOffsetInBits), BYTES(64));
        headers.mac80211.Addr2 = htonll(headers.mac80211.Addr2);     // ** 64 - 0 - 48 - u **
        headers.mac80211.Addr2 >>= 16;
        headers.mac80211.Addr2 &= WP4_MASK(u64, 48);
        wp4_packetOffsetInBits += 48;

        memcpy(&headers.mac80211.Addr3, wp4_packetStart + BYTES(wp4_packetOffsetInBits), BYTES(64));
        headers.mac80211.Addr3 = htonll(headers.mac80211.Addr3);     // ** 64 - 0 - 48 - u **
        headers.mac80211.Addr3 >>= 16;
        headers.mac80211.Addr3 &= WP4_MASK(u64, 48);
        wp4_packetOffsetInBits += 48;

        memcpy(&headers.mac80211.seqCtrl, wp4_packetStart + BYTES(wp4_packetOffsetInBits), BYTES(16));
        headers.mac80211.seqCtrl = htons(headers.mac80211.seqCtrl);     // ** 16 - 0 - 16 - u **
        wp4_packetOffsetInBits += 16;

        memcpy(&headers.mac80211.Addr4, wp4_packetStart + BYTES(wp4_packetOffsetInBits), BYTES(64));
        headers.mac80211.Addr4 = htonll(headers.mac80211.Addr4);     // ** 64 - 0 - 48 - u **
        headers.mac80211.Addr4 >>= 16;
        headers.mac80211.Addr4 &= WP4_MASK(u64, 48);
        wp4_packetOffsetInBits += 48;

        headers.mac80211.wp4_valid = 1;
        switch (headers.mac80211.Addr2) {
            default: goto accept;
        }
    }

    reject: { 
        printk("** WP4: Packet Rejected!! **\n");
        return -1;
    }

// Start of Pipeline
    accept:
    {
        u8 hit;
        {
            if (((headers.frameCtrl.frameType == 0x0) && ((headers.frameCtrl.subType == 0xa) || (headers.frameCtrl.subType == 0xc)))) 
                                {
                /* construct key */
                struct swtch_lookup_tbl_key key = {};
                struct swtch_lookup_tbl_key wp4_zero = {};
                key.headers_mac80211_Addr2_class = headers.mac80211.Addr2;
                key.headers_frameCtrl_frameType_exact = headers.frameCtrl.frameType;
                key.headers_frameCtrl_subType_exact = headers.frameCtrl.subType;
                key.headers_rfFeatures_rate_idx_exact = headers.rfFeatures.rate_idx;
                key.headers_rfFeatures_rssi_min = headers.rfFeatures.rssi;
                key.headers_rfFeatures_rssi_max = headers.rfFeatures.rssi;
                key.headers_rfFeatures_phaseOffset_min = headers.rfFeatures.phaseOffset;
                key.headers_rfFeatures_phaseOffset_max = headers.rfFeatures.phaseOffset;
                key.headers_rfFeatures_pilotOffset_min = headers.rfFeatures.pilotOffset;
                key.headers_rfFeatures_pilotOffset_max = headers.rfFeatures.pilotOffset;
                key.headers_rfFeatures_magSq_min = headers.rfFeatures.magSq;
                key.headers_rfFeatures_magSq_max = headers.rfFeatures.magSq;
                /* value */
                enum lookup_tbl_0_actions value;
                /* perform lookup */
                value = wp4_table_lookup(&key);
                if (value >= 0) {
                    /* run action */
                    switch (value) {
                        case swtch_Drop_action: 
                        {
                            wp4out.output_action = DROP;
                        }
                        break;
                        case swtch_Pass_action: 
                        {
                            wp4out.output_action = PASS;
                        }
                        break;
                        case swtch_CPU_action: 
                        {
                            wp4out.output_action = CPU;to_cpu(headers);

                        }
                        break;
                        default: return -1;
                    }
                }
                else return -1;
            }
            else 
            {
                wp4out.output_action = CPU;
                to_cpu(headers);
            }
        }
    }

// Start of Deparser
    
    return wp4out.output_action;
}

int wp4_table_lookup(struct swtch_lookup_tbl_key *key) {

    /* LCS Prediction Algorithm */

    struct timespec ts_time;
    time_t ct;
    int i;

    for (i=0;i<flow_table->last_entry;i++)
    {
        printk("headers_mac80211_Addr2_class: %llX  - %llX (%d)\n", key->headers_mac80211_Addr2_class, flow_table->key[i].headers_mac80211_Addr2_class, MAX_VALUE(key->headers_mac80211_Addr2_class));
        printk("headers_frameCtrl_frameType_exact: %d  - %d (%d)\n", key->headers_frameCtrl_frameType_exact, flow_table->key[i].headers_frameCtrl_frameType_exact, MAX_VALUE(key->headers_frameCtrl_frameType_exact));
        printk("headers_frameCtrl_subType_exact: %d  - %d (%d)\n", key->headers_frameCtrl_subType_exact, flow_table->key[i].headers_frameCtrl_subType_exact, MAX_VALUE(key->headers_frameCtrl_subType_exact));
        printk("headers_rfFeatures_rate_idx_exact: %d  - %d (%d)\n", key->headers_rfFeatures_rate_idx_exact, flow_table->key[i].headers_rfFeatures_rate_idx_exact, MAX_VALUE(key->headers_rfFeatures_rate_idx_exact));
        printk("headers_rfFeatures_rssi_min: %d  - %d (%d)\n", key->headers_rfFeatures_rssi_min, flow_table->key[i].headers_rfFeatures_rssi_min, MAX_VALUE(key->headers_rfFeatures_rssi_min));
        printk("headers_rfFeatures_rssi_max: %d  - %d (%d)\n", key->headers_rfFeatures_rssi_max, flow_table->key[i].headers_rfFeatures_rssi_max, MAX_VALUE(key->headers_rfFeatures_rssi_max));
        printk("headers_rfFeatures_phaseOffset_min: %d  - %d (%d)\n", key->headers_rfFeatures_phaseOffset_min, flow_table->key[i].headers_rfFeatures_phaseOffset_min, MAX_VALUE(key->headers_rfFeatures_phaseOffset_min));
        printk("headers_rfFeatures_phaseOffset_max: %d  - %d (%d)\n", key->headers_rfFeatures_phaseOffset_max, flow_table->key[i].headers_rfFeatures_phaseOffset_max, MAX_VALUE(key->headers_rfFeatures_phaseOffset_max));
        printk("headers_rfFeatures_pilotOffset_min: %d  - %d (%d)\n", key->headers_rfFeatures_pilotOffset_min, flow_table->key[i].headers_rfFeatures_pilotOffset_min, MAX_VALUE(key->headers_rfFeatures_pilotOffset_min));
        printk("headers_rfFeatures_pilotOffset_max: %d  - %d (%d)\n", key->headers_rfFeatures_pilotOffset_max, flow_table->key[i].headers_rfFeatures_pilotOffset_max, MAX_VALUE(key->headers_rfFeatures_pilotOffset_max));
        printk("headers_rfFeatures_magSq_min: %d  - %d (%d)\n", key->headers_rfFeatures_magSq_min, flow_table->key[i].headers_rfFeatures_magSq_min, MAX_VALUE(key->headers_rfFeatures_magSq_min));
        printk("headers_rfFeatures_magSq_max: %d  - %d (%d)\n", key->headers_rfFeatures_magSq_max, flow_table->key[i].headers_rfFeatures_magSq_max, MAX_VALUE(key->headers_rfFeatures_magSq_max));
        printk("Action = %d\n", flow_table->action[i]);
        
    }
    getnstimeofday(&ts_time);
    ct = (ts_time.tv_sec * 1000) + (ts_time.tv_nsec / 1000000);
    int time_delta = ct - flow_table->last_lookup;
    printk("current_time = %lu - time delta = %u\n", ct, time_delta);
    flow_table->last_lookup = ct;
    return swtch_Pass_action;   // Return default action for a table miss
}

// Kernel module functions
EXPORT_SYMBOL(wp4_packet_in);

module_init(wp4_init);
module_exit(wp4_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("openwifi_wp4.p4");
MODULE_DESCRIPTION("WP4");
MODULE_VERSION("0.1");

