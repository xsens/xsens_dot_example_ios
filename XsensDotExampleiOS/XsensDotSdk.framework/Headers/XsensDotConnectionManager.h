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
 *  @brief Bluetooth state changed
 *  @param managerState The XSDotManagerState state
 */
- (void)onManagerStateUpdate:(XSDotManagerState)managerState;

/**
 *  @brief Scan completed.
 */
- (void)onScanCompleted;

/**
 *  @brief Disconver a Xsend DOT  sensor when start scan.
 *  @param device The XsensDotDevice object
 */
- (void)onDiscoverDevice:(XsensDotDevice *_Nonnull)device;

/**
 *  @brief Sensor connect succeeded
 *  @param device The XsensDotDevice object
 */

- (void)onDeviceConnectSucceeded:(XsensDotDevice *_Nonnull)device;
/**
 *  @brief Sensor connect failed
 *  @param device The XsensDotDevice object
 */

- (void)onDeviceConnectFailed:(XsensDotDevice *_Nonnull)device;
/**
 *  @brief Sensor disconnected
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
 *  @brief Set the delegate
 *  @param delegate The XsensDotConnectionDelegate object
 */
+ (void)setConnectionDelegate:(nullable id<XsensDotConnectionDelegate>)delegate;

/**
 *  @brief The current bluetooth state of phone
 *  @return The XSDotManagerState object
 */
+ (XSDotManagerState)managerState;

/**
 *  @brief Phone Bluetooth is on
 *  @return The bluetooth state is power on
 */
+ (BOOL)managerStateIsPoweredOn;

/**
 *  @brief Scan Xsens DOT sensors
 */
+ (void)scan;

/**
 *  @brief Stop scan Xsens DOT sensors
 */
+ (void)stopScan;

/**
 *  @brief Connect Xsens DOT sensor
 *  @param device The XsensDotDevice object
 */
+ (void)connect:(XsensDotDevice *)device;

/**
 *  @brief Disconnect a Xsens DOT sensor
 *  @param device The XsensDotDevice object
 */
+ (void)disconnect:(XsensDotDevice *)device;

@end

NS_ASSUME_NONNULL_END
