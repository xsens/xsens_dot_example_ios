//
//  XsensDotFirmwareVersion.h
//  XsensDotSdk
//
//  Created by Nick Yang on 2019/5/15.
//  Copyright © 2019 Xsens. All rights reserved.
//
//  Sample: 0xAA 0xBB 0xCC 0xDDDDDDDD 0xEEEEEEEE
//  New Sample: 0xfdf2858ffcfb010000e3070c0607012d69915b00
//  0xAA = Major version
//  0xBB = Minor version
//  0xCC = Patch number
//  0xDDDDDDDD = Build number
//  0xEEEEEEEE = Repository revision
//

/**
 *  The Xsens DOT firmware information class.
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

extern const NSInteger BLEFirmwareVersionDataSize;

@interface XsensDotFirmwareVersion : NSObject

/// @brief Get the major version number
- (NSUInteger)majorVersion;

/// @brief Get the minor version number
- (NSUInteger)minorVersion;

/// @brief Get the reversion version number
- (NSUInteger)reversionVersion;

/// @brief Get the build year
- (NSUInteger)buildYear;

/// @brief Get the build month
- (NSUInteger)buildMonth;

/// @brief Get the build data
- (NSUInteger)buildDate;

/// @brief Get the build hour
- (NSUInteger)buildHour;

/// @brief Get the build minute
- (NSUInteger)buildMinute;

/// @brief Get the build second
- (NSUInteger)buildSecond;

/// @brief Get the soft device version
- (NSUInteger)softDeviceVersion;

/// @brief Get the build time
- (NSString *)buildTime;

/**
 *  Constructor method
 *  @param data The ble data
 */
+ (instancetype)versionWithData:(NSData *)data;

/**
 *  @brief The firmware version description
 *  @return The version string. For example: 1.6.0
 */
- (NSString *)description;

@end

NS_ASSUME_NONNULL_END
