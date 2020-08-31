//
//  XsensDotDevicePool.h
//  XsensDotSdk
//
//  Created by Nick Yang on 2019/6/18.
//  Copyright © 2019 Xsens. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "XsensDotDevice.h"

NS_ASSUME_NONNULL_BEGIN

extern NSInteger const XSDotDevicePoolCapacityMax;

@interface XsensDotDevicePool : NSObject
+ (XsensDotDevice *)inquireDeviceWithPeripheral:(CBPeripheral *)peripheral;
+ (void)bindDevices:(NSArray <XsensDotDevice *>*)devices;
+ (BOOL)bindDevice:(XsensDotDevice *)device;
+ (void)unbindDevice:(XsensDotDevice *)device;
+ (void)unbindAllDevices;
+ (NSArray <XsensDotDevice *>*)allBoundDevices;
+ (NSArray <XsensDotDevice *>*)allOtaDevices;
+ (void)addOtaDevice:(XsensDotDevice *)device;
@end


@interface XsensDotDevicePool (Connection)
+ (XsensDotDevice *)heldDeviceWithPeripheral:(CBPeripheral *)peripheral;
+ (void)holdDevice:(XsensDotDevice *)device;
+ (void)releaseDevice:(XsensDotDevice *)device;
+ (void)onCentralStateUpdated;
@end

NS_ASSUME_NONNULL_END
