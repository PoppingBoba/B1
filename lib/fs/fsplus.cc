/*
 * Copyright (c) 2026 Nakada Tokumei
 * Copyright (c) 2009-2015 Travis Geiselbrecht
 *
 * Use of this source code is governed by a MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT
 */

 
#include <lk/compiler.h>
#include <lib/fs.h>
#include <lib/fsplus.h>

extern "C" FileSystemMetaClass* __start_fsplus_meta[] __WEAK;
extern "C" FileSystemMetaClass* __stop_fsplus_meta[] __WEAK;

extern "C" void fsplus_dump_list() 
{
    auto metaListStart = __start_fsplus_meta;
    for (; metaListStart != __stop_fsplus_meta; metaListStart++)
    {

    }
}
