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

@interface XsensDotUtils : NSObject

+ (void)quatToEuler:(double [_Nullable])eular WithW:(float)quatW withX:(float)quatX withY:(float)quatY withZ:(float)quatZ;

+ (NSString *)hexStringFromString:(NSString *)string;
+ (NSString *)hexStringFromData:(NSData *)data;
+ (NSData *)dataWithHexString:(NSString*)string;

+ (NSData *)byteFromUInt8:(UInt8)value;
+ (NSData *)bytesFromUInt16:(UInt16)value;
+ (NSData *)bytesFromUInt32:(UInt32)value;

+ (NSData *)getOtaCRC16:(NSData *)data;

+ (BOOL)isSensorFusionMode:(XSBleDevicePayloadMode) payloadMode;
+ (BOOL)isInertialMode:(XSBleDevicePayloadMode) payloadMode;
+ (BOOL)isCustomMode:(XSBleDevicePayloadMode)payloadMode;
+ (UInt8)bytesFromRecordingData:(XSRecordingData)recordingData;

+ (NSString *)dateWithTimeStamp:(NSUInteger)timeStamp;

@end

NS_ASSUME_NONNULL_END
