//
//  UIDeviceCategory.h
//  Xsens DOT
//
//  Created by Jayson on 2019/5/8.
//  Copyright © 2019 Xsens. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIDevice (VersionInformation)
+ (CGFloat)systemVersion;
+ (NSInteger)systemMainVersion;
+ (NSString *)systemVersionString;

+ (NSString *)appBuildVersionString;
+ (NSString *)appShortVersionString;
+ (NSString *)appVersionString;
@end

@interface UIDevice (HardwareInfo)
+ (BOOL)isIPad;
+ (BOOL)isSimulator;
+ (BOOL)isJailbroken;
+ (NSString *)devicePlatformInfo;
+ (NSString *)iPhoneBriefInfo;
+ (BOOL)isIPhone4Series;
+ (BOOL)isIPhone5Series;
+ (BOOL)isIPhoneSE;
+ (BOOL)isIPhoneXSeries;
+ (NSDate *)systemUptime;
@end

NS_ASSUME_NONNULL_END
