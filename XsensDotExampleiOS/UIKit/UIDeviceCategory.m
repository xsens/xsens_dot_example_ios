//
//  UIDeviceCategory.m
//  Xsens DOT
//
//  Created by Jayson on 2019/5/8.
//  Copyright © 2019 Xsens. All rights reserved.
//

#import "UIDeviceCategory.h"
#import <sys/types.h>
#import <sys/sysctl.h>

/*
 ----------------------------------------
 UIDevice (VersionInformation)
 ----------------------------------------
 */
@implementation UIDevice (VersionInformation)

#pragma mark - SystermVersion

+ (NSString *)systemVersionString
{
    return [UIDevice currentDevice].systemVersion;
}

+ (CGFloat)systemVersion
{
    return [self systemVersionString].floatValue;
}

+ (NSInteger)systemMainVersion
{
    return [self systemVersionString].integerValue;
}

#pragma mark - AppVersion

+ (NSString *)appBuildVersionString
{
    NSDictionary *bundleInfoDict = [NSBundle mainBundle].infoDictionary;
    NSString *buildVersion = bundleInfoDict[@"CFBundleVersion"];
    return buildVersion;
}

+ (NSString *)appShortVersionString
{
    NSDictionary *bundleInfoDict = [NSBundle mainBundle].infoDictionary;
    NSString *shortVersion = bundleInfoDict[@"CFBundleShortVersionString"];
    return shortVersion;
}

+ (NSString *)appVersionString
{
    NSString *shortVersion = [self appShortVersionString];
    NSString *buildVersion = [self appBuildVersionString];
    return [NSString stringWithFormat:@"%@ (%@)", shortVersion, buildVersion];
}

@end


/*
 ----------------------------------------
 UIDevice (HardwareInfo)
 ----------------------------------------
 */
@implementation UIDevice (HardwareInfo)

+ (BOOL)isIPad;
{
    static dispatch_once_t onceToken;
    static BOOL isIPad;
    dispatch_once(&onceToken, ^{
        isIPad = UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad;
    });
    return isIPad;
}

+ (BOOL)isSimulator
{
#if TARGET_OS_SIMULATOR
    return YES;
#else
    return NO;
#endif
}

+ (BOOL)isJailbroken
{
    if([self isSimulator])
    {
        return NO;
    }
    
    // iOS9 URL Scheme query changed ...
    // NSURL *cydiaURL = [NSURL URLWithString:@"cydia://package"];
    // if ([[UIApplication sharedApplication] canOpenURL:cydiaURL]) return YES;
    
    NSArray *paths =
    @[
      @"/Applications/Cydia.app",
      @"/private/var/lib/apt/",
      @"/private/var/lib/cydia",
      @"/private/var/stash"
      ];
    for(NSString *path in paths)
    {
        if([[NSFileManager defaultManager] fileExistsAtPath:path])
        {
            return YES;
        }
    }
    
    FILE *bash = fopen("/bin/bash", "r");
    if(bash)
    {
        fclose(bash);
        return YES;
    }
    
    CFUUIDRef uuid = CFUUIDCreate(NULL);
    CFStringRef string = CFUUIDCreateString(NULL, uuid);
    CFRelease(uuid);
    NSString *uuidString = (__bridge_transfer NSString *)string;
    
    NSString *path = [NSString stringWithFormat:@"/private/%@", uuidString];
    if([@"test" writeToFile:path atomically:YES encoding:NSUTF8StringEncoding error:NULL])
    {
        [[NSFileManager defaultManager] removeItemAtPath:path error:nil];
        return YES;
    }
    return NO;
}

+ (NSString *)machineModel
{
    static dispatch_once_t onceToken;
    static NSString *model;
    dispatch_once(&onceToken, ^{
        size_t size;
        sysctlbyname("hw.machine", NULL, &size, NULL, 0);
        char *machine = malloc(size);
        sysctlbyname("hw.machine", machine, &size, NULL, 0);
        model = [NSString stringWithUTF8String:machine];
        free(machine);
    });
    return model;
}

+ (NSString *)devicePlatformInfo
{
    /*
     https://www.theiphonewiki.com/wiki/Models
     */
    static dispatch_once_t onceToken;
    static NSString *name;
    dispatch_once(&onceToken, ^{
        NSString *model = [self machineModel];
        if(!model)
        {
            return;
        }
        NSDictionary *infoDict =
        @{
          @"iPhone1,1"      :@"iPhone 1G",
          @"iPhone1,2"      :@"iPhone 3G",
          @"iPhone2,1"      :@"iPhone 3GS",
          @"iPhone3,1"      :@"iPhone 4 (GSM)",
          @"iPhone3,2"      :@"iPhone 4",
          @"iPhone3,3"      :@"iPhone 4 (CDMA)",//@"Verizon iPhone 4"
          @"iPhone4,1"      :@"iPhone 4s",
          @"iPhone5,1"      :@"iPhone 5 (GSM)",
          @"iPhone5,2"      :@"iPhone 5 (GSM+CDMA)",
          @"iPhone5,3"      :@"iPhone 5c (GSM)",
          @"iPhone5,4"      :@"iPhone 5c (GSM+CDMA)",
          @"iPhone6,1"      :@"iPhone 5s (GSM)",
          @"iPhone6,2"      :@"iPhone 5s (GSM+CDMA)",
          @"iPhone7,1"      :@"iPhone 6 Plus",
          @"iPhone7,2"      :@"iPhone 6",
          @"iPhone8,1"      :@"iPhone 6s",
          @"iPhone8,2"      :@"iPhone 6s Plus",
          @"iPhone8,4"      :@"iPhone SE",
          @"iPhone9,1"      :@"iPhone 7",
          @"iPhone9,2"      :@"iPhone 7 Plus",
          @"iPhone9,3"      :@"iPhone 7",
          @"iPhone9,4"      :@"iPhone 7 Plus",
          @"iPhone10,1"     :@"iPhone 8",
          @"iPhone10,4"     :@"iPhone 8",
          @"iPhone10,2"     :@"iPhone 8 Plus",
          @"iPhone10,5"     :@"iPhone 8 Plus",
          @"iPhone10,3"     :@"iPhone X",
          @"iPhone10,6"     :@"iPhone X",
          @"iPhone11,8"     :@"iPhone Xr",
          @"iPhone11,2"     :@"iPhone Xs",
          @"iPhone11,4"     :@"iPhone Xs Max",
          @"iPhone11,6"     :@"iPhone Xs Max",
          
          @"i386"           :@"Simulator x86",
          @"x86_64"         :@"Simulator x64",
          
          @"iPod1,1"        :@"iPod Touch 1G",
          @"iPod2,1"        :@"iPod Touch 2G",
          @"iPod3,1"        :@"iPod Touch 3G",
          @"iPod4,1"        :@"iPod Touch 4G",
          @"iPod5,1"        :@"iPod Touch 5G",
          @"iPod7,1"        :@"iPod Touch 6G",
          
          @"iPad1,1"        :@"iPad",
          @"iPad2,1"        :@"iPad 2 (WiFi)",
          @"iPad2,2"        :@"iPad 2 (GSM)",
          @"iPad2,3"        :@"iPad 2 (CDMA)",
          @"iPad2,4"        :@"iPad 2 (WiFi)",
          @"iPad2,5"        :@"iPad Mini (WiFi)",
          @"iPad2,6"        :@"iPad Mini (GSM)",
          @"iPad2,7"        :@"iPad Mini (GSM+CDMA)",
          @"iPad3,1"        :@"iPad 3 (WiFi)",
          @"iPad3,2"        :@"iPad 3 (GSM+CDMA)",
          @"iPad3,3"        :@"iPad 3 (GSM)",
          @"iPad3,4"        :@"iPad 4 (WiFi)",
          @"iPad3,5"        :@"iPad 4 (GSM)",
          @"iPad3,6"        :@"iPad 4 (GSM+CDMA)",
          @"iPad4,1"        :@"iPad Air (WiFi)",
          @"iPad4,2"        :@"iPad Air (Cellular)",
          @"iPad4,3"        :@"iPad Air",
          @"iPad4,4"        :@"iPad Mini 2G (WiFi)",
          @"iPad4,5"        :@"iPad Mini 2G (Cellular)",
          @"iPad4,6"        :@"iPad Mini 2G",
          @"iPad4,7"        :@"iPad Mini 3 (WiFi)",
          @"iPad4,8"        :@"iPad Mini 3 (Cellular)",
          @"iPad4,9"        :@"iPad Mini 3 (China Model)",
          @"iPad5,1"        :@"iPad Mini 4 (WiFi)",
          @"iPad5,2"        :@"iPad Mini 4 (Cellular)",
          @"iPad5,3"        :@"iPad Air 2 (WiFi)",
          @"iPad5,4"        :@"iPad Air 2 (Cellular)",
          @"iPad6,3"        :@"iPad Pro (WiFi)",      //9.7inch
          @"iPad6,4"        :@"iPad Pro (Cellular)",  //9.7inch
          @"iPad6,7"        :@"iPad Pro (WiFi)",      //12.9inch
          @"iPad6,8"        :@"iPad Pro (Cellular)",  //12.9inch
          @"iPad6,11"       :@"iPad 5",
          @"iPad6,12"       :@"iPad 5",
          @"iPad7,1"        :@"iPad Pro 2",//12.9inch
          @"iPad7,2"        :@"iPad Pro 2",//12.9inch
          @"iPad7,3"        :@"iPad Pro",//10.5inch
          @"iPad7,4"        :@"iPad Pro",//10.5inch
          @"iPad7,5"        :@"iPad 6",//iPad (6th generation)
          @"iPad7,6"        :@"iPad 6",
          
          @"Watch1,1"   :@"Apple Watch (38mm)",
          @"Watch1,2"   :@"Apple Watch (42mm)",
          @"Watch2,6"   :@"Apple Watch Series 1 (38mm)",
          @"Watch2,7"   :@"Apple Watch Series 1 (42mm)",
          @"Watch2,3"   :@"Apple Watch Series 2 (38mm)",
          @"Watch2,4"   :@"Apple Watch Series 2 (42mm)",
          @"Watch3,1"   :@"Apple Watch Series 3 (38mm)",
          @"Watch3,2"   :@"Apple Watch Series 3 (42mm)",
          @"Watch3,3"   :@"Apple Watch Series 3 (38mm)",
          @"Watch3,4"   :@"Apple Watch Series 3 (42mm)",
          @"Watch4,1"   :@"Apple Watch Series 4 (40mm)",
          @"Watch4,2"   :@"Apple Watch Series 4 (44mm)",
          @"Watch4,3"   :@"Apple Watch Series 4 (40mm)",
          @"Watch4,4"   :@"Apple Watch Series 4 (44mm)",
          
          @"AppleTV2,1"   :@"Apple TV 2",
          @"AppleTV3,1"   :@"Apple TV 3",
          @"AppleTV3,2"   :@"Apple TV 3",
          @"AppleTV5,3"   :@"Apple TV 4",
          @"AppleTV6,2"   :@"Apple TV 4K",
          
          @"AirPods1,1"         :@"AirPods",
          @"AudioAccessory1,1"  :@"HomePod",
          @"AudioAccessory1,2"  :@"HomePod",
          };
        name = infoDict[model];
        if(!name)
        {
            name = model;
        }
    });
    return name;
}

+ (NSString *)iPhoneBriefInfo
{
    static dispatch_once_t onceToken;
    static NSString *briefInfo = nil;
    dispatch_once(&onceToken, ^{
        NSString *deviceInfo = self.devicePlatformInfo;
        if([deviceInfo hasPrefix:@"iPhone"])
        {
            NSRange range = [deviceInfo rangeOfString:@"("];
            if(range.length > 0)
            {
                deviceInfo = [deviceInfo substringToIndex:range.location];
            }
            briefInfo = [deviceInfo stringByReplacingOccurrencesOfString:@" " withString:@""];
        }
    });
    return briefInfo;
}

+ (BOOL)isIPhone4Series
{
    NSString *machineModel = self.machineModel;
    return (machineModel.length > 0
            && [@[@"iPhone3,1", @"iPhone3,2", @"iPhone3,3", @"iPhone4,1"] containsObject:machineModel]);
}

+ (BOOL)isIPhoneSE
{
    NSString *machineModel = self.machineModel;
    return (machineModel.length > 0
            && [machineModel isEqualToString:@"iPhone8,4"]);
}

+ (BOOL)isIPhone5Series
{
    NSString *machineModel = self.machineModel;
    return (machineModel.length > 0
            && [@[@"iPhone5,1", @"iPhone5,2", @"iPhone5,3", @"iPhone5,4", @"iPhone6,1", @"iPhone6,2"] containsObject:machineModel]);
}

+ (BOOL)isIPhoneXSeries
{
    BOOL iPhoneXSeries = NO;
    if(UIDevice.currentDevice.userInterfaceIdiom == UIUserInterfaceIdiomPhone)
    {
        if(@available(iOS 11.0, *))
        {
            UIWindow *mainWindow = [UIApplication sharedApplication].delegate.window;
            if(mainWindow.safeAreaInsets.bottom > 0.0)
            {
                iPhoneXSeries = YES;
            }
        }
    }
    return iPhoneXSeries;
}

+ (BOOL)isIPhoneXSeries2
{
#ifdef DEBUG
    CGSize screenSize = [UIScreen mainScreen].currentMode.size;
    return (CGSizeEqualToSize(CGSizeMake(1125, 2436), screenSize)
            || CGSizeEqualToSize(CGSizeMake(828, 1792), screenSize)
            || CGSizeEqualToSize(CGSizeMake(1242, 2688), screenSize));
#else
    NSString *machineModel = self.machineModel;
    return (machineModel.length > 0
            && [@[@"iPhone10,3", @"iPhone10,6", @"iPhone11,8", @"iPhone11,2", @"iPhone11,4", @"iPhone11,6"] containsObject:machineModel]);
#endif
}

+ (BOOL)isIPhoneX
{
#ifdef DEBUG
    return CGSizeEqualToSize(CGSizeMake(1125, 2436), [UIScreen mainScreen].currentMode.size);
    //return CGSizeEqualToSize([UIScreen mainScreen].bounds.size, CGSizeMake(375, 812));
#else
    NSString *machineModel = self.machineModel;
    return (machineModel.length > 0
            && [@[@"iPhone10,3", @"iPhone10,6"] containsObject:machineModel]);
#endif
}

+ (NSDate *)systemUptime
{
    NSTimeInterval time = [[NSProcessInfo processInfo] systemUptime];
    return [NSDate dateWithTimeIntervalSinceNow:-time];
}

@end
