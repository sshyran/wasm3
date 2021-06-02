//
//  Wasm3, high performance WebAssembly interpreter
//
//  Extensions
//
//  Copyright © 2019-2021 Steven Massey, Volodymyr Shymanskyy.
//  All rights reserved.
//

#ifndef wasm3_ext_h
#define wasm3_ext_h

#include "m3_exec_defs.h"

#include <stdbool.h>

#if defined(__cplusplus)
extern "C" {
#endif

//-------------------------------------------------------------------------------------------------------------------------------
//  API extensions
//-------------------------------------------------------------------------------------------------------------------------------
/*
    These extensions allow for unconventional uses of Wasm3 -- mainly dynamic modification of modules to inject new Wasm
    functions during runtime.
*/
//-------------------------------------------------------------------------------------------------------------------------------

    // Creates an empty module.
    IM3Module           m3Ext_NewModule             (IM3Environment         i_environment);

    // ReserveFunctions must be called prior to LoadModule.  This reserves extra empty function slots that InjectFunction
    // can rely upon.
    M3Result            m3Ext_ReserveFunctions      (IM3Module              i_module,
                                                     uint32_t               i_numFunctions);

    // To append a new function, set io_functionIndex to negative. On return, the new function index will be set.
    // To overwrite an existing function, set io_functionIndex to the desired element. i_signature must match the existing
    // function signature.  TODO: failure result is?
    M3Result            m3Ext_InjectFunction        (IM3Module              i_module,
                                                     int32_t *              io_functionIndex,
//                                                   const char * const     i_name,
                                                     const char * const     i_signature,
                                                     const uint8_t * const  i_wasmBytes,            // i_wasmBytes is copied
                                                     bool                   i_doCompilation);

    M3Result            m3Ext_AddFunctionToTable    (IM3Function            i_function,
                                                     uint32_t *             o_elementIndex,
                                                     uint32_t               i_tableIndex);          // i_tableIndex must be zero


    IM3Function         m3_GetFunctionByIndex       (IM3Module              i_module,
                                                     uint32_t               i_index);

    M3Result            m3_GetFunctionIndex         (IM3Function            i_function,
                                                     uint32_t *             o_index);

    M3Result            m3_GetDataSegmentOffset     (IM3Module              i_module,
                                                     uint32_t               i_index);

//-------------------------------------------------------------------------------------------------------------------------------

    M3Result            m3_RegisterCustomOpcode     (IM3Module              i_module,
                                                     uint16_t               i_opcode,
                                                     uint8_t                i_numImmediates,
                                                     IM3Operation           i_operation);

//-------------------------------------------------------------------------------------------------------------------------------

#if 0
    M3Result            m3_SetStackGlobalIndex      (IM3Module              io_module,
                                                     uint32_t               i_index);

    M3Result            m3_StackAllocate            (IM3Module              io_module,
                                                     uint32_t *             o_location,
                                                     const uint8_t * const  i_bytes,
                                                     uint32_t               i_size);

    M3Result            m3_PopStack                 (IM3Module              io_module,
                                                     uint32_t               i_size);
#endif

#if defined(__cplusplus)
}
#endif

#endif // wasm3_h
