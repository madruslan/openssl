/*
 * Copyright 2016-2020 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#include <openssl/err.h>
#include "crypto/store.h"
#include "store_local.h"

static CRYPTO_ONCE store_init = CRYPTO_ONCE_STATIC_INIT;
DEFINE_RUN_ONCE_STATIC(do_store_init)
{
    return OPENSSL_init_crypto(0, NULL);
}

int ossl_store_init_once(void)
{
    if (!RUN_ONCE(&store_init, do_store_init)) {
        ERR_raise(ERR_LIB_OSSL_STORE, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    return 1;
}

void ossl_store_cleanup_int(void)
{
    ossl_store_destroy_loaders_int();
}
