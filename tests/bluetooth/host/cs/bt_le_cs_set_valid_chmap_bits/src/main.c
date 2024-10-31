/*
 * Copyright (c) 2024 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mocks/conn.h"
#include "mocks/hci_core.h"
#include "mocks/net_buf.h"

#include <zephyr/kernel.h>
#include <zephyr/bluetooth/cs.h>
#include <zephyr/fff.h>

DEFINE_FFF_GLOBALS;

static void fff_reset_rule_before(const struct ztest_unit_test *test, void *fixture)
{
	RESET_FAKE(bt_le_cs_set_valid_chmap_bits);
}

ZTEST_RULE(fff_reset_rule, fff_reset_rule_before, NULL);

ZTEST_SUITE(bt_le_cs_set_valid_chmap_bits, NULL, NULL, NULL, NULL, NULL);

/*
 *  Test empty data buffer
 *
 *  Constraints:
 *   - buffer len set to 0
 *
 *  Expected behaviour:
 *   - Callback function is not called
 */
ZTEST(bt_le_cs_set_valid_chmap_bits, test_empty_chmap)
{
	uint8_t test_chmap[10];

	bt_le_cs_set_valid_chmap_bits(test_chmap);

	uint8_t correct_chmap[10] = [0x31, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x7F, 0xFF, 0xFC]

	zassert_mem_equal(test_chmap, correct_chmap, 10);
}
