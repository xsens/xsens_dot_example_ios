//
//  XsensDotUtils.h
//  XsensDotSdk
//
//  Created by Jayson on 2020/4/16.
//  Copyright © 2020 Xsens. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "XsensDotDevice.h"

NS_ASSUME_NONNULL_BEGIN

/**
 *  The utils class contains the available conversion methods.
 */
@interface XsensDotUtils : NSObject
/**
    Convert quaternion to euler
    @param eular The euler array
    @param quatW The XsensDotPlotData.quatW data
    @param quatX The XsensDotPlotData.quatX data
    @param quatY The XsensDotPlotData.quatY data
    @param quatZ The XsensDotPlotData.quatZ data
 */
+ (void)quatToEuler:(double [_Nullable])eular WithW:(float)quatW withX:(float)quatX withY:(float)quatY withZ:(float)quatZ;

/**
    @brief Convert string to hex string
    @param string The NSString object
    @return The NSString object
 */
+ (NSString *)hexStringFromString:(NSString *)string;

/**
    @brief Convert data to hex string
    @param data The NSData object
    @return The NSString object
 */
+ (NSString *)hexStringFromData:(NSData *)data;

/**
    @brief Convert hex string to data
    @param string The NSString object
    @return The NSData object
 */
+ (NSData *)dataWithHexString:(NSString*)string;

/**
    @brief UInt8  to data
    @param value UInt8 value
    @return The NSData object
 */
+ (NSData *)byteFromUInt8:(UInt8)value;

/**
    @brief UInt16  to data
    @param value UInt16 value
    @return The NSData object
 */
+ (NSData *)bytesFromUInt16:(UInt16)value;

/**
    @brief UInt32  to data
    @param value UInt32 value
    @return The NSData object
 */
+ (NSData *)bytesFromUInt32:(UInt32)value;

/**
    @brief Get ota crc data from data , SDK internal used
    @param data 16 bytes data
 */
+ (NSData *)getOtaCRC16:(NSData *)data;

/**
    @brief Check current payloadMode is sensor fusion mode.
    @param payloadMode XSBleDevicePayloadMode object
    @return YES/NO if it's the sensor fusion mode
 */
+ (BOOL)isSensorFusionMode:(XSBleDevicePayloadMode) payloadMode;

/**
    @brief Check current payloadMode is inertial  mode.
    @param payloadMode XSBleDevicePayloadMode object
    @return YES/NO if it's the inertial mode
 */
+ (BOOL)isInertialMode:(XSBleDevicePayloadMode) payloadMode;

/**
    @brief Check current payloadMode is custom  mode.
    @param payloadMode XSBleDevicePayloadMode object
    @return YES/NO if it's the custom mode
 */
+ (BOOL)isCustomMode:(XSBleDevicePayloadMode)payloadMode;

/**
    @brief The bytes length of recording data
    @param recordingData XSRecordingData object
    @return The length
 */
+ (UInt8)bytesFromRecordingData:(XSRecordingData)recordingData;

/**
    @brief Convert timestamp to Date string
    @param timeStamp The timestamp
    @return The NSSting object
 */
+ (NSString *)dateStringFromTimeStamp:(NSUInteger)timeStamp;

@end

NS_ASSUME_NONNULL_END
