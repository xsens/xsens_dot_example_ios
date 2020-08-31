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

@interface XsensDotFirmwareVersion : NSObject

- (NSUInteger)majorVersion;
- (NSUInteger)minorVersion;
- (NSUInteger)reversionVersion;
- (NSUInteger)buildYear;
- (NSUInteger)buildMonth;
- (NSUInteger)buildDate;
- (NSUInteger)buildHour;
- (NSUInteger)buildMinute;
- (NSUInteger)buildSecond;
- (NSUInteger)softDeviceVersion;
- (NSString *)buildTime;


+ (instancetype)versionWithData:(NSData *)data;

/*
    Return the version string like: 1.3.0
 */
- (NSString *)description;

@end

NS_ASSUME_NONNULL_END
