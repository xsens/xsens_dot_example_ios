//
//  XsensDotConnectionManager.h
//  XsensDotSdk
//
//  Created by Nick Yang on 2019/5/15.
//  Copyright © 2019 Xsens. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "XsensDotDevice.h"
#import "XsensDotDefine.h"

/**
 *  The protocol of XsensDotConnectionManager.
 *  You can use these methods to get all the scanning and connection status.
 */
@protocol XsensDotConnectionDelegate <NSObject>
@optional
/**
 *  Bluetooth state changed
 *  @param managerState The XSDotManagerState state
 */
- (void)onManagerStateUpdate:(XSDotManagerState)managerState;

/**
 *  Scan completed.
 */
- (void)onScanCompleted;

/**
 *  Disconver a Xsend DOT  sensor when start scan.
 *  @param device The XsensDotDevice object
 */
- (void)onDiscoverDevice:(XsensDotDevice *_Nonnull)device;

/**
 *  Sensor connect succeeded
 *  @param device The XsensDotDevice object
 */

- (void)onDeviceConnectSucceeded:(XsensDotDevice *_Nonnull)device;
/**
 *  Sensor connect failed
 *  @param device The XsensDotDevice object
 */

- (void)onDeviceConnectFailed:(XsensDotDevice *_Nonnull)device;
/**
 *  Sensor disconnected
 *  @param device The XsensDotDevice object
 */
- (void)onDeviceDisconnected:(XsensDotDevice *_Nonnull)device;
@end


NS_ASSUME_NONNULL_BEGIN

/**
 *  This class manages the BLE connection of Xsens DOT sensors.
 */
@interface XsensDotConnectionManager : NSObject

/**
 *  Set the delegate
 *  @param delegate The XsensDotConnectionDelegate object
 */
+ (void)setConnectionDelegate:(nullable id<XsensDotConnectionDelegate>)delegate;

/**
 *  The current bluetooth state of phone
 *  @return The XSDotManagerState object
 */
+ (XSDotManagerState)managerState;

/**
 *  Phone Bluetooth is on
 *  @return The bluetooth state is power on
 */
+ (BOOL)managerStateIsPoweredOn;

/**
 *  Scan Xsens DOT sensors
 */
+ (void)scan;

/**
 *  Stop scan Xsens DOT sensors
 */
+ (void)stopScan;

/**
 *  Connect Xsens DOT sensor
 *  @param device The XsensDotDevice object
 */
+ (void)connect:(XsensDotDevice *)device;

/**
 *  Disconnect a Xsens DOT sensor
 *  @param device The XsensDotDevice object
 */
+ (void)disconnect:(XsensDotDevice *)device;

@end

NS_ASSUME_NONNULL_END
