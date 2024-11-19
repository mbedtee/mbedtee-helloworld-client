/*
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) 2019 KapaXL (kapa.xl@outlook.com)
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <getopt.h>

#include <tee_client_api.h>

#define TA_UUID {0x6d809454, 0xccb2, 0x4ed9, {0xb7, 0xcf, \
		0x92, 0x44, 0x73, 0x54, 0xb3, 0x67}}

int main(int argc, char *argv[])
{
	TEEC_Result ret;
	TEEC_Context context;
	TEEC_Session session;
	uint32_t cmd_id = 0;;
	uint32_t errorigin = 0;
	const TEEC_UUID uuid = TA_UUID;
	TEEC_Operation ops = {0};

	ret = TEEC_InitializeContext(NULL, &context);
	if (ret != TEEC_SUCCESS) {
		printf("TEEC_InitializeContext failed (%x)\n", (int)ret);
		return ret;
	}

	ret = TEEC_OpenSession(&context, &session, &uuid,
			  TEEC_LOGIN_PUBLIC, NULL, NULL, &errorigin);
	if (ret != TEEC_SUCCESS) {
		printf("TEEC_OpenSession failed (%x)\n", (int)ret);
		goto cleanup;
	}

	ops.paramTypes = TEEC_PARAM_TYPES(TEEC_NONE, TEEC_NONE, TEEC_NONE, TEEC_NONE);
	ret = TEEC_InvokeCommand(&session, cmd_id, &ops, &errorigin);

	ops.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INPUT, TEEC_NONE, TEEC_NONE, TEEC_NONE);
	ret = TEEC_InvokeCommand(&session, cmd_id + 1, &ops, &errorigin);

	ops.paramTypes = TEEC_PARAM_TYPES(TEEC_NONE, TEEC_VALUE_INPUT, TEEC_NONE, TEEC_NONE);
	ret = TEEC_InvokeCommand(&session, cmd_id + 2, &ops, &errorigin);

	ops.paramTypes = TEEC_PARAM_TYPES(TEEC_NONE, TEEC_NONE, TEEC_VALUE_INPUT, TEEC_NONE);
	ret = TEEC_InvokeCommand(&session, cmd_id + 3, &ops, &errorigin);

	ops.paramTypes = TEEC_PARAM_TYPES(TEEC_NONE, TEEC_NONE, TEEC_NONE, TEEC_VALUE_INPUT);
	ret = TEEC_InvokeCommand(&session, cmd_id + 4, &ops, &errorigin);

	TEEC_CloseSession(&session);

cleanup:
	TEEC_FinalizeContext(&context);
	return ret;
}
