//
// seph 0.2
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

#include <inttypes.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>


uint64_t seph(const void* in, uint32_t seed, uint32_t length) {
    static const uint64_t e[16] =
    {0xb7e151628aed2a6aull, 0xbf7158809cf4f3c7ull,
     0x62e7160f38b4da56ull, 0xa784d9045190cfefull,
     0x324e7738926cfbe5ull, 0xf4bf8d8d8c31d763ull,
     0xda06c80abb1185ebull, 0x4f7c7b5757f59584ull,
     0x90cfd47d7c19bb42ull, 0x158d9554f7b46bceull,
     0xd55c4d79fd5f24d6ull, 0x613c31c3839a2ddfull,
     0x8a9a276bcfbfa1c8ull, 0x77c56284dab79cd4ull,
     0xc2b3293d20e9e5eaull, 0xf02ac60acc93ed87ull} ;

    const uint64_t* in_body = (const uint64_t*)in;

    uint32_t i = 0;
    uint32_t l = length / 8;

    __uint128_t h = e[0];

    h ^= (((uint64_t)seed) << 32) ^ length;

    for (; i < l; i++) {
        h += in_body[i+0];
    }

    const uint8_t* in_tail = (const uint8_t*)in;

    for (i = i * 8; i < length; i++) {
        h += (((uint64_t)in_tail[i+0]) << ((i & 0x7) * 8));
    }

    h *= e[h & 0xF];
    h ^= h >> 29;
    h *= e[h & 0xF];
 
    return (h >> 64) + h;
}
