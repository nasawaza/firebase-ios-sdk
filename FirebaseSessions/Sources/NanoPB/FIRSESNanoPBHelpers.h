//
// Copyright 2022 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef FIRSESNanoPBHelpers_h
#define FIRSESNanoPBHelpers_h

#import <TargetConditionals.h>
#if __has_include("CoreTelephony/CTTelephonyNetworkInfo.h") && !TARGET_OS_MACCATALYST && \
                  !TARGET_OS_OSX && !TARGET_OS_TV
#define TARGET_HAS_MOBILE_CONNECTIVITY
#import <CoreTelephony/CTCarrier.h>
#import <CoreTelephony/CTTelephonyNetworkInfo.h>
#endif

#import <nanopb/pb.h>
#import <nanopb/pb_decode.h>
#import <nanopb/pb_encode.h>

NS_ASSUME_NONNULL_BEGIN

// It seems impossible to specify the nullability of the `fields` parameter below,
// yet the compiler complains that it's missing a nullability specifier. Google
// yields no results at this time.
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnullability-completeness"
NSData* _Nullable FIRSESEncodeProto(const pb_field_t fields[],
                                    const void* _Nonnull proto,
                                    NSError** error);
#pragma clang diagnostic pop

/// Mallocs a pb_bytes_array and copies the given NSData bytes into the bytes array.
/// @note Memory needs to be freed manually, through pb_free or pb_release.
/// @param data The data to copy into the new bytes array.
pb_bytes_array_t* _Nullable FIRSESEncodeData(NSData* _Nullable data);

/// Mallocs a pb_bytes_array and copies the given NSString's bytes into the bytes array.
/// @note Memory needs to be freed manually, through pb_free or pb_release.
/// @param string The string to encode as pb_bytes.
pb_bytes_array_t* _Nullable FIRSESEncodeString(NSString* _Nullable string);

/// Checks if 2 nanopb arrays are equal
/// @param array array to check
/// @param expected expected value of the array
BOOL FIRSESIsPBArrayEqual(pb_bytes_array_t* _Nullable array, pb_bytes_array_t* _Nullable expected);

/// Checks if a nanopb string is equal to an NSString
/// @param pbString nanopb string to check
/// @param str NSString that's expected
BOOL FIRSESIsPBStringEqual(pb_bytes_array_t* _Nullable pbString, NSString* _Nullable str);

/// Checks if a nanopb array is equal to NSData
/// @param pbArray nanopb array to check
/// @param data NSData that's expected
BOOL FIRSESIsPBDataEqual(pb_bytes_array_t* _Nullable pbArray, NSData* _Nullable data);

/// Returns the validated MccMnc if it is available, or nil if the device does not support telephone
NSString* _Nullable FIRSESGetMccMnc(void);

NS_ASSUME_NONNULL_END

#endif /* FIRSESNanoPBHelpers_h */
