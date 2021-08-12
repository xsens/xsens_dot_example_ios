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

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

extern const NSInteger BLEFirmwareVersionDataSize;

/**
 *  The Xsens DOT firmware information class.
 */
@interface XsensDotFirmwareVersion : NSObject

/**
 * Get the major version number
 */
- (NSUInteger)majorVersion;

/**
 * Get the minor version number
 */
- (NSUInteger)minorVersion;

/**
 * Get the reversion version number
 */
- (NSUInteger)reversionVersion;

/**
 * Get the build year
 */
- (NSUInteger)buildYear;

/**
 * Get the build month
 */
- (NSUInteger)buildMonth;

/**
 * Get the build data
 */
- (NSUInteger)buildDate;

/**
 * Get the build hour
 */
- (NSUInteger)buildHour;

/**
 * Get the build minute
 */
- (NSUInteger)buildMinute;

/**
 * Get the build second
 */
- (NSUInteger)buildSecond;

/**
 * Get the soft device version
 */
- (NSUInteger)softDeviceVersion;

/**
 * Get the build time
 */
- (NSString *)buildTime;

/**
 *  Constructor method
 *  @param data The ble data
 */
+ (instancetype)versionWithData:(NSData *)data;

/**
 *  The firmware version description
 *  @return The version string. For example: 1.6.0
 */
- (NSString *)description;

@end

NS_ASSUME_NONNULL_END
