//
//  XsensDotDeviceAssistor.h
//  XsensDotSdk
//
//  Created by Nick Yang on 2019/5/21.
//  Copyright © 2019 Xsens. All rights reserved.
//
//
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

extern NSInteger const kDeviceMacAddressDataLength;
extern NSInteger const kDeviceNameDataStartIndex;
extern NSInteger const kDeviceNameDataLength;
extern NSInteger const kDeviceSerialNumberStartIndex;
extern NSInteger const kDeviceSerialNumberLength;

@interface XsensDotDeviceAssistor : NSObject

+ (NSString *)macAddressWithUUID:(NSString *)uuid;
+ (NSString *)parseAdvertismentData:(NSDictionary *)advData;
+ (NSString *)parseMacAddressData:(NSData *)macData;
+ (void)saveMacAddress:(NSString *)macAddress forDevice:(NSString *)uuid;

+ (NSString *)customizedNameWithUUID:(NSString *)uuid;
+ (void)saveCustomizedName:(nullable NSString *)name forDevice:(NSString *)uuid;

@end

NS_ASSUME_NONNULL_END
