//
// seph 0.x
//
// Copyright 2024 Kyle Furlong
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <stdint.h>

static uint64_t e[16] =
{0xb7e151628aed2a6aull, 0xbf7158809cf4f3c7ull,
 0x62e7160f38b4da56ull, 0xa784d9045190cfefull,
 0x324e7738926cfbe5ull, 0xf4bf8d8d8c31d763ull,
 0xda06c80abb1185ebull, 0x4f7c7b5757f59584ull,
 0x90cfd47d7c19bb42ull, 0x158d9554f7b46bceull,
 0xd55c4d79fd5f24d6ull, 0x613c31c3839a2ddfull,
 0x8a9a276bcfbfa1c8ull, 0x77c56284dab79cd4ull,
 0xc2b3293d20e9e5eaull, 0xf02ac60acc93ed87ull} ;

uint64_t cm2(uint64_t a, uint64_t b) {
    if (a == 0) {
        a = e[0];
    }
    if (b == 0) {
        b = e[1];
    }
    __uint128_t p = (__uint128_t)a * (__uint128_t)b;

    return (p >> 64) ^ p;
}

uint64_t seph(const void* in, uint32_t seed, uint32_t length) {
    const uint64_t* in_body = (const uint64_t*)in;

    size_t i = 0;
    size_t l = length / 8;

    uint64_t h1 = e[0];

    h1 ^= cm2(seed, length);

    for (; i < l; i++) {
        h1 ^= in_body[i+0] ^ (i+0);
    }

    const uint8_t* in_tail = (const uint8_t*)in;

    for (i = i * 8; i < length; i++) {
        h1 += (in_tail[i+0] << ((i & 0x7) * 8)) + (i+0);
    }

    int k = 2;
    while(k--) h1 = cm2(h1, e[h1 & 0xF]);

    return h1;
}
