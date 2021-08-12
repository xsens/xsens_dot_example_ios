//
//  XsensDotReconnectManager.h
//  XsensDotSdk
//
//  Created by Nick Yang on 2019/6/19.
//  Copyright © 2019 Xsens. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  Xsens DOT reconnection manager class, when setEnable is set to YES,
 *  the sensor will automatically reconnect every second if the connection is lost.
 */
@interface XsensDotReconnectManager : NSObject

/**
 * Set reconnection enable
 * @param enable Enable/Disable reconnection
 */
+ (void)setEnable:(BOOL)enable;
/**
 * Get current reconnection state
 * @return The enable state
 */
+ (BOOL)enable;

/**
 * Bluetooth state of phone has changed
 */
+ (void)onManagerStateUpdated;

/**
 * The Bounded sensors count has changed
 */
+ (void)onBoundDeviceCapacityModified;

@end

NS_ASSUME_NONNULL_END
