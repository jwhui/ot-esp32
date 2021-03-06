/*
 *  Copyright (c) 2020, The OpenThread Authors.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. Neither the name of the copyright holder nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

#include "platform-esp32.h"

#include <stdio.h>

#include <esp_log.h>

#include <openthread/platform/logging.h>
#include <openthread/platform/toolchain.h>

#include "error_handling.h"

#if (OPENTHREAD_CONFIG_LOG_OUTPUT == OPENTHREAD_CONFIG_LOG_OUTPUT_PLATFORM_DEFINED) || \
    (OPENTHREAD_CONFIG_LOG_OUTPUT == OPENTHREAD_CONFIG_LOG_OUTPUT_NCP_SPINEL)
OT_TOOL_WEAK void otPlatLog(otLogLevel aLogLevel, otLogRegion aLogRegion, const char *aFormat, ...)
{
    char    logString[256];
    int     charsWritten;
    va_list args;

    OT_UNUSED_VARIABLE(aLogRegion);

    va_start(args, aFormat);
    charsWritten = vsnprintf(logString, sizeof(logString), aFormat, args);
    if (charsWritten < 0)
    {
        logString[0] = '\0';
    }

    switch (aLogLevel)
    {
    case OT_LOG_LEVEL_CRIT:
        ESP_LOGE(OT_PLAT_LOG_TAG, "%s", logString);
        break;
    case OT_LOG_LEVEL_WARN:
        ESP_LOGW(OT_PLAT_LOG_TAG, "%s", logString);
        break;
    case OT_LOG_LEVEL_NOTE:
    case OT_LOG_LEVEL_INFO:
        ESP_LOGI(OT_PLAT_LOG_TAG, "%s", logString);
        break;
    default:
        ESP_LOGD(OT_PLAT_LOG_TAG, "%s", logString);
        break;
    }
    va_end(args);
}
#endif
