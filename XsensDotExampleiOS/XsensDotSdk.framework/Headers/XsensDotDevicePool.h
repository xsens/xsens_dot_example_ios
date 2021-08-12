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

/**
 *  This class manages the reconnection behavior of sensors. When reconnection is enabled,
 *  you need to bind the sensor to activate the reconnection function after connecting a sensor.
 *  Unbind it after disconnecting the sensor, otherwise a reconnection will be initialized.
 */
@interface XsensDotDevicePool : NSObject
/**
 * Inquire sensor with peripheral to check if it is in the connection  pool.
 * @param peripheral the CBPeripheral object
 */
+ (XsensDotDevice *)inquireDeviceWithPeripheral:(CBPeripheral *)peripheral;

/**
 * Add sensors to the bound device pool
 * @param devices The XsensDotDevice  array
 */
+ (void)bindDevices:(NSArray <XsensDotDevice *>*)devices;

/**
 * Add a sensor to the bound device pool
 * @param device The XsensDotDevice object
 */
+ (BOOL)bindDevice:(XsensDotDevice *)device;

/**
 * Remove sensor from the bound device pool
 * @param device The XsensDotDevice object
 */
+ (void)unbindDevice:(XsensDotDevice *)device;

/**
 * Remove all sensors from the bound device pool
 */
+ (void)unbindAllDevices;

/**
 * Get all bound sensors
 * @return All bound sensors array
 */
+ (NSArray <XsensDotDevice *>*)allBoundDevices;

/**
 * Get the ota sensors , after the sensor just done ota ,this will be return.
 * @return The ota devices array
 */
+ (NSArray <XsensDotDevice *>*)allOtaDevices;

/**
 * Add a ota sensor to ota device array
 * @param device The ota object
 */
+ (void)addOtaDevice:(XsensDotDevice *)device;
@end


@interface XsensDotDevicePool (Connection)

/**
 *  Check the sensor if it is in the connected device pool. The connected device pool is a array that sensor has been connected .
 *  @param peripheral The CBPeripheral object
 */
+ (XsensDotDevice *)heldDeviceWithPeripheral:(CBPeripheral *)peripheral;

/**
 *  Add a sensor to connected device pool, Prevent the same sensor from connecting multiple times
 *  @param device The XsensDotDevice object
 */
+ (void)holdDevice:(XsensDotDevice *)device;

/**
 *  Release a sensor from connected device list, if a sensor has disconnected ,we must release it.
 *  @param device The XsensDotDevice object
 */
+ (void)releaseDevice:(XsensDotDevice *)device;

/**
 *  The bluetooth state of phone updated (Turn on or turn off bluetooth)
 */
+ (void)onCentralStateUpdated;
@end

NS_ASSUME_NONNULL_END
